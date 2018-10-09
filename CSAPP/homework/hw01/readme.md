##	程序设计与计算机系统第二章作业

*	2.58

	```c
	int is_little_endian(){
		unsigned short a = 0x0012;
		unsigned char * p = (unsigned char *) & a;
		if( p[0] == 0x12 ){
			return 1;
		}else{
			return 0;
		}
	}
	```

*	2.61

	*	A.　　`!(x+1);`
	*	B.　　`!x;`
	*	C.　　`((x & 0xff) + 1 ) >> 8) & 0x01;`
	*	D.　　`!( ( x >> ( (sizeof(int) - 1) << 3) ) & 0xff );`

*	2.77

	*	K=17.　　　`x + (x << 4);`
	*	K=-7.　　　`x - (x << 3);`
	*	K=60.　　　`(x << 6) - (x << 2);`
	*	K=-112.　　`(x << 4) - (x << 7);`

*	2.84

	```c
	return	( !( ux & 0x7fffffff ) && !( uy & 0x7fffffff ) ) ||	// 1. 0 <= 0, 除了符号位, 其他位全为0
		( sx && !sy ) ||					// 2. 负数 <= 正数
		( !(sx - sy) && ( (ux - uy) >> 31 ) & 0x01 );		// 3. 符号相同, ux - uy <= 0, 则 x <= y
	```

*	2.89

	*	A.　　正确

		```c
		1. 32-bit float 最多 24 位有效位数, 而 64-bit double 最多有 54 位有效位数, 
		2. 设 x 的有效位数为 significand,
		3. 当 significand <= 24 时, float 和 double 都能保留 x 的准确值
		4. 当 24 < significand <= 32 < 54 时, x 被 cast 成 float 时, 多出来的有效位数会被 rounded
		5. 而当 x 被 cast 成 double 时，虽然能够保留 x 的准确值, 但是当 dx 再被 cast 成 float 时, 
		   多出来的有效位数也会按照和 4 相同的规则被 rounded,
		6. 所以最后结果是相同的
		```

	*	B.　　错误

		```c
		// 假设
		int x = 0x80000000;
		int y = 0x7fffffff;
		double dx = (double) x;
		double dy = (double) y;

		printf("%lf\n", dx-dy);				// -4294967295.000000
		printf("%lf\n", (double)(x-y));			// 1.000000
		// 所以 dx - dy != (double)(x - y)
		```

	*	C.　　正确

		```c
		一般来说, 浮点数不满足结合律, 这主要是由 rounding 造成的, 比如书中的例子
		(3 + 1e10) - 1e10 != 3 +(1e10 - 1e10), 因为单精度下, 

		1e10     = 10 0101 0100 0000 1011 1110 0100 0000 0000
		3        = 00 0000 0000 0000 0000 0000 0000 0000 0011

		3 + 1e10 = [10 0101 0100 0000 1011 1110 01] 00 0000 0011

		由于 float 的 significand 只有 23, 所以在 rounding 的时候会将最后的 [00 0000 0011] 舍去, 即丢失了精度,
		但是这里我们用到的是 double, 其 significand 有 52, 足够放下来自 32-bit int 的所有有效位, 
		因此在本题条件下, 结合律成立
		```

	*	D.　　错误

		```c
		// 假设
		int x = 0x55555555;
		int y = 0x7fffffff;
		int z = 0x7fffffff;
		double dx = (double) x;
		double dy = (double) y;
		double dz = (double) z;
		
		printf("%lf\n", (dx * dy) * dz);	// 660234686850255 07 00000000000.000000
		printf("%lf\n", dx * (dy * dz));	// 660234686850255 18 00000000000.000000
		// 两者不相等
		```

	*	E.　　错误

		```c
		当 int x = 0, z = 1; 时
		dx / dx 结果是 INF
		dz / dz 结果是 1.000000
		```

*	2.91

	*	A.　　`0x40490FDB = 11.00 1001 0000 1111 1101 1011 (2)`
	*	B.　　`22/7 = 3 + 1/7 = 11 + 1/111 (2) = 11.001 001 001 001...`
	*	C.　　`从二进制小数点后的第9位开始不同`

<br><br>

##	解题过程与分析

*	题源: `CSAPP` 第三版第二章

	<!--吐槽：中文版翻译质量堪忧，如 `2.58` 的 `procedure`，在当前语境应该是 `程序` 的意思，却译成了 `过程`。更糟糕的是。。`2.57` 的 `procedure` 对应的中文翻译是 `程序`。这该不会是传说中的佛系翻译吧-->

