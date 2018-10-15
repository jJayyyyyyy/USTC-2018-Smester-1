/* 
 * CS:APP Data Lab 
 * 
 * Lou, Xu, Chen
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

// You will provide your solution to the Data Lab by
// editing the collection of functions in this source file.

// INTEGER CODING RULES:
 
// 	Replace the "return" statement in each function with one
// 	or more lines of C code that implements the function. Your code 
// 	must conform to the following style:
 
// 	int Funct(arg1, arg2, ...) {
// 			/* brief description of how your implementation works */
// 			int var1 = Expr1;
// 			...
// 			int varM = ExprM;

// 			varJ = ExprJ;
// 			...
// 			varN = ExprN;
// 			return ExprR;
// 	}

// 	Each "Expr" is an expression using ONLY the following:
// 	1. Integer constants 0 through 255 (0xFF), inclusive. You are
// 			not allowed to use big constants such as 0xffffffff.
// 	2. Function arguments and local variables (no global variables).
// 	3. Unary integer operations ! ~
// 	4. Binary integer operations & ^ | + << >>
		
// 	Some of the problems restrict the set of allowed operators even further.
// 	Each "Expr" may consist of multiple operators. You are not restricted to
// 	one operator per line.

// 	You are expressly forbidden to:
// 	1. Use any control constructs such as if, do, while, for, switch, etc.
// 	2. Define or use any macros.
// 	3. Define any additional functions in this file.
// 	4. Call any functions.
// 	5. Use any other operations, such as &&, ||, -, or ?:
// 	6. Use any form of casting.
// 	7. Use any data type other than int.  This implies that you
// 		cannot use arrays, structs, or unions.

 
// 	You may assume that your machine:
// 	1. Uses 2s complement, 32-bit representations of integers.
// 	2. Performs right shifts arithmetically.
// 	3. Has unpredictable behavior when shifting an integer by more than the word size.

// EXAMPLES OF ACCEPTABLE CODING STYLE:
// 	/*
// 	* pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
// 	*/
// 	int pow2plus1(int x) {
// 		/* exploit ability of shifts to compute powers of 2 */
// 		return (1 << x) + 1;
// 	}

// 	/*
// 	* pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
// 	*/
// 	int pow2plus4(int x) {
// 		/* exploit ability of shifts to compute powers of 2 */
// 		int result = (1 << x);
// 		result += 4;
// 		return result;
// 	}

// FLOATING POINT CODING RULES

// For the problems that require you to implent floating-point operations,
// the coding rules are less strict.  You are allowed to use looping and
// conditional control.  You are allowed to use both ints and unsigneds.
// You can use arbitrary integer and unsigned constants.

// You are expressly forbidden to:
// 	1. Define or use any macros.
// 	2. Define any additional functions in this file.
// 	3. Call any functions.
// 	4. Use any form of casting.
// 	5. Use any data type other than int or unsigned.  This means that you
// 		cannot use arrays, structs, or unions.
// 	6. Use any floating point data types, operations, or constants.


// NOTES:
// 	1. Use the dlc (data lab checker) compiler (described in the handout) to 
// 		check the legality of your solutions.
// 	2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
// 		that you are allowed to use for your implementation of the function. 
// 		The max operator count is checked by dlc. Note that '=' is not 
// 		counted; you may use as many of these as you want without penalty.
// 	3. Use the btest test harness to check your functions for correctness.
// 	4. Use the BDD checker to formally verify your functions
// 	5. The maximum number of ops for each function is given in the
// 		header comment for each function. If there are any inconsistencies 
// 		between the maximum ops in the writeup and in this file, consider
// 		this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
#include "btest.h"
/* Copyright (C) 1991-2017 Free Software Foundation, Inc.
	This file is part of the GNU C Library.

	The GNU C Library is free software; you can redistribute it and/or
	modify it under the terms of the GNU Lesser General Public
	License as published by the Free Software Foundation; either
	version 2.1 of the License, or (at your option) any later version.

	The GNU C Library is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
	Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public
	License along with the GNU C Library; if not, see
	<http://www.gnu.org/licenses/>.  */
