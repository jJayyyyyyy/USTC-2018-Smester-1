##	程序设计与计算机系统第三章作业

3.58 3.60 3.63 3.69 3.70

*	3.58

	```c
	// x--rdi, y--rsi, z--rdx
	long decode2(long x, long y, long z){
		y -= z;
		x *= y;
		long res = y;
		res <<= 63;
		res >>= 63;
		res ^= x;
		return res;
	}
	```

	<br>

*	3.60

	*	A.	`x` 存放于 `%rdi` 寄存器

		`n` 存放于 `%esi` 寄存器

		`result` 存放于 `%eax` 寄存器

		`mask` 存放于 `%rdx` 寄存器

	*	B.	`result` 初始化为 `0`, `mask` 初始化为 `1`

	*	C.	判断条件为 `mask != 0`

	*	D.	`mask = mask << (n&0xff);`

	*	E.	`result |= (x & mask);`

	*	F.	`C` 代码

		```c
		long loop(long x, long n){
			long result = 0;
			long mask;
			mask = 1;
			for( mask = 1; mask != 0; mask = mask << (n&0xff) ){
				result |= (x & mask);
			}
			return result;
		}
		```

	<br>

*	3.63

	`switch` 中需要填充的 `body` 如下

	```c
	case 60:
	case 62:
		result = x * 8;
		break;
	case 63:
		result >>= 3;
		break;
	case 64:
		result <<= 4;
		result -= x;
		x = result;
	case 65:
		x *= x
	default:
		result = 0x4b + x;
	```

	<br>

*	3.69

	*	A. `CNT=7`

	*	B.

		```c
		typedef struct {
			long idx;
			long x[4];
		} a_struct;
		```

	<br>

*	3.70

	`proc()` 的代码如下

	```c
	void proc(union ele *up){
		up->e2.x = *(up->e2.next->e1.p) - up->e2.next->e1->y;
	}
	```

<br><br>

##	解题过程与分析

