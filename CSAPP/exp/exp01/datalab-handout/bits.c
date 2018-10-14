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
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
int bitAnd(int x, int y) {
	return ~( ~x | ~y );
}
/* 
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int getByte(int x, int n) {
	/* Shift x n*8 positions right */
	int shift = n << 3;
	int xs = x >> shift;
	/* Mask byte */
	return xs & 0xFF;
}
/* 
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3 
 */
int logicalShift(int x, int n) {
	/* Create mask for n = 0 */
	// n == 0 的时候特殊处理，因为 x<<32 似乎是个 undefined behavior, VS 和 gcc 上跑出来的结果不一样
	int zmask = (!n);
	/* Arithmetic shift right by n */
	int right = x >> n;
	
	/* Mask off upper 1's */
	int lmask = (~0) << (33 + ~n);	// 33 + ~n = 32 + ~n + 1 = 32 - n
	lmask &= ~((zmask<<31)>>31);
	// 如果 n = 0, 那么 zmask = 1, lmask = 0 & lmask = 0
	// 如果 n != 0, 那么 zmask = 0, lmask = 0xffff ffff & lmask
	// 更多测试用例可见 ./btest
	
	right &= ~lmask;
	return right;
}
/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int bitCount(int x) {
	/* Sum 8 groups of 4 bits each */
	int m1 = 0x11 | (0x11 << 8);
	int mask = m1 | (m1 << 16);
	int s = x & mask;
	s += x>>1 & mask;
	s += x>>2 & mask;
	s += x>>3 & mask;
	/* Now combine high and low order sums */
	s = s + (s >> 16);
	/* Low order 16 bits now consists of 4 sums,
		each ranging between 0 and 8.
		Split into two groups and sum */
	mask = 0xF | (0xF << 8);
	s = (s & mask) + ((s >> 4) & mask);
	return (s + (s>>8)) & 0x3F; // 0x3f 去掉高位可能存在的1
}
/* 
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int bang(int x) {
	int minus_x = ~x + 1;
	/* Cute trick: 0 is the only value of x
	* for which neither x nor -x are negative */
	return (~(minus_x | x) >> 31) & 1;
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
	return 1 << 31;
}
/* 
 * fitsBits - return 1 if x can be represented as an 
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n) {
	int shift = 32 + ~n + 1;
	int move = (x << shift) >> shift;
	return !(x ^ move);
}
/* TODO
 * divpwr2 - Compute x/(2^n), for 0 <= n <= 30
 *  Round toward zero
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
		int mask = (1 << n) + ~0;
		int bias = (x >> 31) & mask;
		return (x+bias) >> n;
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
	return ~x + 1;
}
/* 
 * isPositive - return 1 if x > 0, return 0 otherwise 
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 3
 */
int isPositive(int x) {
	return !((!x) | (x >> 31));
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
	int x_neg = x>>31;
	int y_neg = y>>31;
	return (   ( x_neg & !y_neg ) | (  !(x_neg ^ y_neg) & !( (y+~x+1)>>31 )  )   );
}
/* TODO
 * ilog2 - return floor(log base 2 of x), where x > 0
 *   Example: ilog2(16) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 90
 *   Rating: 4
 */
int ilog2(int x) {
	int m16 = ((1<<16) + ~0) << 16; /* groups of 16 */
	int m8 = (((1<<8) + ~0) << 24) + (((1<<8) + ~0) << 8); /* groups of 8 */
	int m4 = (0xf0<<24) + (0xf0<<16) + (0xf0<<8) + 0xf0; /* groups of 4 */
	int m2 = (0xcc<<24) + (0xcc<<16) + (0xcc<<8) + 0xcc; /* groups of 2 */
	int m1 = (0xaa<<24) + (0xaa<<16) + (0xaa<<8) + 0xaa; /* groups of 1 */
	int result = 0;
	int upper;
	int mask;
	/* m16 */
	upper = !!(x & m16);
	result += upper << 4;
	mask = m16 ^ ~((upper<<31)>>31);
	/* m8 */
	upper = !!(x & m8 & mask);
	result += upper << 3;
	mask &= (m8 ^ ~((upper<<31)>>31));
	/* m4 */
	upper = !!(x & m4 & mask);
	result += upper << 2;
	mask &= (m4 ^ ~((upper<<31)>>31));
	/* m2 */
	upper = !!(x & m2 & mask);
	result += upper << 1;
	mask &= (m2 ^ ~((upper<<31)>>31));
	/* m1 */
	upper = !!(x & m1 & mask);
	result += upper;
	return result;
}
/* 
 * float_neg - Return bit-level equivalent of expression -f for
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
	unsigned mask = 1 << 31;
	unsigned result = uf ^ mask;
	unsigned abs = uf & !mask;
	if (abs > 0x7F800000){
		/* NaN */
		result = uf;
	}
	return result;
}
/* 
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_i2f(int x) {
	unsigned sign = (x < 0);
	unsigned ax = (x < 0) ? -x : x;
	unsigned exp = 127+31;
	unsigned residue;
	unsigned frac = 0;
	if (ax == 0) {
		exp = 0;
		frac = 0;
	} else {
		/* Normalize so that msb = 1 */
		while ((ax & (1<<31)) == 0) {
			ax = ax << 1;
			exp--;
		}
		/* Now have Bit 31 = MSB (becomes implied leading one)
			Bits 8-30 are tentative fraction,
			Bits 0-7 require rounding.
		*/
		residue = ax & 0xFF;
		frac = (ax >> 8) & 0x7FFFFF; /* 23 bits */
		if (residue > 0x80 || (residue == 0x80 && (frac & 0x1))) {
			/* Round up */
			frac ++;
			/* Might need to renormalize */
			if (frac > 0x7FFFFF) {
				frac = (frac >> 1) & 0x7FFFFF;
				exp++;
			}
		}
	}
	return (sign << 31) | (exp << 23) | frac;
}
/* TODO
 * float_twice - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_twice(unsigned uf) {
	unsigned sign = (uf >> 31) & 0x01;
	unsigned exp = uf>>23 & 0xFF;
	unsigned frac = uf & 0x7FFFFF;
	if (exp == 0) {
		/* Denormalized.  Must double fraction */
		frac = 2*frac;
		if (frac > 0x7FFFFF) {
			/* Result normalized */
			frac = frac & 0x7FFFFF; /* Chop off leading bit */
			exp = 1;
		}
	} else if (exp < 0xFF) {
		/* Normalized.  Increase exponent */
		exp++;
		if (exp == 0xFF) {
			/* Infinity */
			frac = 0;
		}
	}
	/* Infinity and NaN do not require any changes */
	return (sign << 31) | (exp << 23) | frac;
}
