##	程序设计与计算机系统第七章作业

7.7, 7.8, 7.10, 7.12

*	7.7

	*	将 `bar5.c` 中的 `double x` 改为 `int x`
	*	去掉 `bar5.c` 第 6 行的 `x = -0.0`
	*	修改后的 `bar5.c` 为

		```c
		int x;

		void f(){
		}
		```

		<br>

		另外, 也可也把 `bar5.c` 中的 `x` 改为局部变量, 

		```c
		void f(){
			double x;
			x = -0.0;
		}
		```

		这样就不会影响 `foo5.c` 中的 `x` 了

	<br>

*	7.8

	*	A

		```
		a). main.1
		b). main.2    (static 仅在本文件起作用, 不会跨文件)
		```

	*	B

		```
		a). UNKNOWN (未知, 由 rule3 任意选择一个)
		b). UNKNOWN (未知, 由 rule3 任意选择一个)
		```

	*	C

		```
		a). ERROR (错误, 两个模块中都是 strong, 违反 rule1)
		b). ERROR (错误, 两个模块中都是 strong, 违反 rule1)
		```

	<br>

*	7.10

	*	A

		```bash
		# p.o 依赖于 libx.a
		gcc p.o libx.a
		```

	*	B

		```bash
		# p.o 依赖于 libx.a 和 liby.a, 而 liby.a 又依赖于 libx.a, 因此 libx.a 需要重复出现
		gcc p.o libx.a liby.a libx.a
		```

	*	C

		```bash
		# p.o 依赖于 libx.a 和 liby.a, 而 liby.a 又依赖于 libx.a, 因此 libx.a 需要重复出现
		# 最后, libx.a 和 liby.a 都依赖于 libz.a, 所以 libz.a 放在最后
		gcc p.o libx.a liby.a libx.a libz.a
		```

	<br>

*	7.12

	*	A. `0xa`

		由题可得

		```
		r.offset = 0xa
		r.symbol = swap
		r.type   = R_X86_64_PC32    # 相对引用
		r.addend = -4

		ADDR(s) = ADDR(.text) = <m> = 0x4004e0
		ADDR(r.symbol) = ADDR(swap) = <swap> = 0x4004f8

		refaddr = <m> + r.offset
		        = 0x4004e0 + 0xa
		        = 0x4004ea

		*refptr = <swap> + r.addend - refaddr
		        = 0x4004f8 + (-4) - 0x4004ea
		        = 0xa
		```

		所以, 当 `<m>=0x4004e0, <swap> = 0x4004f8` 时, `callq` 指令中对 `swap` 的重定位引用的值为 `0xa`

		<br>

	*	B. `0xa`

		同上可得

		```
		<m> = 0x4004d0
		<swap> = 0x400500

		refaddr = <m> + r.offset
		        = 0x4004d0 + 0xa
		        = 0x4004da

		*refptr = <swap> + r.addend - refaddr
		        = 0x400500 + (-4) - 0x4004da
		        = 0x22
		```

		所以, 当 `<m>=0x4004d0, <swap> = 0x400500` 时, `callq` 指令中对 `swap` 的重定位引用的值为 `0x22`

		<br>

##	参考资料

*	[CSAPP](https://book.douban.com/subject/26344642/)
*	[CMU 15-213](https://www.bilibili.com/video/av20304787?p=13)
