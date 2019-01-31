#
# Makefile for linuxnet/lab3
#

CC_PTHREAD_FLAGS			 = -lpthread
CC_FLAGS                     = -c 
CC_OUTPUT_FLAGS				 = -o
CC                           = gcc
RM                           = rm
RM_FLAGS                     = -f

TARGET  =   main
OBJS    =   linktable.o  menu.o main.o

all:	$(OBJS)
	$(CC) $(CC_OUTPUT_FLAGS) $(TARGET) $(OBJS) 
rootfs:
	gcc -o init linktable.c menu.c main.c -m32 -static -lpthread
	find init | cpio -o -Hnewc |gzip -9 > ../rootfs.img
	qemu -kernel ../../linux-3.18.6/arch/x86/boot/bzImage -initrd ../rootfs.img -s -S
.c.o:
	$(CC) $(CC_FLAGS) $<

clean:
	$(RM) $(RM_FLAGS)  $(OBJS) $(TARGET) *.bak init
