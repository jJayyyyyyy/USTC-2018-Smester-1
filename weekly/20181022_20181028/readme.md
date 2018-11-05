时间: 20181022 ~ 20181028

##	新闻

*	[Alphabet’s Waymo begins charging passengers for self-driving cars](https://www.ft.com/content/7980e98e-d8b6-11e8-a854-33d6f82e62f8)

	[全球首例！谷歌无人车开始商用，自动驾驶时代到了](http://www.sohu.com/a/271621177_115978)

	Google 的无人车开始进行商用(收费)测试

*	[PNG 格式联合设计者去世](https://www.solidot.org/story?sid=58351)

<br>

##	资源推荐

*	[知乎: 为什么 Python 不支持函数重载？其他函数大部分都支持的？](https://www.zhihu.com/question/20053359)

*	精确测量时间

	*	c, 跨平台, ms(millisecond)

		https://www.gnu.org/software/libc/manual/html_node/CPU-Time.html#CPU-Time

		```c
		#include <time.h>
		clock_t start, end;
		double cpu_time_used;

		start = clock();
		// do something
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		```

	*	c, Windows, us(microsecond)

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

	*	C++11, 跨平台, us(microsecond)

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

*	[online plot, Desmos](https://www.desmos.com/calculator)

	[online plot, plot.ly](https://plot.ly/create/#/)

<br>

##	其他

*	TODO

	本周 `CSAPP` 的实验 `datalab2 --- bomb` 要用到 `GDB`, 最后一个隐藏的 `secret_phase` , 虽然在分析完外部的汇编代码后可以得出输入的范围是 `[1, 1001]` 的整数, 
	
	但是用于具体确定输入合法性的 `fun7()` 非常麻烦, 我在想能不能通过 `brute force` 的方法进行定位, 不过 `[1, 1001]` 的范围对于手动尝试来说还是太耗时了, 所以需要使用自动化工具

	[用 Python 拓展 GDB](https://segmentfault.com/a/1190000005718889)
	
	[How to import 'GDB' in Python](https://stackoverflow.com/questions/4792483/how-to-import-gdb-in-python)

	搜索关键词是 `python gdb`, 以后有时间了来实现一个自动化脚本

*	[How To Get Thousands of Stars on Your Github Project](https://blog.cwrichardkim.com/how-to-get-hundreds-of-stars-on-your-github-project-345b065e20a2)

*	[How to add GIFs to your GitHub README](https://medium.com/@josephcardillo/how-to-add-gifs-to-your-github-readme-89c74da2ce47)

*	Python

	```python
	s1 = [2, 1, 4, 3]
	s2 = ['c', 'a', 'b']
	s3 = s1 + s2[-1]    # TypeError: can only concatenate list (not "str") to list
	```

*	docker 与 host 之间传送文件

	[Copying files from host to Docker container](https://stackoverflow.com/questions/22907231/copying-files-from-host-to-docker-container)

	[Docker CLI docs for cp](https://docs.docker.com/engine/reference/commandline/cp/)

	```bash
	$ docker cp foo.txt mycontainer:/notebooks/foo.txt
	$ docker cp mycontainer:/notebooks/foo.txt foo.txt
	```

<br>