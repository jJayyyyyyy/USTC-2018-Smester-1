*	首先依次运行 `ramdisk` 中的命令

	```bash
	#!/bin/bash
	dd if=/dev/zero of=rootfs.img bs=4096 count=1024
	mkfs.ext3 rootfs.img

	mkdir root
	sudo mount -o loop rootfs.img root

	sudo cp etc root/ -rf

	gcc -o init linktable.c menu.c main.c -m32 -static -lpthread
	sudo cp init root/
	sudo mkdir root/dev

	sudo mknod root/dev/console c 5 1
	sudo mknod root/dev/ram b 1 0
	sudo umount root
	```

*	再运行 `remake` 中的命令

	```bash
	#!/bin/bash
	gcc -o init linktable.c menu.c main.c -m32 -static -lpthread
	sudo mount -o loop rootfs.img root
	sudo cp init root/
	sudo umount root
	
	qemu-system-i386 -curses -kernel ../bzImage -initrd rootfs.img -append "root=/dev/ram init=/init"

	```

	即可启动 menuos