*	2.58 Write a procedure `is_little_endian` that will return 1 when compiled and run on a little-endian machine, and will return 0 when compiled and run on a big-endian machine. This program should run on any machine, regardless of its word size.

	编写程序 `is_little_endian` ，当它在小端系统上编译运行后，返回的值是 `1`，当它在大端系统上编译运行后，返回的值是 `0`。要求这个程序可以运行在任何机器上，无论机器的字长是多少。

	```c
	#include <stdio.h>
	
	// 对于 unsigned short a = 0x0012
	// 若是 little endian, 那么 [内存地址: 值]应该是这样的
	// 0x10010: 0x12
	// 0x10011: 0x00
	//
	// 若是 big endian,    那么 [内存地址: 值]应该是这样的
	// 0x10010: 0x00
	// 0x10011: 0x12
	int is_little_endian(){
		unsigned short a = 0x0012;
		unsigned char * p = (unsigned char *) & a;
		if( p[0] == 0x12 ){
			return 1;
		}else{
			return 0;
		}
	}
	
	int main(){
		printf("%d\n", is_little_endian());
		return 0;
	}
	```

	<br>

*	2.61 Write C expressions that evaluate to 1 when the following conditions are true and to 0 when they are false. Assume x is of type `int`.

	对于下列描述，分别写出对应的C语言表达式，使其值为 `1`，而在其他情况下，值为 `0`，假设 `x` 是 `int` 类型的变量。

	*	A. `x` 的任何位都等于 `1`
	
		```c
		// 若 x 的任何位都为 1, 则 x + 1 会溢出, 得到全 0 
		// (x+1) 为假, !(x+1) 为真

		!(x+1);
		```

	*	B. `x` 的任何位都等于 `0`

		```c
		// 若 x 全 0, 则 x 为假, !x 为真

		!x;
		```

	*	C. `x` 的最低有效字节中的任何位都等于 `1`

		```c
		// 先取 x 的最低 8 bit, (x & 0xff), 设为 y
		// 若 y 全为 1, 则 y+1 会有进位, 即0x100
		// 否则 y+1 只在低 8 bit 有非0数字, 高位都是 0
		// 记 z = y + 1
		// 再将 z 右移 8 bit, 得到 a,
		// 若 a 的最低位为 1, 则说明 y->z 的过程中发生了进位
		// 也即 x 的最低有效字节中的任何位都等于 1

		((x & 0xff) + 1 ) >> 8) & 0x01;
		```

	*	D. `x` 的最高有效字节中的任何位都等于 `0`

		```c
		// 首先获取 x 的最高有效字节
		// 若 int 为 16 bit
		// 则 (sizeof(int) - 1) << 3 :== 8
		// (x >> 8) & 0xff 即为 x 的最高 8 位，设为 y
		// 若 int 为 32 bit
		// 则 (sizeof(int) - 1) << 3 :== 24
		// (x >> 24) & 0xff 即为 x 的最高 8 位，设为 y
		//
		// 最后，若 y 全为 0, 则 !y 为 1, 否则 !y 为 1
		// 由此可以判断 `x` 的最高有效字节中的任何位是否为 `0`
		// 最后, 由于 C 语言的移位操作执行的是 逻辑左移 和 算术右移, 所以需要加上 & 0xff 盖掉可能存在的符号位

		!( ( x >> ( (sizeof(int) - 1) << 3) ) & 0xff );
		```

	<br>

*	2.77 Suppose we are given the task of generating code to multiply integer variable x by various different constant factors K. To be efficient, we want to use only the operations `+`, `-`, and `<<`. For the following values of K, write C expressions to perform the multiplication using at most three operations per expression.

	假设我们有一个任务，生成一段代码，将整数变量 `x` 乘以不同的常数因子 `K`。为了提高效率，我们只想使用 `+`, `-`, `<<` 运算。对于下列 `K` 值，写出执行乘法运算的 `C` 语言表达式，每个表达式最多使用 3 个运算

	*	K = 17

		```c
		// x * 17 == x + x * 16
		( x + (x << 4) );
		```

	*	K = -7

		```c
		// x * (-7) == x - x * 8
		( x - (x << 3) );
		```

	*	K = 60

		```c
		// x * 60 == x * 64 - x * 4
		( (x << 6) - (x << 2) );
		```

	*	K = -112

		```c
		// x * -112 = x * 16 - x * 128
		( (x << 4) - (x << 7) );
		```

	<br>

