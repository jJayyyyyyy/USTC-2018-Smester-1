##	CSAPP第一次实验(datalab1)

*	实验环境

	*	Ubuntu 16.04
	*	gcc 4.8.4

	*	注1: 使用 `./dlc bits.c` 进行语法检查时, 可能会提示 `No such file or directory # include <sys/cdefs.h>`, 根据[参考链接1](https://askubuntu.com/questions/470796/fatal-error-sys-cdefs-h-no-such-file-or-directory), 需要安装额外的库文件

		```bash
		$ sudo apt-get --reinstall install libc6 libc6-dev
		```

	*	注2: 使用 `./dlc bits.c` 进行语法检查时, 可能会提示关于 `stdc-predef.h` 的 `warning`, 根据[参考链接2](https://courses.cs.washington.edu/courses/cse351/16wi/lab-1.html)

		> Note: dlc will always output the following warning, which can be ignored:
		> /usr/include/stdc-predef.h:1: Warning: Non-includable file <command-line> included from includable file /usr/include/stdc-predef.h.

	*	注3: 在 x64 机器运行时, 需要对 `Makefile` 进行如下修改

		```makefile
		# CFLAGS = -O -Wall -m32
		# ===>
		CFLAGS = -O -Wall -m64
		```

*	实验内容

	使用有限的位操作符完成指定功能的函数。

*	实验代码

	由于代码及注释内容较多，所以仍然存放为文件 `bits.c`

*	运行结果截图

	![csapp_exp1_result](https://github.com/jJayyyyyyy/USTC-2018-Smester-1/blob/master/CSAPP/exp/exp01/assets/csapp_exp1_result.png)

##	参考资料

*	[No such file or directory # include <sys/cdefs.h>, askubuntu](https://askubuntu.com/questions/470796/fatal-error-sys-cdefs-h-no-such-file-or-directory)

*	[Warning: Non-includable file <command-line> included from includable file /usr/include/stdc-predef.h, University of Washington](https://courses.cs.washington.edu/courses/cse351/16wi/lab-1.html)

*	[lec02c-Float.ppt](http://ssea.ustcsz.edu.cn:443/UploadFiles/courseResources/20180918/lec02c-Float_2018918161645396.ppt)
