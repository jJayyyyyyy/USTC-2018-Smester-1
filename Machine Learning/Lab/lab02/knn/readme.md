##	KNN 分类器的构造

*	算法思路

	存在一个样本数据集合, 称为训练样本集, 且样本集中每个数据都存在标签, 即样本集中每一数据与所属分类的对应关系。

	输入没有标签的数据后, 将新数据中的每个特征与样本集中数据对应的特征进行比较, 提取出样本集中特征最相似数据（最近邻）的分类标签。选择 k 个最相似数据中出现次数最多的分类作为新数据的分类。

*	算法步骤

	1. 计算未知实例到所有已知实例的距离

	2. 选择参数 k

	3. 根据多数表决( majority-voting )规则, 将未知实例归类为样本中最多数的类别

*	距离的衡量方法

	*	欧式距离

		这种测量方式就是简单的平面几何中两点之间的直线段距离

		```
		d(p1, p2) = √[(x1 - x2)^2 + (y1 - y2)^2]
		```

	*	曼哈顿距离 / 街区距离

		```
		d(p1, p2) = |x1 - x2| + |y1 - y2|
		```

*	k 值的选择

	k 值的选择会影响结果, 如何选择一个最佳的 k 值取决于数据。一般, 较大 k 值能减小噪声的影响, 但会使类别之间的界限变得模糊, 因此 k 的取值一般比较小 (k < 20)

	<br>

##	实验步骤

*	首先学习参考例程

	```python3
	import sys
	import os
	import math
	import numpy as np
	from sklearn import datasets
	import matplotlib.pyplot as plt
	from collections import Counter
	from sklearn.datasets import make_classification
	%matplotlib inline

	def shuffle_data(X, y, seed=None):
		if seed:
			np.random.seed(seed)

		idx = np.arange(X.shape[0])
		np.random.shuffle(idx)
		return X[idx], y[idx]

	# 正规化数据集 X
	def normalize(X, axis=-1, p=2):
		lp_norm = np.atleast_1d(np.linalg.norm(X, p, axis))
		lp_norm[lp_norm == 0] = 1
		return X / np.expand_dims(lp_norm, axis)

	# 标准化数据集 X
	def standardize(X):
		X_std = np.zeros(X.shape)
		mean = X.mean(axis=0)
		std = X.std(axis=0)
		# 分母不能等于 0 的情形
		# X_std = (X - X.mean(axis=0)) / X.std(axis=0)
		for col in range(np.shape(X)[1]):
			if std[col]:
				X_std[:, col] = (X_std[:, col] - mean[col]) / std[col]
		return X_std

	# 划分数据集为训练集和测试集
	def train_test_split(X, y, test_size=0.2, shuffle=True, seed=None):
		if shuffle:
			X, y = shuffle_data(X, y, seed)
			n_train_samples = int(X.shape[0] * (1-test_size))
			x_train, x_test = X[:n_train_samples], X[n_train_samples:]
			y_train, y_test = y[:n_train_samples], y[n_train_samples:]
		return x_train, x_test, y_train, y_test

	# 测试准确率
	def accuracy(y, y_pred):
		y = y.reshape(y.shape[0], -1)
		y_pred = y_pred.reshape(y_pred.shape[0], -1)
		return np.sum(y == y_pred)/len(y)

	class KNN():
		""" K 近邻分类算法.
		Parameters:
		-----------
		k: int
		最近邻个数.
		"""
		def __init__(self, k=5):
			self.k = k

		# 计算一个样本与训练集中所有样本的欧氏距离的平方
		def euclidean_distance(self, one_sample, X_train):
			one_sample = one_sample.reshape(1, -1)
			X_train = X_train.reshape(X_train.shape[0], -1)
			distances = np.power(np.tile(one_sample, (X_train.shape[0], 1)) - X_train, 2).sum(axis=1)
			return distances

		# 获取 k 个近邻的类别标签
		def get_k_neighbor_labels(self, distances, y_train, k):
			k_neighbor_labels = []

			for distance in np.sort(distances)[:k]:
				label = y_train[ distances == distance ]
				k_neighbor_labels.append(label)

			return np.array(k_neighbor_labels).reshape(-1, )

		# 进行标签统计, 得票最多的标签就是该测试样本的预测标签
		def vote(self, one_sample, X_train, y_train, k):
			distances = self.euclidean_distance(one_sample, X_train)
			#print(distances.shape)
			y_train = y_train.reshape(y_train.shape[0], 1)
			# print(distances)
			k_neighbor_labels = self.get_k_neighbor_labels(distances, y_train, k)
			#print(k_neighbor_labels.shape)
			find_label, find_count = 0, 0
			
			# print(k_neighbor_labels.shape)
			for label, count in Counter(k_neighbor_labels).items():
				if count > find_count:
					find_count = count
					find_label = label
			return find_label


		# 对测试集进行预测
		def predict(self, X_test, X_train, y_train):
			y_pred = []
			for sample in X_test:
				label = self.vote(sample, X_train, y_train, self.k)
				y_pred.append(label)

			#print(y_pred)
			return np.array(y_pred)

	def main():
		# Generate a random n-class classification problem.
		# n_classes=2, 2分类
		data = make_classification(n_samples=200, n_features=4, n_informative=2, n_redundant=2, n_repeated=0, n_classes=2)
		X, y = data[0], data[1]
		# 训练集 2/3, 测试集 1/3, 随机打乱
		X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.5, shuffle=True)
		
		clf = KNN(k=5)
		y_pred = clf.predict(X_test, X_train, y_train)
		accu = accuracy(y_test, y_pred)
		print("Accuracy:", accu)

	if __name__ == "__main__":
		main()
	```

*	接着使用 Iris 数据集进行训练和预测

	训练集和测试集是 `sklearn` 中关于 `Iris` 的数据

	```python3
	from sklearn import datasets
	iris = datasets.load_iris()
	```

	`Iris` 是三分类问题, 我们要修改源程序中的 `get_k_neighbor_labels()`, 使分类器能够正常工作

##	参考资料
