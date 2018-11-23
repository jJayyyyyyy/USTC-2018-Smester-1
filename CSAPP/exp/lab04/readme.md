##	0. 实验准备

*	实验名称

	**Lab 4:Code Optimization**

*	实验内容和目的

	图像处理中存在很多函数，可以对这些函数进行优化。本实验主要关注两种图像处理操作

	*	旋转：对图像逆时针旋转90度
	*	平滑：对图像进行模糊操作

	图像用二维矩阵 `M` 表示，`M[i][j]`表示图像 `M` 的第 `[i, j]` 像素的值，像素值用红，绿，蓝表示

*	实验环境

	*	Ubuntu 16.04 x64
	*	gcc 4.8.4
	*	GNU Make 3.81

*	`make driver` 可能出现的错误

	```
	/usr/bin/ld: skipping incompatible /usr/lib/gcc/x86_64-linux-gnu/4.8/libgcc.a when searching for -lgcc
	/usr/bin/ld: cannot find -lgcc
	/usr/bin/ld: skipping incompatible /usr/lib/gcc/x86_64-linux-gnu/4.8/libgcc_s.so when searching for -lgcc_s
	/usr/bin/ld: cannot find -lgcc_s
	collect2: error: ld returned 1 exit status
	make: *** [driver] Error 1
	```

	解决方案

	```bash
	$ sudo apt-get install gcc-multilib
	```

*	在本实验中像素 `pixel` 定义为如下的结构体

	```c
	typedef struct {
		unsigned short red;    /* R value */
		unsigned short green;  /* G value */
		unsigned short blue;   /* B value */
	} pixel;
	```

*	`RIDX(i,j,n)`, 用于定位 M[i][j]

	```c
	#define RIDX(i,j,n) ((i)*(n)+(j))
	```

	<br>

##	1. rotate 旋转

*	题目要求

	逆时针旋转(rotates an image counter-clockwise by 90°)。旋转操作用可以由下面 2 步操作完成

	*	Transpose, 矩阵转置，即将 M(i, j) 变为 M(j, i)
	
	*	Exchange rows，即交换 row(i) 和 row(N-1-i)

*	`naive_rotate()` 如下

	```c
	void naive_rotate(int dim, pixel *src, pixel *dst) {
		int i, j;
		for(i=0; i < dim; i++)
			for(j=0; j < dim; j++)
				dst[RIDX(dim-1-j,i,dim)] = src[RIDX(i,j,dim)];
		return;
	}
	/*
	dst[j][i] = src[i][j];
	src[i][j] = src[i*dim + j] = src[RIDX(i,j,dim)]
	dst[j][i] = dst[RIDX(j,i,dim)]

	dst[dim-1-j][i] = dst[j][i]
	dst[dim-1-j][i] = dst[RIDX(dim-1-j,i,dim)]

	所以合并起来就是 dst[RIDX(dim-1-j,i,dim)] = src[RIDX(i,j,dim)]
	*/
	```

*	优化

	主要应当采用分块的手段提高代码的空间局部性的利用率。分块之后可以减少大量的cache miss，从而提升速度。

	尝试了不同大小的分块，在实验机器上，32x32 分块矩阵的cache平均命中率最高

	```c
	// 关于 rotate() 函数的描述
	char rotate_descr[] = "rotate: 32*32 version";
	// 32x32 分块的 rotate() 函数
	void rotate(int dim, pixel *src, pixel *dst){
		int i, j, k, l;
		int div = 32;
		for (i = 0; i < dim; i += div) {
			for (j = 0; j < dim; j += div) {
				for (k = i; k < i + div; k++) {
					for (l = j; l < j + div; l++) {
						dst[RIDX(k, l, dim)] = src[RIDX(l, dim - 1 - k, dim)];
					}
				}
			}
		}
	}

	// 注册 rotate() 函数
	void register_rotate_functions(){
		add_rotate_function(&naive_rotate, naive_rotate_descr);   
		/* ... Register additional test functions here */
		add_rotate_function(&rotate, rotate_descr);
	}
	```

	<br>

##	2. smooth 平滑

*	题目要求

	本题要求我们实现一个平滑操作，将每个格子用它周围一圈格子(9个, 含自身)的平均值代替。

*	`naive_smooth()` 如下

	```c
	void naive_smooth(int dim, pixel *src, pixel *dst){
		int i, j;

		for (i = 0; i < dim; i++)
		for (j = 0; j < dim; j++)
			dst[RIDX(i, j, dim)] = avg(dim, i, j, src);
	}
	```

