##	程序设计与计算机系统第八章作业

*	题目

	8.13 8.15, 8.18

	<br>

*	8.13

	题目所给程序为

	```c
	int main(){
		int x = 3;
		if( Fork() != 0 ){
			// 父进程
			printf("x = %d\n", ++x);
		}

		// 父与子都执行
		printf("x = %d\n", --x);
	}
	```

	因此可以得到如下进程图

	![result1](https://github.com/jJayyyyyyy/USTC-2018-Smester-1/blob/master/CSAPP/homework/hw06/assets/result1.jpg)

	所以可能的输出为

	```
	4
	3
	2
	```

	或

	```
	4
	2
	3
	```

	或

	```
	2
	4
	3
	```

	<br>

*	8.15

	题目所给代码为

	```c
	void doit(){
		if( Fork() == 0 ){
			// 子进程
			Fork();
			// 子子进程和子父进程
			printf("hello\n");
			return;
		}
		return;
	}

	int main(){
		doit();
		printf("hello\n");
		exit(0);
	}
	```

	由于 `fork()` 相当于是 `replicate`, 每个子进程会回到自己的 `main()`, 而不是一个统一的 `main()`, 因此可以得到如下进程图

	![result2](https://github.com/jJayyyyyyy/USTC-2018-Smester-1/blob/master/CSAPP/homework/hw06/assets/result2.jpg)

	所以一共会输出 `5` 行 `hello`

	<br>

*	8.18

	题目所给代码为

	```c
	void end(){
		printf("2");
		fflush(stdout);
	}

	int main(){
		if( Fork() == 0 ){
			// 子进程
			atexit(end);
		}

		if( Fork() == 0 ){
			printf("0");
			fflush(stdout);
		}else{
			printf("1");
			fflush(stdout);
		}

		exit(0);
	}
	```

	可以得到如下进程图

	![result3](https://github.com/jJayyyyyyy/USTC-2018-Smester-1/blob/master/CSAPP/homework/hw06/assets/result3.jpg)

	可以发现, 在第一个 `2` 之前必有一个 `n1`, `n1` 可以是`0` 或 `1`

	在第二个 `2` 之前, 除了 `n1` 还至少有 `n2`, `n2` 可以是`0` 或 `1`

	观察题目所给选项, `B` 中第一个 `2` 前面没有数, 不会出现这样的输出, `D` 的第二个 `2` 之前只有一个 `0` 或 `1`, 这也是不可能的。因此可能出现的输出是 `A, C, E`

	<br>

##	参考资料

*	[CSAPP](https://book.douban.com/subject/26344642/)

*	[CMU 15-213](https://www.bilibili.com/video/av20304787?p=13)