*	题源: `CSAPP` 第3版第3章

	书中的这个表格很有帮助, 放在这里以便参照

	![operand forms](https://github.com/jJayyyyyyy/USTC-2018-Smester-1/blob/master/CSAPP/homework/hw02/assets/OperandFroms.jpg)

	<br>

*	3.58 For a function with prototype

	```c
	long decode2(long x, long y, long z);
	```

	GCC generates the following assembly code:

	```asm
	1	decode2:
	2	    subq	%rdx, %rsi
	3	    imulq	%rsi, %rdi
	4	    movq	%rsi, %rax
	5	    salq	$63, %rax
	6	    sarq	$63, %rax
	7	    xorq	%rdi, %rax
	8	    ret
	```

	Parameters `x, y, z` are passed in registers `%rdi, %rsi, %rdx`. The code stores the return value in register `%rax`.

	Write C code for `decode2` that will have an effect equivalent to the assembly code shown.

	```c
	#include <stdio.h>

	/*
	// x=1, y=2, z=3
	long decode2(long x, long y, long z){
		y -= z;			// y = -1
		x *= y;			// x = -1
		long res = y;		// res = -1 = 0xffffffff ffffffff
		res <<= 63;		// res = 0x80000000 0000000 = (1000 .... 0000) 2
		res >>= 63;		// res = (1111 .... 1111) 2 = 0xffffffff ffffffff = -1
		res ^= x;		// res = 0
		return res;
	}
	*/

	// x=5, y=4, z=2
	long decode2(long x, long y, long z){
		y -= z;				// y = 2 = (0010) 2
		x *= y;				// x = 10 = (1010) 2
		long res = y;			// res = 2 = 0x0010
		res <<= 63;			// res = 0
		res >>= 63;			// res = (0000) 2
		res ^= x;			// res = (1010) 2
		return res;
	}

	// 要么 x-1, 要么 x*2
	int main(){
		// long x = 1, y = 2, z = 3;
		long x = 11, y = 4, z = 2;
		printf("%ld\n", decode2(x, y, z));

		return 0;
	}
	```

	<br>

*	3.60 Consider the following assembly code

	```asm
	# long loop(long x, int n)
	# x in %rdi, n in %esi
	loop:
		movl	%esi, %ecx
		movl	$1, %edx
		movl	$0, %eax
	.L3:
		movq	%rdi, %r8
		andq	%rdx, %r8
		orq	%r8, %rax
		salq	%cl, %rdx		# cl is lowest 8-bit of ecx
		
	.L2:
		testq	%rdx, %rdx
		jne	.L3
		rep; ret
	```

	回答问题并写出 `loop` 对应的 `C` 代码

	*	A. Which registers hold program values x, n, result, and mask?
	*	B. What are the initial values of result and mask?
	*	C. What is the test condition for mask?
	*	D. How does mask get updated?
	*	E. How does result get updated?
	*	F. Fill in all the missing parts of the C code.

	```c
	/*
	// 汇编直接翻译过来就是下面这段代码
	loop:
		long size = n;
		long mask = 1;
		result = 0;
	L3
		long tmp = x;
		tmp &= 1;
		sum |= tmp;
		i <<= (n&0xff);
	L2
		if( i != 0 ){
			goto L3
		}else{
			return sum
		}
	*/

	// 改写成与函数 loop 一致的形式
	long loop(long x, long n){
		long result = 0;
		long mask;
		mask = 1;
		for( mask = 1; mask != 0; mask = mask << (n&0xff) ){
			// long tmp = x;
			// tmp &= mask;
			// result |= tmp;
			result |= (x & mask);
		}
		return result;
	}
	```

	<br>

*	3.63 题目略

	注: 英文版的书, 3.63 的题目中间夹了一个 3.62 的题图, 注意区分

	思路: 题目已经帮我们找好了 `Jump Table` 的入口地址 `Ox4006f8`, 里面有 `6` 个 `target`, 对应 6 个 `case` 的入口地址

	```c
	long switch_prob(long x, long n){
		long result = x;			// 5aa, 5b2
		int n1 = n - 0x3c;
		switch(n1){
			case 0:				// goto 5a1
			case 2:				// goto 5a1
				result = x * 8;		// 5a1
				break;			// 5a8
			case 3:				// goto 5aa
				// result = x;		// 5aa
				result >>= 3;		// 5ad
				break;			// 5b1
			case 4:				// goto 5b2
				// result = x;		// 5b2
				result <<= 4;		// 5b5
				result -= x;		// 5b9
				x = result;		// 5bc
			case 5:				// goto 5bf
				x *= x			// 5bf
			default:			// goto 5c3
				result = 0x4b + x;	// 5c3
		}
		return result;				// 5c7
	}

	// 精简之后
	long switch_prob(long x, long n){
		long result = x;
		switch(n){
			case 60:			// 0x3c == 60
			case 62:
				result = x * 8;
				break;
			case 63:
				result >>= 3;
				break;
			case 64:
				result <<= 4;
				result -= x;
				x = result;
			case 65:
				x *= x
			default:
				result = 0x4b + x;
		}
		return result;
	}
	```

	<br>

*	3.69 题目大致意思如下

	有这么一个结构体, 还有一段测试函数

	```c
	typedef struct{
		int first;
		a_struct a[CNT];
		int last;
	} b_struct;

	void test(long i, b_struct * bp){
		int n = bp->first + bp->last;
		a_struct * ap = & bp->a[i];
		ap->x[ap->idx] = n;
	}
	```

	其中, 我们不知道 `a_struct` 的内部结构如何。但是我们有测试函数的 `.o` 文件, 对其使用 `objdump` 我们可以得到如下的反汇编代码

	```asm
	void test(long o, b_struct *bp)
	i in %rdi, bp in %rsi
	1	0000000000000000 <test>:
	2		0:	8b 8e 20 01 00 00   mov   	0x120(%rsi), %ecx
	3		6:	03 Oe               add   	(%rsi), %ecx
	4		8:	48 8d 04 bf         lea   	(%rdi,%rdi,4), %rax
	5		c:	48 8d 04 c6         lea   	(%rsi,%rax,8), %rax
	6		10:	48 8b 50 08         mov   	Ox8(%rax), %rdx
	7		14:	48 63 c9            movslq	%ecx,%rcx
	8		17:	48 89 4c dO 10      mov   	%rcx, Ox10(%rax,%rdx,8)
	9		1c:	c3                  retq
	```

	题目要求我们通过逆向工程, 分析出 `CNT` 的值, 以及 `a_strcut` 的具体结构。假设 `a_strcut` 中只有 `idx, x` 这两个字段, 且它们都是有符号数

	<br>

	分析汇编代码并结合 `b_struct` 与 `test()`, 可以得到如下过程

	```asm
	# R(%rdi) = i, R(%rsi) = bp

	mov     0x120(%rsi), %ecx             # R(%ecx) = M[288 + R(%rsi)]
	                                      #         = M[288 + bp]
	                                      #         = last
	                                      #
	add     (%rsi), %ecx                  # R(%ecx) = R(%ecx) + M[R(%rsi)]
	                                      #         = bp->last + M[bp]
	                                      #         = bp->last + bp->first
	                                      #         = n
	                                      #
	                                      #
	lea     (%rdi,%rdi,4), %rax           # R(%rax) = lea( M[R(%rdi) * 5] )
	                                      #         = R(%rdi) * 5
	                                      #         = i*5
	                                      #           (lea相当于取地址)
	                                      # 
	lea     (%rsi,%rax,8), %rax           # R(%rax) = R(%rsi) + R(%rax) * 5
	                                      #         = bp + i*40
	                                      #
	                                      #
	mov     Ox8(%rax), %rdx               # R(%rdx) = M[ 8 + R(%rax) ]
	                                      #         = M[ 8 + bp + i*40 ]
	                                      # 
	                                      # 推测
	                                      # ap = R(%rdx)
	                                      # bp 是 first 的首地址
	                                      # (bp + 4) ~ (bp + 8) 是用于对其的 padding
	                                      # bp + 8 是数组 bp->a 的首地址
	                                      # i * 40 说明一个元素占40个字节
	                                      # 
	                                      # 由于 bp + 288 是 last 的首地址
	                                      # 所以 a[CNT] 一共占据 (288 - 8) = 280 个字节
	                                      # 所以 CNT = 280 / 40 = 7
	                                      # 
	                                      # 再进行化简
	                                      # 8 + bp + i*40 就是 ap 的起始地址
	                                      # 所以 
	                                      # R(%rdx) = M[ap]
	                                      #         = *ap
	                                      # 
	movslq  %ecx,%rcx                     # R(%rcx) = n
	                                      # 
	mov     %rcx, Ox10(%rax,%rdx,8)       # M[16 + R(%rax) + R(%rdx)*8] = n
	                                      # M[8 + 8 + bp + i*40 + R(%rdx)*8] = n
	                                      # 其中 8 + bp + i*40 就是 ap 的起始地址, 所以
	                                      # M[8 + ap + R(%rdx)*8] = n
	                                      # M[ap + 8 + M[ap]*8] = n
	                                      # 结合题目, 推测
	                                      # ap + 8 是数组 ap->x 的起始地址
	                                      # 数组 ap->x 的每个元素大小为 8 字节
	                                      # M[ap] = ap->idx, idx 大小为 8 字节
	                                      # 这样, M[ap + 8 + M[ap]*8] 就对应了 ap->x[ap->idx]
	                                      # 最后, 由于每个元素占 40 字节
	                                      # 所以 数组 ap->x 的大小为
	                                      # (40 - 8)/8 = 4
	retq
	```

	所以

	*	A. `CNT = 7`

	*	B.

		```c
		typedef struct {
			long idx;
			long x[4];
		} a_struct;
		```

	<br>

*	3.70 Consider the following union declaration:

	```c
	union ele {
		struct {
			long *P;
			long y;
		} e1;
		struct {
			long x;
			union ele *next;
		} e2;
	};
	```

	This declaration illustrates that structures can be embedded within unions.

	The following function (with some expressions omitted) operates on a linked list having these unions as list elements:

	```c
	void proc (union ele *up) {
		up->_______ = *(________) - __________;
	}
	```

	*	A. What are the offsets (in bytes) of the following fields:

		*	e1.p -> 0
		*	e1.y -> 8
		*	e2.x -> 0
		*	e2.next -> 8

	*	B. How many total bytes does the structure require?

		8 + 8 = 16

	*	C. The compiler generates the following assembly code for proc:

		```asm
		# void proc (unibn ele *up)
		# up in %rdi

		1.  proc:
		2.    movq    8(%rdi), %rax
		3.    movq    (%rax), %rdx
		4.    movq    (%rdx), %rdx
		5.    subq    8(%rax), %rdx
		6.    movq    %rdx, (%rdi)
		7.    ret
		```

		On the basis of this information, fill in the missing expressions in the code for proc. Hint: Some union references can have ambiguous interpretations, These ambiguities get resolved as you see where the references lead, There is only one answer that does not perform any casting and does not violate any type constraints.

	*	分析汇编代码

		```asm
		# void proc (unibn ele *up)
		# up in %rdi

		1.  proc:
		2.    movq    8(%rdi), %rax    # R(%rax) = M[8 + R(%rdi)]
		                               #         = M[8 + up]
		                               # 右边的值是
		                               # up->e1.y 或
		                               # up->e2.next
		                               #
		                               #
		3.    movq    (%rax), %rdx     # R(%rdx) = M[R(%rax)]
		                               # 由这里的 M[], 可以推测 R(%rax) 是地址, 所以
		                               # R(%rax) = up->e2.next
		                               # R(%rdx) = up->e2.next->e1.p 或
		                               # R(%rdx) = up->e2.next->e2.x
		                               #
		4.    movq    (%rdx), %rdx     # R(%rdx) = M[R(%rdx)]
		                               # 同样由 M[], 可以推测 R(%rdx) 是地址, 所以
		                               # R(%rdx) = up->e2.next->e1.p, 然后
		                               # R(%rdx) = M[R(%rdx)]
		                               #         = *(up->e2.next->e1.p)
		                               #
		5.    subq    8(%rax), %rdx    # R(%rdx) = R(%rdx) - M[8 + R(%rax)]
		                               #         = R(%rdx) - M[8 + up->e2.next]
		                               # 由于 R(%rdx) 是数值, 所以 M[8 + up->e2.next] 也是数值, 不是地址,
		                               # 否则会产生 casting
		                               # 所以 M[8 + up->e2.next] = up->e2.next->e1->y
		                               # 
		                               # R(%rdx) = R(%rdx) - up->e2.next->e1->y
		                               #
		                               #
		6.    movq    %rdx, (%rdi)     # M[R(%rdi)] = R(%rdx)
		                               # 由于右边是一个数值, 不是地址, 所以左边也是数值,
		                               # 否则会产生 casting
		                               # 左边 = up->e2.x
		                               # 右边 = *(up->e2.next->e1.p) - up->e2.next->e1->y
		                               #
		7.    ret
		```

		因此可以得到 `proc()` 的代码如下

		```c
		void proc(union ele *up){
			up->e2.x = *(up->e2.next->e1.p) - up->e2.next->e1->y;
		}
		```

	<br>

##	参考资料

*	[salq is a left-shift, sarq is an arithmetic right shift](https://www.reddit.com/r/learnprogramming/comments/3na5r9/assembly_x86_64_question_salq_sarq/)

*	[subq, asm64-handout](https://www.cs.cmu.edu/~fp/courses/15213-s07/misc/asm64-handout.pdf)

*	[Registers, x64 Cheat Sheet](https://cs.brown.edu/courses/cs033/docs/guides/x64_cheatsheet.pdf)

*	[csapp-3e-solutions](https://dreamanddead.gitbooks.io/csapp-3e-solutions/)

*	[CSAPP](https://book.douban.com/subject/26344642/)

*	[CSAPP homepage, CMU, CS-15-213](https://www.cs.cmu.edu/~213/)