*	优化

	在 `naive_smooth()` 中，把整个矩阵作为一个整体，然后对于每个 `M[i][j]` 都需要进行函数调用，然后还要进行条件判断，造成极大的时间浪费。

	本题主要优化这两个方面，也就是，把矩阵的不同区域分开处理。由于是求周围及其自身格子的平均值，且不会在矩阵周围补零，因此可以把矩阵分为这么几个区域

	```
	1. 四个角
	2. 四条边(不含四个顶角)
	3. 中间区域(每个格子周围都是满的)
	```

	然后，直接展开，写出每一部分各自的循环，而不是调用 `avg()` 函数

	因此可以得到如下优化后的代码

	```c
	char smooth_descr[] = "smooth: Current working version";
	void smooth(int dim, pixel *src, pixel *dst){
		int i, j;

		// 中间的部分
		for (i = 1; i < dim - 1; i++) {
			for (j = 1; j < dim - 1; j++) {
				// 求 red 分量的 9 个格子的平均值
				dst[RIDX(i, j, dim)].red = (src[RIDX(i - 1, j - 1, dim)].red
				                         + src[RIDX(i, j - 1, dim)].red
				                         + src[RIDX(i + 1, j - 1, dim)].red
				                         + src[RIDX(i - 1, j, dim)].red
				                         + src[RIDX(i, j, dim)].red
				                         + src[RIDX(i + 1, j, dim)].red
				                         + src[RIDX(i - 1, j + 1, dim)].red
				                         + src[RIDX(i, j + 1, dim)].red
				                         + src[RIDX(i + 1, j + 1, dim)].red)
				                         / 9;
				
				// 求 green 分量的 9 个格子的平均值
				dst[RIDX(i, j, dim)].green = (src[RIDX(i - 1, j - 1, dim)].green
				                           + src[RIDX(i, j - 1, dim)].green
				                           + src[RIDX(i + 1, j - 1, dim)].green
				                           + src[RIDX(i - 1, j, dim)].green
				                           + src[RIDX(i, j, dim)].green
				                           + src[RIDX(i + 1, j, dim)].green
				                           + src[RIDX(i - 1, j + 1, dim)].green
				                           + src[RIDX(i, j + 1, dim)].green
				                           + src[RIDX(i + 1, j + 1, dim)].green)
				                           / 9;
				// 求 blue 分量的 9 个格子的平均值
				dst[RIDX(i, j, dim)].blue = (src[RIDX(i - 1, j - 1, dim)].blue
				                          + src[RIDX(i, j - 1, dim)].blue
				                          + src[RIDX(i + 1, j - 1, dim)].blue
				                          + src[RIDX(i - 1, j, dim)].blue
				                          + src[RIDX(i, j, dim)].blue
				                          + src[RIDX(i + 1, j, dim)].blue
				                          + src[RIDX(i - 1, j + 1, dim)].blue
				                          + src[RIDX(i, j + 1, dim)].blue
				                          + src[RIDX(i + 1, j + 1, dim)].blue)
				                          / 9;
			}
		}

		// 处理最上面一行(除了两个顶角)
		for (i = 1; i < dim - 1; i++) {
			dst[RIDX(i, 0, dim)].red = (src[RIDX(i - 1, 0, dim)].red
			                         + src[RIDX(i, 0, dim)].red
			                         + src[RIDX(i + 1, 0, dim)].red
			                         + src[RIDX(i - 1, 1, dim)].red
			                         + src[RIDX(i, 1, dim)].red
			                         + src[RIDX(i + 1, 1, dim)].red)
			                         / 6;

			dst[RIDX(i, 0, dim)].green = (src[RIDX(i - 1, 0, dim)].green
			                           + src[RIDX(i, 0, dim)].green
			                           + src[RIDX(i + 1, 0, dim)].green
			                           + src[RIDX(i - 1, 1, dim)].green
			                           + src[RIDX(i, 1, dim)].green
			                           + src[RIDX(i + 1, 1, dim)].green)
			                           / 6;

			dst[RIDX(i, 0, dim)].blue = (src[RIDX(i - 1, 0, dim)].blue
			                          + src[RIDX(i, 0, dim)].blue
			                          + src[RIDX(i + 1, 0, dim)].blue
			                          + src[RIDX(i - 1, 1, dim)].blue
			                          + src[RIDX(i, 1, dim)].blue
			                          + src[RIDX(i + 1, 1, dim)].blue) / 6;
		}

		// 处理最下面一行(除了两个顶角)
		for (i = 1; i < dim - 1; i++) {
			dst[RIDX(i, dim - 1, dim)].red = (src[RIDX(i - 1, dim - 2, dim)].red
			                               + src[RIDX(i, dim - 2, dim)].red
			                               + src[RIDX(i + 1, dim - 2, dim)].red
			                               + src[RIDX(i - 1, dim - 1, dim)].red
			                               + src[RIDX(i, dim - 1, dim)].red
			                               + src[RIDX(i + 1, dim - 1, dim)].red)
			                               / 6;

			dst[RIDX(i, dim - 1, dim)].green = (src[RIDX(i - 1, dim - 2, dim)].green
			                                 + src[RIDX(i, dim - 2, dim)].green
			                                 + src[RIDX(i + 1, dim - 2, dim)].green
			                                 + src[RIDX(i - 1, dim - 1, dim)].green
			                                 + src[RIDX(i, dim - 1, dim)].green
			                                 + src[RIDX(i + 1, dim - 1, dim)].green)
			                                 / 6;

			dst[RIDX(i, dim - 1, dim)].blue = (src[RIDX(i - 1, dim - 2, dim)].blue
			                                + src[RIDX(i, dim - 2, dim)].blue
			                                + src[RIDX(i + 1, dim - 2, dim)].blue
			                                + src[RIDX(i - 1, dim - 1, dim)].blue
			                                + src[RIDX(i, dim - 1, dim)].blue
			                                + src[RIDX(i + 1, dim - 1, dim)].blue)
			                                / 6;
		}

		// 处理最左边一列(除了两个顶角)
		for (j = 1; j < dim - 1; j++) {
			dst[RIDX(0, j, dim)].red = (src[RIDX(0, j - 1, dim)].red
			                         + src[RIDX(0, j, dim)].red
			                         + src[RIDX(0, j + 1, dim)].red
			                         + src[RIDX(1, j - 1, dim)].red
			                         + src[RIDX(1, j, dim)].red
			                         + src[RIDX(1, j + 1, dim)].red)
			                         / 6;

			dst[RIDX(0, j, dim)].green = (src[RIDX(0, j - 1, dim)].green
			                           + src[RIDX(0, j, dim)].green
			                           + src[RIDX(0, j + 1, dim)].green
			                           + src[RIDX(1, j - 1, dim)].green
			                           + src[RIDX(1, j, dim)].green
			                           + src[RIDX(1, j + 1, dim)].green)
			                           / 6;

			dst[RIDX(0, j, dim)].blue = (src[RIDX(0, j - 1, dim)].blue
			                          + src[RIDX(0, j, dim)].blue
			                          + src[RIDX(0, j + 1, dim)].blue
			                          + src[RIDX(1, j - 1, dim)].blue
			                          + src[RIDX(1, j, dim)].blue
			                          + src[RIDX(1, j + 1, dim)].blue)
			                          / 6;
		}

		// 处理最右边一列(除了两个顶角)
		for (j = 1; j < dim - 1; j++) {
			dst[RIDX(dim - 1, j, dim)].red = (src[RIDX(dim - 1, j - 1, dim)].red
			                               + src[RIDX(dim - 1, j, dim)].red
			                               + src[RIDX(dim - 1, j + 1, dim)].red
			                               + src[RIDX(dim - 2, j - 1, dim)].red
			                               + src[RIDX(dim - 2, j, dim)].red
			                               + src[RIDX(dim - 2, j + 1, dim)].red)
			                               / 6;

			dst[RIDX(dim - 1, j, dim)].green = (src[RIDX(dim - 1, j - 1, dim)].green
			                                 + src[RIDX(dim - 1, j, dim)].green
			                                 + src[RIDX(dim - 1, j + 1, dim)].green
			                                 + src[RIDX(dim - 2, j - 1, dim)].green
			                                 + src[RIDX(dim - 2, j, dim)].green
			                                 + src[RIDX(dim - 2, j + 1, dim)].green)
			                                 / 6;

			dst[RIDX(dim - 1, j, dim)].blue = (src[RIDX(dim - 1, j - 1, dim)].blue
			                                + src[RIDX(dim - 1, j, dim)].blue
			                                + src[RIDX(dim - 1, j + 1, dim)].blue
			                                + src[RIDX(dim - 2, j - 1, dim)].blue
			                                + src[RIDX(dim - 2, j, dim)].blue
			                                + src[RIDX(dim - 2, j + 1, dim)].blue)
			                                / 6;
		}

		// 处理左上角
		dst[RIDX(0, 0, dim)].red = (src[RIDX(0, 0, dim)].red
		                         + src[RIDX(0, 1, dim)].red
		                         + src[RIDX(1, 0, dim)].red
		                         + src[RIDX(1, 1, dim)].red)
		                         >> 2;
		dst[RIDX(0, 0, dim)].green = (src[RIDX(0, 0, dim)].green
		                           + src[RIDX(0, 1, dim)].green
		                           + src[RIDX(1, 0, dim)].green
		                           + src[RIDX(1, 1, dim)].green)
		                           >> 2;
		dst[RIDX(0, 0, dim)].blue = (src[RIDX(0, 0, dim)].blue
		                          + src[RIDX(0, 1, dim)].blue
		                          + src[RIDX(1, 0, dim)].blue
		                          + src[RIDX(1, 1, dim)].blue)
		                          >> 2;

		// 处理右上角
		dst[RIDX(0, dim - 1, dim)].red = (src[RIDX(0, dim - 1, dim)].red
		                               + src[RIDX(0, dim - 2, dim)].red
		                               + src[RIDX(1, dim - 1, dim)].red
		                               + src[RIDX(1, dim - 2, dim)].red)
		                               >> 2;

		dst[RIDX(0, dim - 1, dim)].green = (src[RIDX(0, dim - 1, dim)].green
		                                 + src[RIDX(0, dim - 2, dim)].green
		                                 + src[RIDX(1, dim - 1, dim)].green
		                                 + src[RIDX(1, dim - 2, dim)].green)
		                                 >> 2;
		dst[RIDX(0, dim - 1, dim)].blue = (src[RIDX(0, dim - 1, dim)].blue
		                                + src[RIDX(0, dim - 2, dim)].blue
		                                + src[RIDX(1, dim - 1, dim)].blue
		                                + src[RIDX(1, dim - 2, dim)].blue)
		                                >> 2;

		// 处理左下角
		dst[RIDX(dim - 1, 0, dim)].red = (src[RIDX(dim - 1, 0, dim)].red
		                               + src[RIDX(dim - 1, 1, dim)].red
		                               + src[RIDX(dim - 2, 0, dim)].red
		                               + src[RIDX(dim - 2, 1, dim)].red)
		                               >> 2;
		dst[RIDX(dim - 1, 0, dim)].green = (src[RIDX(dim - 1, 0, dim)].green
		                                 + src[RIDX(dim - 1, 1, dim)].green
		                                 + src[RIDX(dim - 2, 0, dim)].green
		                                 + src[RIDX(dim - 2, 1, dim)].green)
		                                 >> 2;
		dst[RIDX(dim - 1, 0, dim)].blue = (src[RIDX(dim - 1, 0, dim)].blue
		                                + src[RIDX(dim - 1, 1, dim)].blue
		                                + src[RIDX(dim - 2, 0, dim)].blue
		                                + src[RIDX(dim - 2, 1, dim)].blue)
		                                >> 2;

		// 处理右下角
		dst[RIDX(dim - 1, dim - 1, dim)].red = (src[RIDX(dim - 1, dim - 1, dim)].red
		                                     + src[RIDX(dim - 2, dim - 1, dim)].red
		                                     + src[RIDX(dim - 1, dim - 2, dim)].red
		                                     + src[RIDX(dim - 2, dim - 2, dim)].red)
		                                     >> 2;
		dst[RIDX(dim - 1, dim - 1, dim)].green = (src[RIDX(dim - 1, dim - 1, dim)].green
		                                       + src[RIDX(dim - 2, dim - 1, dim)].green
		                                       + src[RIDX(dim - 1, dim - 2, dim)].green
		                                       + src[RIDX(dim - 2, dim - 2, dim)].green)
		                                       >> 2;
		dst[RIDX(dim - 1, dim - 1, dim)].blue = (src[RIDX(dim - 1, dim - 1, dim)].blue
		                                      + src[RIDX(dim - 2, dim - 1, dim)].blue
		                                      + src[RIDX(dim - 1, dim - 2, dim)].blue
		                                      + src[RIDX(dim - 2, dim - 2, dim)].blue)
		                                      >> 2;
	}
	```

	<br>

