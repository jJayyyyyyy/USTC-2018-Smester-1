##	使用 `SVM` 进行分类

*	实验目标

	理解 `SVM` 的分类原理

	能根据数据集设计合理的 `SVM` 分类方法

	准确评估分类器精度

*	实验工具

	[libsvm](https://github.com/cjlin1/libsvm)

	[python](https://www.python.org/)

	<br>

##	实验原理参考文档

*	[SVM 算法原理](https://blog.csdn.net/u012581541/article/details/51181041)

*	[机器学习算法与python实践之（二）支持向量机（SVM）初级](https://blog.csdn.net/zouxy09/article/details/17291543)

*	[SVM入门（一）至（三）Refresh](http://www.blogjava.net/zhenandaci/archive/2009/02/13/254519.html)

*	[支持向量机: Kernel](http://blog.pluskid.org/?p=685)

*	[机器学习, 周志华著](https://book.douban.com/subject/26708119/)

*	[统计学习方法, 李航著](https://book.douban.com/subject/10590856/)

*	[MLA, Machine Learning in Action, 机器学习实战, Peter Harrington著](https://book.douban.com/subject/24703171/)

	<br>

##	实验准备

*	实验环境

	Ubuntu 16.04 x64

	python 3.5

	libsvm v323

*	安装 libsvm

	```bash
	sudo apt-get update
	sudo apt-get install g++ make p7zip-full
	mkdir libsvm
	cd libsvm
	wget https://codeload.github.com/cjlin1/libsvm/zip/v323
	7z x v323.zip
	```

	如果要在 python 中使用 libsvm, 那么
	
	```python 
	cd libsvm-323/python
	make
	```

*	调用和测试 libsvm

	python 调用和测试 libsvm, 参考 [Python使用libsvm](https://blog.csdn.net/xmu_jupiter/article/details/46830327) 和 [LibSVM for Python 使用](https://www.cnblogs.com/Finley/p/5329417.html), 以及 [Python interface of LIBSVM](https://github.com/cjlin1/libsvm/tree/master/python)

	```python
	import sys
	path = "libsvm/libsvm-323/python"
	sys.path.append(path)
	from svmutil import *
	from svm import *

	y, x = [1,-1], [{1:1, 2:1}, {1:-1,2:-1}]
	prob  = svm_problem(y, x)
	param = svm_parameter('-t 0 -c 4 -b 1')
	model = svm_train(prob, param)
	yt = [1]
	xt = [{1:1, 2:1}]
	p_label, p_acc, p_val = svm_predict(yt, xt, model)
	print(p_label)
	```

	<br>

##	实验步骤

*	实验文档摘抄自这篇博客

	[[机器学习实验6]线性SVM分类和非线性SVM分类](https://blog.csdn.net/gyh_420/article/details/77943973)

	而这篇博客的内容来自 Stanford 的公开课 Machine Learning (by Andrew Ng)

	更具体地, 博客内容来自

	*	作业7, [Exercise 7: SVM Linear Classification](http://openclassroom.stanford.edu/MainFolder/DocumentPage.php?course=MachineLearning&doc=exercises/ex7/ex7.html)

	*	作业8, [Exercise 8: Non-linear SVM classification with kernels](http://openclassroom.stanford.edu/MainFolder/DocumentPage.php?course=MachineLearning&doc=exercises/ex8/ex8.html)

	按照以上关键字进行搜索, 可以找到丰富的资源。另外, 为了尊重原作者, 建议在实验说明文档中标注出处/原文链接。

	接下来分别对两个实验进行介绍。

	<br>
