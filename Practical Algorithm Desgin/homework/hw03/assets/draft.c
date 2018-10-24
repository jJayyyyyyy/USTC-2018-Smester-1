/*
精确测量时间

1.	C, 跨平台, ms(millisecond)

	https://www.gnu.org/software/libc/manual/html_node/CPU-Time.html#CPU-Time
	
	```c
	#include <time.h>
	clock_t start, end;
	double cpu_time_used;
	
	start = clock();
	
	// do something
	for(int i = 0; i < 0x3fffff0; i++){}
	
	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	```

2.	C, Windows, us(microsecond)

	https://msdn.microsoft.com/en-us/library/windows/desktop/ms644905(v=vs.85).aspx

	QPF获取CPU频率 freq, QPC获取当前tick

	(end_tick - start_tick) / freq = elapsed 秒,  x10^6, 就是以 us 的形式显式

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

	int main(){
		long long starttime = GetCPUTime();

		// do something
		for(int i = 0; i < 0x3fffff0; i++){}
		
		
		long long endtime = GetCPUTime();
		long long elapsed =  endtime - starttime;
		printf_s("%ld\n", elapsed);
		return 0;
	}
	```

3.	C++11, 跨平台, us(microsecond)

	https://stackoverflow.com/questions/23615776/measure-time-milliseconds-or-microseconds-for-windows-c
	https://en.cppreference.com/w/cpp/chrono
	https://en.cppreference.com/w/cpp/chrono/high_resolution_clock/now

	```cpp
	#include <iostream>
	#include <chrono>
	#include <iomanip>
	using namespace std;

	int main(){
		auto start = chrono::high_resolution_clock::now();
		
		for(int i = 0; i < 0x3fffff0; i++){}
		
		auto end = chrono::high_resolution_clock::now();
		
		chrono::duration<double> elapsed = (end-start);
		cout<<setprecision(9)<<elapsed.count()<<'\n';   // 在我的PC上可以精确到 0.1us, 更高的精度则依机器和系统而定
	}
	```
*/



/*
复杂度分析

https://stackoverflow.com/questions/2327244/complexity-of-recursive-factorial-program/6195662
关于 facto 的复杂度, 假设每个操作只需要 O(1) 的时间, 那么
时间 T(n) = T(n-1) + O(1) = ... = O(n)

https://www.cnblogs.com/python27/archive/2011/12/09/2282486.html#commentform
f(n) = n * f(n-1)
可以理解为
tmp = f(n-1);       // T(n-1)
result = n * tmp;   // n很小的时候是 O(1), n很大的时候可能是 O(lg n)


T(n) = T(n-1) + O(1)

空间
S(n) = O(n)			// 栈的深度为n

*/


/*
在线画图

[online plot, Desmos](https://www.desmos.com/calculator)

[online plot, plot.ly](https://plot.ly/create/#/)

*/

/*
图表数据

10, 512
20, 1952
30, 4486
40, 8356
50, 14199
60, 20364
70, 27176
80, 36194
90, 45894
100, 60613

*/


/*
// 非递归, 保存状态
double factoList[32] = {0};

double factoNoRecur(int n){
	if( n <= 1 ){
		factoList[n] = 1;
		return 1;
	}

	double res = n * factoList[n-1];
	factoList[n] = res;
	return res;
}

double sumFacto(int n){
	double sum = 0;
	for( int i = 1; i <= n; i++ ){
		sum += factoList[i];
	}
	return sum;
}

*/

/*
int main(){
	long long starttime, endtime, elapsed;
	double sum;
	int n = 40;
	starttime = GetCPUTime();
	for( int i = 0; i < 1000; i++ ){
		sum = sumFacto(n);
	}
	endtime = GetCPUTime();
	elapsed =  endtime - starttime;
	// cout<<"n: "<<n<<'\n';
	// cout<<"elapsed: "<<elapsed<<'\n';
	cout<<"("<<n<<", "<<elapsed<<")\n";
	return 0;
}

// int main(){
// 	auto start = chrono::high_resolution_clock::now();

// 	for( int i = 0; i < 0x3fffff0; i++ ){}

// 	auto end = chrono::high_resolution_clock::now();

// 	chrono::duration<double> elapsed = (end-start);
// 	cout<<elapsed.count()<<'\n';
// }

*/