*	2.84 Fill in the return value for the following procedure, which tests whether its first  argument is less than or equal to its second. Assume the functino f2u returns an unsigned 32-bit number having the same bit representation as its floating-point argument. You can assume that neither argument is `NaN`, The two flavors of zero, `+0` and `-0`, are considered equal.

	填写下列程序的返回值。这个程序测试它的第一个参数是否小于等于第二个参数。假定函数 `f2u` 返回一个无符号32位整数，它的和原浮点数有相同的二进制表示形式。你可以假设两个参数都不是 `NaN`，而且假设两种 `0`，即 `+0` 和 `-0` 是相等的。

	```c
	int float_le(float x, float y){
		unsigned ux = f2u(x);
		unsigned uy = f2u(y);

		/* Get the sign bits */
		unsigned sx = ux >> 31;
		unsigned sy = uy >> 31;

		/* Give an expression using only ux, uy, sx, and sy */
		return	( !( ux & 0x7fffffff ) && !( uy & 0x7fffffff ) ) ||	// 1. 0 <= 0, 除了符号位, 其他位全为0
			( sx && !sy ) ||					// 2. 负数 <= 正数
			( !(sx - sy) && ( (ux - uy) >> 31 ) & 0x01 );		// 3. 符号相同, ux - uy <= 0, 则 x <= y
	}
	```

	<br>

*	2.89 We are running programs on a machine where values of type int have a 32-bit two's-complement representation. Values of type float use the 32-bit IEEE format, and values of type double use the 64-bit IEEE format.

	我们在一个 `int` 类型为 `32-bit` 补码表示的机器上运行程序。`float` 类型的值使用 `32-bit IEEE` 格式，而 `double` 类型的值使用 `64-bit IEEE` 格式

	We generate arbitrary integer values x, y, and z, and convert them to values of type double as follows:

	我们产生随机整数 `x, y, z`, 并把它们转换成 `double` 类型的值:

	```c
	/* Create some arbitarary values */
	int x = random();
	int y = random();
	int z = random();
	/* Convert to double */
	double dx = (double) x;
	double dy = (double) y;
	double dz = (double) z;
	```

	for each of the following C expressions, you are to indicate whether or not the expression always yields 1. If it always yields 1, describe the underlying mathematical principles. Otherwise, give an example of arguments that make it yield 0. Note that you cannot use an IA32 machine running `GCC` to test your answers, since it would use the 80-bit extended-precision representation for both float and double.

	对于下列的每个 `C` 表达式，你要指出表达式的值是否为 `1`。如果它总是为 `1`，请描述其中的数学原理，否则举出反例。请注意，不要使用 `IA32` 机器运行 `GCC` 来测试你的答案，因为对于 `float` 和 `double`，它使用的都是 `80-bit` 扩展的精度表示。

	*	A. (float) x == (float) dx;

		```c
		true, 理由如下

		1. 32-bit float 最多 24 位有效位数, 而 64-bit double 最多有 54 位有效位数, 
		2. 设 x 的有效位数为 significand,
		3. 当 significand <= 24 时, float 和 double 都能保留 x 的准确值
		4. 当 24 < significand <= 32 < 54 时, x 被 cast 成 float 时, 多出来的有效位数会被 rounded
		5. 而当 x 被 cast 成 double 时，虽然能够保留 x 的准确值, 但是当 dx 再被 cast 成 float 时, 
		   多出来的有效位数也会按照和 4 相同的规则被 rounded,
		6. 所以最后结果是相同的

		举例，设 int x = 0x7fffffff;
		即 x = (0111 1111 1111 1111 1111 1111 1111 1111)2 = (1.11 ....)(2) * (2 ^ 30)
		转换成 float 时, 因为超过了最大有效位数, 所以舍去了一部分内容并进行了 rounding
		float f1 = (float) x = (1.000 ... 0000)(2) * 2 ^ 31
		f1 在内存中的表示形式为 0x4f 00 00 00

		而 double dx = (double) x = (1.11 ....)(2) * (2 ^ 30)
		在内存中的表示形式为 0x41 DF FF FF FF C0 00 00
		dx 在被 cast 成为 float 之后的结果，和 f1 一样，是 0x4f 00 00 00
		```

	*	B. dx - dy == (double) (x - y);

		```c
		false, 理由如下, 设
		
		int x = 0x80000000;
		int y = 0x7fffffff;
		double dx = (double) x;
		double dy = (double) y;

		printf("%lf\n", dx-dy);			// -4294967295.000000
		printf("%lf\n", (double)(x-y));		// 1.000000
		
		所以 dx - dy != (double)(x - y)
		```

	*	C. (dx + dy) + dz == dx + (dy + dz);

		```c
		true, 理由如下

		一般来说, 浮点数不满足结合律, 这主要是由 rounding 造成的, 比如书中的例子
		(3 + 1e10) - 1e10 != 3 +(1e10 - 1e10), 因为单精度下, 

		1e10     =  10 0101 0100 0000 1011 1110 0100 0000 0000
		3        =  00 0000 0000 0000 0000 0000 0000 0000 0011
		3 + 1e10 = [10 0101 0100 0000 1011 1110 01] 00 0000 0011

		由于 float 的 significand 只有 23, 所以在 rounding 的时候会将最后的 [00 0000 0011] 舍去, 即丢失了精度,
		但是这里我们用到的是 double, 其 significand 有 52, 足够放下来自 32-bit int 的所有有效位, 
		因此在本题条件下, 结合律成立
		```

	*	D. (dx * dy) * dz == dx * (dy * dz);

		```c
		false, 理由如下

		加法最多增加一个有效位, double肯定能够容纳, 但是乘法可能使有效位加倍,
		如原来有 30 个有效位, 那么新的结果最多就有 60 个左右的有效位, double就可能放不下了, 下面用一个例子说明, 设

		int x = 0x55555555;
		int y = 0x7fffffff;
		int z = 0x7fffffff;
		double dx = (double) x;
		double dy = (double) y;
		double dz = (double) z;
		
		printf("%lf\n", (dx * dy) * dz);	// 660234686850255 07 00000000000.000000
		printf("%lf\n", dx * (dy * dz));	// 660234686850255 18 00000000000.000000
		两者不相等
		```

	*	E. dx / dx == dz / dz;

		```c
		false, 理由如下

		假设 int x = 0, z = 1; 那么
		dx / dx 结果是 INF
		dz / dz 结果是 1.000000
		```

	<br>