##	3. 实验结果

*	截图如下

	![result](https://github.com/jJayyyyyyy/USTC-2018-Smester-1/blob/master/CSAPP/exp/lab04/assets/result.png)

	<br>

##	参考资料

*	[bestscores:6.4:35.0:](http://zxcpyp.com/csapp/2017/11/19/Performance-Lab)

	http://zxcpyp.com/categories/#CSAPP

*	[bestscores:5.4:34.9:](https://blog.codedragon.tech/2017/07/20/%E6%B7%B1%E5%85%A5%E7%90%86%E8%A7%A3%E8%AE%A1%E7%AE%97%E6%9C%BA%E7%B3%BB%E7%BB%9FPerformanceLab%E5%AE%9E%E9%AA%8C%E6%8A%A5%E5%91%8A/)

	https://github.com/BlackDragonF/CSAPPLabs/blob/master/PerformanceLab/kernels.c

*	[bestscores:9.3:34.1](https://github.com/gaocegege/ICS-Labs/blob/master/lab8/kernels.c)

	<br>

*	https://blog.csdn.net/shiyuqing1207/article/details/46286651

*	https://askubuntu.com/questions/85978/building-a-32-bit-app-in-64-bit-ubuntu/85979

*	https://blog.csdn.net/think_ycx/article/details/79846175

*	https://ubuntuforums.org/showthread.php?t=1402263

	<br>
