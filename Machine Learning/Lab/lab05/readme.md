##	使用 `SVM` 进行分类

*	实验目标

	理解 `SVM` 的分类原理

	能根据数据集设计合理的 `SVM` 分类方法

	准确评估分类器精度

*	实验工具

	[libsvm](https://github.com/cjlin1/libsvm)

	[matlab](https://www.mathworks.com/downloads/)

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

	matlab R2016b, academic use

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

	如果是给 matlab 用, 根据 [Matlab interface of LIBSVM](https://github.com/cjlin1/libsvm/tree/master/matlab), 首先打开 matlab, 然后通过 command window 切换到 `libsvm-323/matlab` 目录, 然后

	```matlab
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

	matlab 调用 libsvm, 和 python 类似, 大致形式如下, 具体代码稍后在下面的实例中介绍

	```matlab
	[y, x] = libsvmread(train_set);
	model = svmtrain(train_y, train_x, sprintf('-s 0 -t 0'));
	[test_y, test_x] = libsvmread(test_set);
	[pred_y, accu, decision_values] = svmpredict(test_y, test_x, model);
	```

	<br>

	最后, 附上 svm-train 的 options, 内容来自[libsvm 文档](https://github.com/cjlin1/libsvm/tree/master)

	```
	-s svm_type : set type of SVM (default 0)
		0 -- C-SVC		(multi-class classification)
		1 -- nu-SVC		(multi-class classification)
		2 -- one-class SVM
		3 -- epsilon-SVR	(regression)
		4 -- nu-SVR		(regression)
	-t kernel_type : set type of kernel function (default 2)
		0 -- linear: u'*v
		1 -- polynomial: (gamma*u'*v + coef0)^degree
		2 -- radial basis function: exp(-gamma*|u-v|^2)
		3 -- sigmoid: tanh(gamma*u'*v + coef0)
		4 -- precomputed kernel (kernel values in training_set_file)
	-d degree : set degree in kernel function (default 3)
	-g gamma : set gamma in kernel function (default 1/num_features)
	-r coef0 : set coef0 in kernel function (default 0)
	-c cost : set the parameter C of C-SVC, epsilon-SVR, and nu-SVR (default 1)
	-n nu : set the parameter nu of nu-SVC, one-class SVM, and nu-SVR (default 0.5)
	-p epsilon : set the epsilon in loss function of epsilon-SVR (default 0.1)
	-m cachesize : set cache memory size in MB (default 100)
	-e epsilon : set tolerance of termination criterion (default 0.001)
	-h shrinking : whether to use the shrinking heuristics, 0 or 1 (default 1)
	-b probability_estimates : whether to train a SVC or SVR model for probability estimates, 0 or 1 (default 0)
	-wi weight : set the parameter C of class i to weight*C, for C-SVC (default 1)
	-v n: n-fold cross validation mode
	-q : quiet mode (no outputs)


	The k in the -g option means the number of attributes in the input data.

	option -v randomly splits the data into n parts and calculates cross
	validation accuracy/mean squared error on them.
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

##	实验 1, SVM Linear Classification

*	注意, 由于本次实验使用 matlab 实现, 因此以下均假设 command window 已经切换到了 libsvm/libsvm-323/matlab 目录, 而且所有数据集都下载到了 libsvm/libsvm-323/matlab/dataset 目录下

*	首先下载并解压 [ex7Data数据集](http://openclassroom.stanford.edu/MainFolder/courses/MachineLearning/exercises/ex7materials/ex7Data.zip)

*	我们对其中的 twofeature.txt 文件进行分析

	```matlab
	% 读取训练集数据
	[y, x] = libsvmread('dataset/ex7Data/twofeature.txt');

	% Setting the cost, 设置参数 C
	% 调节 C 可以调节分类面的 Margin
	% C越大, Margin 越小, 正确率也越高, 但在非线性的分类问题中可能会出现过拟合
	C = 1;
	% C = 10;
	% C = 100;

	% 训练模型, sprintf() 输入的是 option 参数
	model = svmtrain(y, x, sprintf('-s 0 -t 0 -c %g', C));

	% 
	w = model.SVs' * model.sv_coef;
	b = -model.rho;

	if (model.Label(1) == -1)
	    w = -w; b = -b;
	end


	% Ploting the data points, 画出数据点图
	figure
	pos = find(y == 1);
	neg = find(y == -1);
	plot(x(pos,1), x(pos,2), 'ko', 'MarkerFaceColor', 'b'); hold on;
	plot(x(neg,1), x(neg,2), 'ko', 'MarkerFaceColor', 'g')

	% Plotting the decision boundary, 画出分类超平面
	plot_x = linspace(min(x(:,1)), max(x(:,1)), 30);
	plot_y = (-1/w(2))*(w(1)*plot_x + b);
	plot(plot_x, plot_y, 'k-', 'LineWidth', 2)

	% 标题
	title(sprintf('SVM Linear Classifier with C = %g', C), 'FontSize', 14)
	```

	可以看到 C = 1 的图示结果如下, 调节 C, 结果会有差别

	![two_features_C1](assets/two_features_C1.png)

*	接着, 我们处理 `email` 数据集, 使用线性 SVM 判断每一条记录是否为垃圾邮件

	```matlab
	% SVM Email text classification
	% 加载训练数据
	[train_y, train_x] = libsvmread('dataset/ex7Data/email_train-100.txt');

	% Train the model and get the primal variables w, b from the model
	model = svmtrain(train_y, train_x, '-s 0 -t 0');

	w = model.SVs' * model.sv_coef;
	b = -model.rho;
	if (model.Label(1) == -1)
	    w = -w; b = -b;
	end

	% 加载测试数据
	[test_y, test_x] = libsvmread('dataset/ex7Data/email_test.txt');

	% 分类预测
	[predicted_label, accuracy, decision_values] = svmpredict(test_y, test_x, model);

	% Ploting the data points
	figure
	pos = find(test_y == 1);
	neg = find(test_y == -1);
	plot(test_x(pos,1), test_x(pos,2), 'ko', 'MarkerFaceColor', 'b'); hold on;
	plot(test_x(neg,1), test_x(neg,2), 'ko', 'MarkerFaceColor', 'g')

	% Plotting the decision boundary
	plot_x = linspace(min(test_x(:,1)), max(test_x(:,1)), 30);
	plot_y = (-1/w(2))*(w(1)*plot_x + b);
	plot(plot_x, plot_y, 'k-', 'LineWidth', 2)

	% title(sprintf('SVM Linear Classifier with C = %g', C), 'FontSize', 14)
	```

	可以看到使用 `email_train-100.txt` 数据集进行训练后, 测试的准确率为 `75.3846%`, 图示结果如下。尝试使用不同的训练集, 测试结果会有差别。

	![email_train-100](assets/email_train-100.png)

*	实验 1 的过程和代码参考了

	[Exercise 7: SVM Linear Classification](http://openclassroom.stanford.edu/MainFolder/DocumentPage.php?course=MachineLearning&doc=exercises/ex7/ex7.html)

	[TwoFeature_SVMClassification by DishantK1807](https://github.com/DishantK1807/Machine-Learning-Algorithms-Andrew-Ng./blob/master/SVM-Linear-Classification/TwoFeature_SVMClassification.m)

	[two features SVM by 2011aad](https://github.com/2011aad/Machine-Learning-Assignments--Coursera-Andrew-Ng--/blob/3c2eeea25622206246b100096498a654bdeb6edf/Machine-Learning-ex7/SVM.m)

	[EmailText_SVMClassification by DishantK1807](https://github.com/DishantK1807/Machine-Learning-Algorithms-Andrew-Ng./blob/master/SVM-Linear-Classification/EmailText_SVMClassification.m)

	<br>



##	reference

[实验摘抄自原博客

[plotboundary()](https://github.com/rawalkhirodkar/machine_learning/blob/6d403cccf92d95e92441d3fef46a87cf74765c53/svm/details/cs725_s2015_a3/vikern/plotboundary.m)

[plotboundary()](http://openclassroom.stanford.edu/MainFolder/courses/MachineLearning/exercises/ex8materials/ex8Data.zip)

[OpenClassroom homepage](http://openclassroom.stanford.edu/MainFolder/DocumentPage.php?course=MachineLearning&doc=exercises/ex7/ex7.html)

[two features](https://github.com/DishantK1807/Machine-Learning-Algorithms-Andrew-Ng./blob/master/SVM-Linear-Classification/TwoFeature_SVMClassification.m)




http://ssea.ustcsz.edu.cn:443/UploadFiles/experimentResources/20181226/%E5%AE%9E%E9%AA%8C%E5%9B%9B%20%20%E5%88%A9%E7%94%A8SVM%E5%AE%9E%E7%8E%B0%E5%88%86%E7%B1%BB%E5%AE%9E%E9%AA%8C_20181226173311956.pdf

https://blog.csdn.net/gyh_420/article/details/77943973

http://openclassroom.stanford.edu/MainFolder/DocumentPage.php?course=MachineLearning&doc=exercises/ex8/ex8.html

https://github.com/2011aad/Machine-Learning-Assignments--Coursera-Andrew-Ng--/blob/3c2eeea25622206246b100096498a654bdeb6edf/Machine-Learning-ex7/SVM.m

https://github.com/2011aad/Machine-Learning-Assignments--Coursera-Andrew-Ng--/blob/3c2eeea25622206246b100096498a654bdeb6edf/Machine-Learning-ex8/Nonlinear_Classification.m


