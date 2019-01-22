##	开发环境

*	Ubuntu 14.04

	<br>

##	安装步骤

*	首先安装必要的编译工具和库

	```bash
	sudo apt-get update
	sudo apt-get install make gcc libc6-dev build-essential bc
	sudo apt-get install libncurses5-dev libncursesw5-dev
	```

*	新建文件夹 `~/LinuxKernel`, 下载解压编译 `linux-3.18.6` 的源代码

	```bash
	mkdir ~/LinuxKernel
	cd ~/LinuxKernel/
	wget https://www.kernel.org/pub/linux/kernel/v3.x/linux-3.18.6.tar.xz
	xz -d linux-3.18.6.tar.xz
	tar -xvf linux-3.18.6.tar
	cd linux-3.18.6
	make i386_defconfig
	make
	```

*	编译 `menu`

	```bash
	cd ~/LinuxKernel/
	git clone https://github.com/mengning/menu.git
	cd menu

	gcc -o init linktable.c menu.c test.c -static –pthread
	# 原博客的编译参数可能会出错
	# gcc: error: –lpthread: No such file or directory
	# 需要多尝试几种方法


	# 我使用的是如下命令, 两种方法都可行
	gcc -o init -pthread linktable.c menu.c test.c -static
	# gcc -Wall -pthread -o init linktable.c menu.c test.c -static
	```

*	建立 `rootfs`

	```bash
	mkdir rootfs
	cd ../rootfs
	cp ../menu/init ./
	find . | cpio -o -H newc |gzip -9 > ../rootfs.img
	cd ..
	```

*	安装 `qemu`

	```bash
	sudo apt-get install qemu
	```

*	测试运行

	如果是通过 ssh 连接到 vps 来使用 qemu, 直接运行如下命令会报错, 因为没有图像界面设备

	```
	qemu-system-i386 -kernel linux-3.18.6/arch/x86/boot/bzImage -initrd rootfs.img
	# Could not initialize SDL(No available video device) - exiting
	```

	根据 [这个问答](https://stackoverflow.com/questions/22967925/running-qemu-remotely-via-ssh), 通过 ssh 连接时需要增加 -curses 参数

	```
	qemu-system-i386 -curses -kernel linux-3.18.6/arch/x86/boot/bzImage -initrd rootfs.img
	```

	退出 qemu 的时候, 需要依次按下 `ESC`, `2`, `q`, `Enter`

	也可以根据这篇文章 [qemu_guide](https://www.cs.swarthmore.edu/~newhall/unixhelp/qemu_guide.html), 使用 pkill 关闭进程

	```
	pkill qemu
	```

	<br>

*	配置 menu

	```bash
	cd ~/LinuxKernel/linux-3.18.6
	make menuconfig
	# 依次选择 kernel hacking --- compile-time checks and compile options --- compile the kernel with debug info
	# 然后 save --- ok, 一路退出

	# 重新 make
	make
	```


*	测试运行

	```
	qemu-system-i386 -curses -kernel linux-3.18.6/arch/x86/boot/bzImage -initrd rootfs.img -s -S
	```

	此时 menuos 会停住, 等待外部的 continue 信号, 此时需要通过 gdb 进行调试

	另外建立一个 ssh 连接, 然后

	```
	gdb
	> file linux-3.18.6/vmlinux
	> target remote:1234
	> continue
	```

	如果一切正常, menuos 就可以启动了

*	搭建好环境后, 剩下的内容参照课程大纲即可

	<br>

##	参考链接

*	[linux内核编译与调试方法](https://www.cnblogs.com/syw-casualet/p/5271369.html)

*	[running-qemu-remotely-via-ssh](https://stackoverflow.com/questions/22967925/running-qemu-remotely-via-ssh)

*	[qemu_guide](https://www.cs.swarthmore.edu/~newhall/unixhelp/qemu_guide.html)