/* This header is separate from features.h so that the compiler can
	include it implicitly at the start of every compilation.  It must
	not itself include <features.h> or any other header that includes
	<features.h> because the implicit include comes before any feature
	test macros that may be defined in a source file before it first
	explicitly includes a system header.  GCC knows the name of this
	header in order to preinclude it.  */
/* glibc's intent is to support the IEC 559 math functionality, real
	and complex.  If the GCC (4.9 and later) predefined macros
	specifying compiler intent are available, use them to determine
	whether the overall intent is to support these features; otherwise,
	presume an older compiler has intent to support these features and
	define these macros by default.  */
/* wchar_t uses Unicode 10.0.0.  Version 10.0 of the Unicode Standard is
	synchronized with ISO/IEC 10646:2017, fifth edition, plus
	the following additions from Amendment 1 to the fifth edition:
	- 56 emoji characters
	- 285 hentaigana
	- 3 additional Zanabazar Square characters */
/* We do not support C11 <threads.h>.  */

/* 
 * bitAnd - x&y using only ~ and |
 * 用 ~ | 实现 &
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
int bitAnd(int x, int y) {
	/* 根据德摩根定律, ~( ~x | ~y ) == (x & y) */
	return ~( ~x | ~y );
}
/* 
 * getByte - Extract byte n from word x
 * 获取 x 的第 n 个字节(从高位开始)
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int getByte(int x, int n) {
	/* Shift x n*8 positions right */
	/* 右移 n*8 位 */
	int shift = n << 3;
	int xs = x >> shift;
	/* Mask byte */
	/* 然后取最低的字节 */
	return xs & 0xFF;
}
/* 
 * logicalShift - shift x to the right by n, using a logical shift
 * C语言的右移算术右移, 本题要求我们实现逻辑右移
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3 
 */
