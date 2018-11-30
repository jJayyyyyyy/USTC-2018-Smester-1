##	0. 实验准备

*	实验名称

	**Lab 5: Writing a Dynamic Storage Allocator**

*	实验内容和目的

	本实验需要用 C 语言实现一个动态的存储分配器，也就是你自己版本的 `malloc(), free(), realloc()` 函数。

*	实验环境

	*	Ubuntu 16.04 x64

	*	gcc 4.8.4

	*	GNU Make 3.81

	<br>

##	1. 实验步骤

*	解压 handout

	```bash
	tar xvf malloclab-handout.tar
	```

*	我们需要修改的唯一文件是 `mm.c`, 包含如下几个需要实现的函数

	```c
	// 在调用 mm_malloc, mm_realloc, mm_free之前需要调用 mm_init 进行初始化, 正确则返回0
	int mm_init(void);

	// 在堆区域分配指定大小的块, 分配的空间, 返回的指针应该是8字节对齐的
	void *mm_malloc(size_t size);

	// 释放指针指向的block
	void mm_free(void *ptr);

	// 返回指向一个大小为size的区域指针, 满足以下条件
	// if ptr is NULL
	//     then the call is equivalent to mm_malloc(size); 
	// if size is equal to zero
	//     the call is equivalent to mm_free(ptr);
	// if ptr is not NULL
	//     then 先按照 size 指定的大小分配空间, 将原有数据从头到尾拷贝到新分配的内存区域, 而后释放原来ptr所指内存区域
	void *mm_realloc(void *ptr, size_t size);
	```

*	在 `memory.c` 中有如下函数可供调用

	```c
	// Expands the heap by incr bytes, where incr is apositive non-zero integer
	// returns a generic pointer to the first byte of the newly allocated heap area
	void *mem_sbrk(int incr);

	// Returns a generic pointer to the first byte in the heap
	void *mem_heap_lo(void);

	// Returns a generic pointer to the last byte in the heap
	void *mem_heap_hi(void);

	// Returns the current size of the heap in bytes
	size_t mem_heapsize(void);

	// Returns the system’s page size in bytes (4K onLinux systems)
	size_t mem_pagesize(void);
	```

*	编程规则

	不能改变 `mm.c` 的函数接口

	不能直接调用任何内存管理的库函数和系统函数 `malloc, calloc, free, realloc, sbrk, brk`

	不能定义任何全局或者静态复合数据结构如 `arrays, structs, trees`

	允许使用 `int, float, pointer` 等简单数据类型

	返回的指针需要8字节对齐

*	验证

	使用如下命令对 `mm.c` 进行测试, 并得出其空间利用率和吞吐量

	```bash
	./mdriver -V  -f short1-bal.rep
	```

	其中 `-V` 参数表示打印出诊断信息, `-f <tracefile>` 表示使用 `trace file` 来测试我们实现的函数

*	提交

	只要提交 `mm.c` 文件

	<br>

##	2. 实验分析

TODO

##	3. 实验结果

*	参考代码

	```
	./malloclab-handout/mm1.c
	./malloclab-handout/mm2.c
	```

*	实验结果截图

![result](https://github.com/jJayyyyyyy/USTC-2018-Smester-1/blob/master/CSAPP/exp/lab05/assets/result.png)

##	4. 参考资料

*	[ICS Malloc Lab: Writing a Dynamic Storage Allocator](https://blog.csdn.net/kqzxcmh/article/details/41552945)

*	[Computer System: A Programmers Perspective](https://book.douban.com/subject/26344642/)

*	[CSAPP:malloclab(一)](https://zybuluo.com/windmelon/note/1354896)
