##	实验目的

*	学习参考资料中的感知机模型, 对其进行改造, 然后对 [UCI](https://archive.ics.uci.edu/ml/index.php) 的 [machine-learning-databases/adult](https://archive.ics.uci.edu/ml/machine-learning-databases/adult/) 数据进行收入分类预测

*	[adult](https://archive.ics.uci.edu/ml/machine-learning-databases/adult/) 数据简介

	数据集有 15 列, 其中 14 列是输入属性 `X`, 包含 `年龄、性别、职业` 等特征, 最后一列是收入, 也就是我们要预测的 `y`

	注意先对数据集进行特征工程，比如缺失值填充(丢弃)、标准化(标准正态分布)等。

	<br>

##	构造感知机模型

*	感知机原理

	感知机是一个二类分类的线性分类器, 是支持向量机和神经网络的基础。假设数据是线性可分的, 目标是通过梯度下降法, 极小化损失函数, 最后找到一个分割超平面, 可以将数据划分成两个类别。

*	决策函数

	```
	f(x) = sign(w·x + b)
	```

	对 `n` 维来说, 线性方程 `wx+b = 0` 对应了特征空间的一个超平面, 其中 `w` 是超平面的法向量, `b` 是超平面的截距。`w·x` 即各项对应相乘后求和。

	要建立感知机模型, 只要确定参数 `w` 和 `b`, 然后通过梯度下降法, 不断调整两个参数, 向最优解靠近。

*	损失函数

	```
	L(w, b) = - ∑ yi(w·xi + b)
	```

	其中 `(xi, yi)` 为分类错误的一个样例, `M` 为所有分类错误样例的集合。

	函数值 `L` 越小, 说明离最好的模型越近。

*	梯度下降

	我们的目标是使损失函数极小化, 即

	```
	min L(w, b) = - ∑ yi(w·xi + b)
	```

	分别对 w 和 b 求偏导, 得到

	```
	∂L/∂w = - ∑ yi·xi
	∂L/∂b = - ∑ yi
	```

	使用 SGD 更新权重

	```
	w = w - η∂L/∂w
	b = b - η∂L/∂b
	```

	直到没有误分类点为止。更具体的过程请参考李航教授的《统计学习方法》

	<br>

##	参考资料

*	[《统计学习方法》](https://book.douban.com/subject/10590856/)

*	[machine-learning-databases/adult](https://archive.ics.uci.edu/ml/machine-learning-databases/adult/)