int logicalShift(int x, int n) {
	/* Create mask for n = 0 */
	/* n == 0 的时候特殊处理，因为 x<<32 是个 Undefined Behavior */
	/* 若 n == 0, 则 zmask = 1 */
	/* 若 n != 0, 则 zmask = 0 */
	int zmask = (!n);
	/* Arithmetic shift right by n */
	/* 先对 x 进行算术右移 */
	int right = x >> n;

	/* Mask off upper 1's */
	/* 然后用 0 覆盖掉 x 的高 n 位 */
	/* 假设 n = 3, 那么最终的 lmask = 0001 1.. 1111  */

	/* 1. 若 n == 0, 使 lmask = 0 */
	/* 2. 若 n != 0, 使 lmask = 1111 .... 1111 */
	int lmask = ~( (zmask << 31) >> 31 );
	
	/* 然后 tmpmask = (1111 .... 1111) << (32-n), 注意下方代码中的 (33 + ~n) = (32 + ~n + 1) = (32 - n) */
	/* 目的是得到 tmpmask = 1110 .... 0000, 后面再进行一次取反操作即可得到 0001 .... 1111 */
	/* 1. 若 n == 0, 虽然 tmpmask 会出现 UB, 但是 lmask = lmask & tmpmask = 0 & tmpmask = 0, 即 lmask 仍为 0, 符合要求 */
	/* 1. 若 n != 0, lmask = lmask & tmpmask = 1111 .... 1111 & tmpmask = tmpmask, 即 lmask = tmpmask, 符合要求 */

	// int tmpmask = ~0 << (33 + ~n);
	lmask = lmask & ( ~0 << (33 + ~n) );
	lmask = ~lmask;

	/* right = right & lmask = right & 0001 .... 1111, 从而使高 3 位覆盖为 0 */
	right = right & lmask;
	return right;
}
/*
 * bitCount - returns count of number of 1's in word
 * 统计 x 的二进制表示中有多少个 1
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int bitCount(int x) {
	/* Sum 8 groups of 4 bits each */
	/* 将 x 分为 8 组, 每组 4 bit, 为了方便描述, 设第 1 组为最低 4bit, 第 8 组为最高 4bit */
	int m1 = 0x11 | (0x11 << 8);
	/* mask = 0x1111 1111 */
	int mask = m1 | (m1 << 16);
	int s = x & mask;
	s += x>>1 & mask;
	s += x>>2 & mask;
	s += x>>3 & mask;
	/* 现在每一小组的值就是各自小组中 1 的个数 */
	/* 每组最多 4 个 1, 即最大值为 0100(2) */

	/* Now combine high and low order sums */
	/* 将第 8 组的值加到第 4 组, 依此类推, 7->3, 6->2, 5->1 */
	/* 每组最大值为 1000(2) */
	s = s + (s >> 16);
	s &= 0xff | (0xff << 8);
	/* 若 x=-1, 则此时 s = 0x00008888 */

	/* Low order 16 bits now consists of 4 sums,
		each ranging between 0 and 8.
		Split into two groups and sum */
	/* mask = 0x0f0f */
	mask = 0x0F | (0x0F << 8);

	/* 将第 4 组的值加到第 2 组, 3->1 */
	s = (s & mask) + ((s >> 4) & mask);
	/* 每组最大值为 10000(2), 即可能有向高组的进位, 如 x=-1, 则此时 s = 0001 0000 0001 0000(2) */

	/* 由于一个小组的容量最大为 8, 而上一条注释已经说明了此时最大值可能超过 8, 如 16 */
	/* 所以现在需要一次移动 2 个小组 */
	/* 将 [4, 3] -> [2, 1] */
	s = ( s + (s>>8) );
	/* 若 x = -1, 则 s = 0001 0000 0010 0000(2) */

	/* 由于 s 的第 [4, 3] 组中可能存在 1, 我们还需要将其置为 0 */
	s &= 0x3F;
	/* 现在, x 中所有的 1 都保存在 s 的最低 8 位里面了 */
	return s;
}
/* 
 * bang - Compute !x without using !
 * 实现 !x 的功能, 但是不能使用 ! 运算符
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int bang(int x) {
	/* 先得到 x 的相反数 minux_x = -x = ~x + 1 */
	int minus_x = ~x + 1;
	/* Cute trick: 0 is the only value of x
	* for which neither x nor -x are negative */
	/* 若 x != 0, 那么 (x | minus_x) 的最高位肯定是 1 */
	return ( ~(minus_x | x) >> 31 ) & 1;
}
/* 
 * tmin - return minimum two's complement integer
 * 获得二进制补码的最小值, 即 -2^31
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
	return 1 << 31;
}
/* 
 * fitsBits - return 1 if x can be represented as an
 * 判断 x 是否能用 n 位补码表示
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n) {
	/* 设 x 的最高有效位是从低往高第 pos 位 */
	/* 对于负数, n >= pos */
	/* 对于非负数, n >= pos+1 */
	/* 这样, x 才能用 n 位补码表示 */
	/* 下面的思路是一种等价表达形式 */

	/* 首先获得 shift = 32 - n, 0 <= shift < 31 */
	int shift = 32 + ~n + 1;
	int move = (x << shift) >> shift;
	/* move 由 x 逻辑左移 shift 位, 再算术右移 shift 位得到 */
	/* 若 x 与 move 每一位都相同, 则 x ^ move == 0 */
	int res = x ^ move;
	res = !res;
	/* 说明 x 可以用 n 位补码表示 */
	return res;
}
/* TODO
 * divpwr2 - Compute x/(2^n), for 0 <= n <= 30
 *  Round toward zero
 * 计算 x/(2^n), 对结果进行向下取整
 *   Examples: divpwr2(15,1) = 7, divpwr2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int divpwr2(int x, int n) {
	/* Handle rounding by generating bias:
		0 when x >= 0
		2^n-1 when x < 0
	*/
	/* 方法1, */
	/* 对于非负数, 直接右移 n 位 即可 */
	/* 对于负数, 加上 bias = 2^n-1, 如 -33/2^4, 一种等价的做法是 y=33>>4, 然后 y = -y = ~y+1 */
	/* 但是对于负数 x, 为什么 x+2^n-1 == -( (-x)>>n ), 暂时还没有理解 */
	/* 负数为什么要加上 bias = 2^n-1 */
	/* 还没理解在做取整的时候, 负数所加的 bias = 2^n-1 是如何算出来的 */

	// mask = 2^n - 1
	int mask = (1 << n) + ~0;
	int bias = (x >> 31) & mask;
	return (x+bias) >> n;

	/*
	// 方法2, 使用等价做法 y=33>>4, 然后y = -y = ~y+1
	int result1 = x >> n;
	int result2 = ~((~x+1) >> n) + 1;
	
	// if( sgn == 0 ){
	// 	return result1;
	// }else{
	// 	return result2;
	// }
	// 用符号位 sgn 实现 if
	int sgn = (x>>31) & 1;
	int mask = (sgn<<31)>>31;
	result1 &= ~mask;
	result2 &= mask;

	return result1 | result2;
	// 还要处理 tmin, 因为 -tmin == tmin, 没有正数的对应值
	// 需要把 tmin 当成正数, 直接 >> n
	// 但是再做这些判断的话 op 就不够用了
	*/
}
/* 
 * negate - return -x
 * 获得 x 的相反数 -x, 不能使用 - 运算符
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
	/* 补码求相反数, -x == ~x + 1 */
	/* 无论 x 是正数, 0, 还是负数, 上述规则都适用 */
	return ~x + 1;
}
/* 
 * isPositive - return 1 if x > 0, return 0 otherwise
 * 判断 x 是否大于 0
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 3
 */