*	2.91 Around 250 B.C., the Greek Mathematician Archimedes proved that `233/71 < π < 22/7`. Had he had access to a computer and the standard library `<math.h>`, he would have been able to determine that the single-precision floating-point approximation of `π` has the hexadecimal representation `0x40490FDB`. Of course, all of these are just approximations, since `π` is not rational.

	大约在公元前 250 年，希腊数学家阿基米德证明了 `233/71 < π < 22/7`，如果当时有一台计算机，而且有标准库函数 `<math.h>`，那么他就能确定 `π` 的单精度浮点数近似值的十六进制表示为 `0x40490FDB`。当然，所有的这些都只是近似值，因为 `π` 不是有理数。

	*	A. What is the fractional binary number denoted by this floating-point value 0x40490FDB?

		这个浮点数 `0x40490FDB` 表示的二进制小数是多少？

		```c
		0x40490FDB = 0100 0000 0100 1001 0000 1111 1101 1011 (2)
		           = 0	1000 0000	1 0010 0100 0011 1111 0110 11

		因此   exp = 1000 0000 = 128
		         E = exp - bias = 128 - 127 = 1
		      frac = 100 1001 0000 1111 1101 1011

		所以答案是
		       val = 1.100 1001 0000 1111 1101 1011 * 2^1
		           = 11.00 1001 0000 1111 1101 1011

		// 另外, 还可以进一步算出
		//     val = (1+1/2+1/16+1/128+1/4096+...) * 2 ≈ 1.57079637 * 2 ≈ 3.14159274
		```

	*	B. What is the fractional binary representation of 22/7? Hint: See Problem 2.83

		`22/7` 的二进制小数表示是什么？

		```c
		因为   1/7 = 1.00/111 (2) = 0.001 001 001 001 ...
		所以  22/7 = 3 + 1/7 = 11 + 1.00/111 (2) = 11.001 001 001 001...
		
		另外 10/71 = 1010.000/1000111 (2) = 0.001 001 000001 ...
		```

	*	C. At what bit postion (relative to the binary point) do these two approximation to π diverge?

		这两个 `π` 的近似值从二进制小数点后的哪一位开始不同？

		```c
		binVal(0x40490FDB) = 11.0010 0100 0011 1111 0110 11 (2)
		
		binVal(22/7)       = 11.0010 0100 1001 0010 0100 10 ... (2)
		binVal(233/71)     = 11.0010 0100 0001 ... (2)

		所以，在二进制中，从第小数点后第9位开始不同
		```

	<br>

##	参考资料

*	[CSAPP](https://book.douban.com/subject/26344642/)

*	[CMU, CS-15-213](https://www.cs.cmu.edu/~213/)

*	[CMU计算机必修课 15-213: Introduction to Computer Systems](https://www.bilibili.com/video/av20304787)

*	[CSDN论坛, x是int型，写一个C表达式使该表达式在x的任何位都等于1时是1](https://bbs.csdn.net/topics/390210659)

*	[csapp-3e-solutions](https://dreamanddead.gitbooks.io/csapp-3e-solutions/)

*	[C语言中的逻辑右移和算术左移](https://blog.csdn.net/zyings/article/details/47084485)

	Special Thanks to 小徐同学

*	[Floating-point arithmetic, Wikipedia](https://en.wikipedia.org/wiki/Floating_point)

*	[Denormal number, Wikipedia](https://en.wikipedia.org/wiki/Denormal_number)
