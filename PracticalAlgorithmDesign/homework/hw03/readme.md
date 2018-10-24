##	作业3(课后)

*	开发环境：

	*	Windows
	*	Visual Studio
	*	C 语言

*	作业内容与要求：

	```
	编写一个递归结构的程序，求1！+2！+3！+4！+…+20！的值。

	要求：
	1）写出该递归程序的算法设计思路（先按照输入规模从小到大进行枚举，然后推导出一个通用的递归数学表达式）;
	2）实现其C代码.
	3）估算算法的近似时间复杂度（假设输入规模为n时）；
	4）通过实验验证前面估算的近似时间复杂度是否正确.
	注意：
	1）Sum使用double类型，以尽量降低函数值溢出的可能性。
	2）由于阶乘的和随着规模的增长过快，因此用来测试实际时间与规模的相关关系时，可以：
	统计不同规模下计算函数值1000次的时间开销，并且将GetCPUTime()的精度改为1微秒，
	以便更容易观察实际时间与规模之间的规律。你可以分别尝试规模n为20,30,40,50,60，……；
	3)注意，对比观察不同规模下的实际时间开销时，需采用release模式
	```

	<br>

##	分析与解答

1.	求阶乘的累加和 `1! + 2! + ... + 20!`

	*	求阶乘 `n!`

		思路: `n! = n * (n-1)!`, 即 `f(n) = n * f(n-1)`, 当 `n = 1` 时, `f(n) = 1`, 于是可以得到如下的递归求阶乘 `n!` 的代码

		```c
		double facto(int n){
			if( n <= 1 ){
				return 1;
			}
			
			double res = facto(n-1);
			return n * res;
		}
		```

	*	求和

		```c
		double sumFacto(int n){
			double sum = 0;
			for( int i = 1; i <= n; i++ ){
				sum += facto(i);
			}
			return sum;
		}
		```

2.	复杂度分析

	*	时间复杂度

		对于 `facto()`, 假设每个操作只需要 `O(1)` 的时间, 那么

		```c
		tmp = f(n-1);       // T(n-1)
		result = n * tmp;   // 根据参考资料1, 在 n 很小的时候乘法是 O(1), n 很大的时候可能达到 O(lg n)
		
		// 所以
		T(n) = T(n-1) + O(1) = ... = O(n)
		```

		对于 `sumFacto()`,

		```
		Tsum(n) = Tfacto(1) + Tfacto(2) + ... + Tfacto(n)
		        = O(1) + O(2) + ... + O(n)
		        = O(n^2)
		```

		因此 阶乘的累加和 `1! + 2! + ... + 20!` 的时间复杂度为 `O(n^2)`

	*	空间复杂度

		递归所用栈的深度为 `n`

		所以空间复杂度为 `S(n) = O(n)`

3.	验证时间复杂度

	*	首先根据先前的作业, 定义时间度量函数 `GetCPUTime()`, 精度为 `1 us`

	*	然后, 记录当前时间 `starttime`, 进行 `1000` 次的 `sumFacto(n)`, 再记录当前时间 `endtime`, 这样, `elapsed = endtime - starttime` 就可以得出 `1000` 次 `sumFacto(n)` 消耗的时间

		代码如下

		```c
		#include <stdio.h>
		#include <windows.h>

		//获取当前时间，精度1微秒
		long GetCPUTime(){
			static LARGE_INTEGER li = {0};
			LARGE_INTEGER linow = {0};
			if (li.QuadPart == 0){
				QueryPerformanceFrequency(&li);
			}
			QueryPerformanceCounter(&linow);
			return linow.QuadPart * 1000000 / li.QuadPart;
		}

		double facto(int n){
			if( n <= 1 ){
				return 1;
			}
			double res = facto(n-1);
			return n * res;
		}

		double sumFacto(int n){
			double sum = 0;
			for( int i = 1; i <= n; i++ ){
				sum += facto(i);
			}
			return sum;
		}

		void getTimeConsumption(){
			printf("n = 10, 20, ..., 60 时, 执行 1000次 sumFacto(n) 的时间开销 (us)\n");
			long long starttime, endtime, elapsed;
			double elapsedList[12] = {0};
			int n;
			for( n = 10; n <= 100; n += 10 ){
				starttime = GetCPUTime();
				double sum = 0;
				for( int i = 0; i < 1000; i++ ){
					sum = sumFacto(n);
				}
				endtime = GetCPUTime();
				elapsed =  endtime - starttime;
				elapsedList[n/10] = elapsed;
				printf("%d, %lld\n", n, elapsed);
			}
		}

		int main(){
			double sum = sumFacto(20);
			printf("1! + 2! + ... + 20! = %lf\n\n", sum);
			
			getTimeConsumption();
			return 0;
		}
		```

	*	最后, 将数据用图表的形式表现出来, 如图所示(图表使用 `Desmos` 绘制)

		![result](https://github.com/jJayyyyyyy/USTC-2018-Smester-1/blob/master/PracticalAlgorithmDesign/homework/hw03/assets/result.png)

		从中我们可以看到, 在 `n<=40` 时, 数据点的分布大致符合 `O(n^2)` 的时间复杂度, 而 `n` 更大时, `sumFacto(n)` 的增长速度超过了 `O(n^2)`, 根据参考资料1, 这可能是由于 n 过大时, `result = n * tmp;` 的时间复杂度从 `O(1)` 变成了 `O(lgn)`, 从而使总的时间复杂度提升到了 `O(n^2 * lgn)`,

	<br>

##	参考资料

*	[Complexity of recursive factorial program, Stack Overflow](https://stackoverflow.com/questions/2327244/complexity-of-recursive-factorial-program/6195662)

*	精确测量时间

	*	[C, Windows, us(microsecond)](https://msdn.microsoft.com/en-us/library/windows/desktop/ms644905(v=vs.85).aspx)

	*	[C++11, 跨平台, us(microsecond)](https://stackoverflow.com/questions/23615776/measure-time-milliseconds-or-microseconds-for-windows-c)

	*	[C++11, Chrono](https://en.cppreference.com/w/cpp/chrono)

*	[在线绘图, online plot, Desmos](https://www.desmos.com/calculator)