int isPositive(int x) {
	/* 首先判断 x 是否为 0 */
	/* 若 x != 0, 则判断 x 的最高位是否为 1 */
	return !((!x) | (x >> 31));
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0
 * 判断 x <= y 是否成立
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
	/* (x <= y) 可以推出 (y - x >= 0), 考虑以下2种情况 */
	/* 1. x < 0, y >= 0, 先考虑这种情况, 防止 y-x 溢出 */
	/* 2. x, y 都不是 0, 且 x, y 同号, 设 z = y-x, 则 z >= 0 可以得到 z 的符号位为 0 */
	int x_neg = x>>31;
	int y_neg = y>>31;

	/* 1. x < 0, y >= 0 */
	int case1 = x_neg & !y_neg;

	/* 2. x, y 都不是 0, 且 x, y 同号 */
	int sameSign = !(x_neg ^ y_neg);
	int z = y + ~x + 1;
	int case2 = sameSign & !(z >> 31);
	return ( case1 | case2 );
}
/*
 * ilog2 - return floor(log base 2 of x), where x > 0
 * 求 log2(x), 向下取整
 *   Example: ilog2(16) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 90
 *   Rating: 4
 */
int ilog2(int x) {
	/* 隐含条件, x > 0 */
	/* 参考 https://www.cnblogs.com/tenlee/p/4951639.html 的解释, 本题等价于 */
	/* 判断 x 需要用多少位二进制表示 */
	/* log2(x) = y ---> 2^y = x */
	/* 如 x = 16, 最少需要 5 个 bit 来表示, y = 5 - 1 = 4 */
	/* 16 <= x < 31 时, 都可以用 5 bit 来表示, 而此时的 log2(x) == 4 */
	/* 由此, 问题可以转换为, 寻找 x 的最高有效位的位置 */
	/* 使用【二分法】进行查找 */

	/* m16 = 0xffff 0000, 注意 ~0 == -1, 所以 var + ~0 相当于 var - 1  */
	int m16 = ((1<<16) + ~0) << 16; /* groups of 16 */
	/* m8  = 0xff00 ff00*/
	int m8 = (((1<<8) + ~0) << 24) + (((1<<8) + ~0) << 8); /* groups of 8 */
	/* m8  = 0xf0f0 f0f0 */
	int m4 = (0xf0<<24) + (0xf0<<16) + (0xf0<<8) + 0xf0; /* groups of 4 */
	/* m4  = 0xcccc cccc == 1100 1100 .... 1100(2) */
	int m2 = (0xcc<<24) + (0xcc<<16) + (0xcc<<8) + 0xcc; /* groups of 2 */
	/* m1  = 0xaaaa aaaa == 1010 1010 .... 1010(2) */
	int m1 = (0xaa<<24) + (0xaa<<16) + (0xaa<<8) + 0xaa; /* groups of 1 */

	int result = 0;
	int upper;
	int mask;
	/* m16 */
	/* 若 x 的最高有效位在其高 16 位, 那么 upper = 1 */
	upper = !!(x & m16);
	/* 若 upper == 1, 则 result += 16, 否则 result += 0 */
	result += upper << 4;
	/* 若 upper == 1, 则 mask = 0xffff 0000, 否则 mask = 0x0000 ffff */
	mask = m16 ^ ~((upper<<31)>>31);
	/* 也就是确定下一步要在哪个半区进行查找, 并把另一半置 0 */
	x &= mask;

	/* m8 */
	upper = !!(x & m8);
	/* 若 upper == 1, 则 result += 8, 否则 result += 0 */
	result += upper << 3;
	mask &= (m8 ^ ~((upper<<31)>>31));
	x &= mask;

	/* m4 */
	upper = !!(x & m4);
	/* 若 upper == 1, 则 result += 4, 否则 result += 0 */
	result += upper << 2;
	mask &= (m4 ^ ~((upper<<31)>>31));
	x &= mask;

	/* m2 */
	upper = !!(x & m2);
	/* 若 upper == 1, 则 result += 2, 否则 result += 0 */
	result += upper << 1;
	mask &= (m2 ^ ~((upper<<31)>>31));
	x &= mask;

	/* m1 */
	upper = !!(x & m1);
	/* 若 upper == 1, 则 result += 1, 否则 result += 0 */
	result += upper;

	return result;
}
/* 
 * float_neg - Return bit-level equivalent of expression -f for
 * 设单精度浮点数为 f, 其二进制表示为 ux, 求 -f 的二进制表示
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_neg(unsigned uf) {
	/* 根据 IEEE-754, 单精度浮点数最高位是 符号位, 且符号位独立于后面的 exp(8) 和 frac(23) */
	/* 所以我们只要对 符号位 取反就可以了 */
	/* 另外, 如果 f 是 NaN, 那么还是返回 uf */

	/* mask = 1000 0000 .... 0000 */
	unsigned mask = 1 << 31;
	/* 仅对 ux 最高位取反, [0]^1=1, [1]^1=0, 其他位不变, [0]^0=0, [1]^0=1 */
	unsigned result = uf ^ mask;

	/* 取 f 的绝对值 */
	unsigned absf = uf & !mask;
	if( absf > 0x7F800000 ){
		/* 如果 f 是 NaN, 那么 absf 的 exp 为 1111 1111 (2), 且 frac != 0 */
		/* 即 absf > 0x7F800000 */
		/* 此时另 result = uf */
		result = uf;
	}
	return result;
}
/* 
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 * 实现强制转换 (float) x, 将整数转为浮点数, 并返回其二进制形式
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_i2f(int x) {
	/* 根据 IEEE-754, 单精度浮点数二进制形式为 uf = sign[1] --- exp[8] --- frac[23] */
	/* 获得符号位 */
	unsigned sign = (x < 0);

	/* 获得 x 的绝对值 ax */
	unsigned ax = (x < 0) ? -x : x;

	/* 对于 32-bit int, 最高可能的 E 是 31, 所以 exp = bias + E = 127 + 31 */
	unsigned exp = 127+31;

	/* 由于输入的是 32-bit int, 所以 x 肯定在 norm 区 */
	/* 不会出现 denorm, 也不会出现 special value, 但是可能需要进行 rounding */
	/* 此时 float f = 1.frac[23] * 2^E */
	/* 即最多有 1+23=24 个有效数字 */
	/* residue 是可能需要舍去最低 8 位 */
	unsigned residue;
	unsigned frac = 0;
	if (ax == 0) {
		/* ax 为 0, 那么 f 也是 0, 其二进制也是全 0 */
		exp = 0;
		frac = 0;
	} else {
		/* Normalize so that msb = 1 */
		/* 将 ax 表示为 1.frac[23] * 2^E 的形式, 即科学计数法 */
		/* 把 ax 左移, 直到最高位非 0 */
		while( (ax & (1<<31)) == 0 ){
			ax = ax << 1;
			exp--;
		}
		/* Now have Bit 31 = MSB (becomes implied leading one)
			Bits 8-30 are tentative fraction,
			Bits 0-7 require rounding.
		*/
		/* 取左移之后的 ax 的最低 8 位, 这里 8 位需要进行 rounding */
		residue = ax & 0xFF;
		/* 再把 ax 右移 8 位, 然后取最低 23 位作为 frac */
		frac = (ax >> 8) & 0x7FFFFF;
		if (residue > 0x80 || (residue == 0x80 && (frac & 0x1))) {
			/* Round up, 向上取整 */
			frac++;
			/* Might need to renormalize */
			/* 如果 frac 为全 1, 即 0x7FFFFF, 那么再加 1 会得到 0x800000, 超过 23 位了 */
			/* 产生进位需要把指数位 exp 加 1, 然后把 frac 置 0 */
			if (frac > 0x7FFFFF) {
				frac &= 0x7FFFFF;	// 等价于 frac = 0;
				exp++;
			}
		}
	}
	/* 将 sign[1], exp[8], frac[23] 按 IEEE-754 的顺序组合起来 */
	return (sign << 31) | (exp << 23) | frac;
}
/* TODO
 * float_twice - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 * 输入单精度浮点数 f 的二进制形式 uf, 返回 2*f 的二进制形式
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_twice(unsigned uf) {
	/* 根据 IEEE-754, 单精度浮点数二进制形式为 uf = sign[1] --- exp[8] --- frac[23] */
	/* 获得符号位 sign[1] */
	unsigned sign = (uf >> 31) & 0x01;

	/* 获得 exp[8] */
	unsigned exp = (uf >> 23) & 0xFF;

	/* 获得 frac[23] */
	unsigned frac = uf & 0x7FFFFF;
	if (exp == 0) {
		/* Denormalized.  Must double fraction */
		/* 最小的 norm 的 exp 是 0000 0001 (2) */
		/* 如果 exp == 0000 0000 (2), 说明处于 denorm 区 */
		/* 实现 2*f 的时候首先 2*frac   */
		frac = 2 * frac;
		if (frac > 0x7FFFFF) {
			/* Result normalized */
			/* 如果 frac 超过了 23 位 0x7FFFFF, 说明进行 *2 以后回到了 norm 区 */
			/* 取 frac 的低 23 位 */
			frac = frac & 0x7FFFFF;
			/* 将 exp 置为 0000 0001 (2) */
			exp = 0x01;
		}
		// 如果没有超过 0x7FFFFF, 说明还是在 denorm 区, 不用进行其他操作
	}
	
	else if ( exp < 0xFF ){
		/* Normalized.  Increase exponent */
		/* 如果处于 norm 区, *2 操作相当于对 exp 进行 +1  */
		exp++;
		if (exp == 0xFF) {
			/* Infinity */
			/* 如果 +1 后 exp == 0xff, 说明发生了上溢, 此时 2*f = Inf */
			/* 所以要把 frac 置为 0, 否则就变成了 NaN */
			frac = 0;
		}
	}

	/* Infinity and NaN do not require any changes */
	/* 如果 f 本身就是 Inf 或者 NaN, 则不用进行处理, 直接返回 uf */

	/* 将 sign[1], exp[8], frac[23] 按 IEEE-754 的顺序组合起来 */
	return (sign << 31) | (exp << 23) | frac;
}
