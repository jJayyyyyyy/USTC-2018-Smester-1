##	构建调试Linux内核网络代码的环境MenuOS系统

*	lab2有一些问题, 可以略过, 直接做 lab3

	<br><br>

##	附录

*	练习: 编译多个文件

	首先进入 exercise 文件夹下

	*	方法 1, 直接法

		```bash
		$ gcc client.c client.h server.c server.h main.c -o main
		$ ./main
		```

	*	编写 Makefile

		```bash
		demo: main.o client.o server.o
			cc -o demo main.o client.o server.o

		main.o: main.c client.h server.h
			cc -c main.c

		client.o: client.c client.h
			cc -c client.c

		server.o: server.c server.h
			cc -c server.c

		clean:
			rm main.o client.o server.o

		.PHONY : demo clean
		```

		然后

		```bash
		make
		make clean
		```

	<br>

*	原实验链接

	[lab2](https://github.com/mengning/linuxnet/tree/master/lab2)

	[构建调试Linux内核网络代码的环境MenuOS系统](https://www.shiyanlou.com/courses/1198/labs/8925/document)

	跟踪分析Linux内核的启动过程

	*	初识MenuOS系统

		我们已经在LinuxKernel目录构建好了基于3.18.6的内核环境，可以使用实验楼的虚拟机打开Xfce终端（Terminal）, 运行MenuOS系统。

		```bash
		shiyanlou:~/ $ cd LinuxKernel/
		shiyanlou:LinuxKernel/ $ qemu -kernel linux-3.18.6/arch/x86/boot/bzImage -initrd rootfs.img
		```

		内核启动完成后进入menu程序（《软件工程C编码实践篇》的课程项目），支持三个命令help、version和quit，您也可以添加更多的命令，对选修过《软件工程C编码实践篇》的童鞋应该是a piece of cake.

	*	跟踪分析Linux内核的启动过程的具体操作方法

		使用gdb跟踪调试内核首先添加-s和-S选项启动MenuOS系

		```bash
		qemu -kernel linux-3.18.6/arch/x86/boot/bzImage -initrd rootfs.img -s -S
		```

		关于-s和-S选项的说明：

		```
		-S freeze CPU at startup (use ’c’ to start execution)
		-s shorthand for -gdb tcp::1234 若不想使用1234端口，则可以使用-gdb tcp:xxxx来取代-s选项
		```

		右击水平分割或者另外打开一个Xfce终端（Terminal），执行gdb

		```
		$ gdb
		> file linux-3.18.6/vmlinux # 在gdb界面中targe remote之前加载符号表
		> target remote:1234 # 建立gdb和gdbserver之间的连接
		> break start_kernel # 断点的设置可以在target remote之前，也可以在之后
		> c                  # 按c 让qemu上的Linux继续运行

		注意：按Ctrl+Alt从QEMU窗口里的MenuOS系统返回到当前系统，否则会误以为卡死在那里。

	*	将网络通信程序的服务端集成到MenuOS系统中

		接下来我们需要将C/S方式的网络通信程序的服务端集成到MenuOS系统中,成为MenuOS系统的命令replyhi，实际上我们已经给大家集成好了,我们git clone 克隆一个linuxnet.git；进入lab2目录执行make可以将我们集成好的代码copy到menu项目中。然后进入menu,我们写了一个脚本rootfs,运行make rootfs,脚本就可以帮助我们自动编译、自动生成根文件系统,还会帮我们运行起来MenuOS系统。详细命令如下：

		```
		cd LinuxKernel  
		git clone https://github.com/mengning/linuxnet.git
		cd linuxnet/lab2
		make
		cd ../../menu/
		make rootfs
		```

		其中我们增加了命令replyhi，功能是回复hi的TCP服务. 接下来您就可以参照前面“跟踪分析Linux内核的启动过程的具体操作方法”进行跟踪调试了，只是我们socket接口使用的是系统sys_socketcall，可以将sys_socketcall设为断点跟踪看看。

		本课程的实验环境沿用庖丁解牛Linux内核慕课课程的实验环境，更具体实验环境构建过程可以参考慕课视频。
