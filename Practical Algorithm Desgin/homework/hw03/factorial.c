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

// 递归求阶乘
double facto(int n){
	if( n <= 1 ){
		return 1;
	}
	double res = facto(n-1);
	return n * res;
}

/*
求前 n 项的和
n <= 15
Σ(i, n) [O(i)] = O(n^2)
*/
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

	/* 忽略, 因为 n 很小时, 执行时间变化占比大, 不适用于做基数
	直接找曲线去拟合上面的数据就好了
	printf("\n标准化\n");

	for( int i = 2; i <= 6; i++ ){
		elapsedList[i] /= elapsedList[1];
	}
	elapsedList[1] = 1;
	for( int i = 1; i <= 6; i++ ){
		printf("%d, %lf\n", i, elapsedList[i]);
	}
	*/
}

int main(){
	double sum = sumFacto(20);
	printf("1! + 2! + ... + 20! = %lf\n\n", sum);
	
	getTimeConsumption();
	return 0;
}
