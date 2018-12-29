'''
1. 预处理   
   1.1 [done] 标准化
   1.2 [done] 按比例，随机分割训练集、测试集

2. knn
   2.1 输入一个测试样本 x
   2.2 计算 x 与所有 train_x 的距离, 排序
   2.3 取前 k 个 train_x, 即最近的 k 个, 统计 label(即 train_y)
   2.4 取数量最大的 label 作为 x 的 label
'''

import numpy as np

class Dataset(object):
	def __init__(self, train_x, train_y, test_x, test_y):
		self.train_x = train_x
		self.train_y = train_y
		self.test_x = test_x
		self.test_y = test_y
		self.pred_y = None

	def print_info(self):
		print(self.train_x)
		print(self.train_y)
		print(self.test_x)
		print(self.test_y)
		print(self.pred_y)

class FeatureEngineer(object):
	def __init__(self, iris):
		self.x = iris.data[:]
		self.y = iris.target[:]
		# print(self.x)
		# print(self.y)

	def standardize(self, mean=0, std=1):
		'''
		标准化数据集 X
		return: @self.std_x
		'''
		# std_x = np.zeros(self.x.shape)
		mean = self.x.mean(axis = 0)
		std = self.x.std(axis = 0)
		
		std_x = []
		for x in self.x:
			record = []
			size = len(x)
			for i in range(size):
				feature = x[i]
				feature = (feature - mean[i]) / std[i]
				record.append(feature)
			std_x.append(record)
		self.std_x = np.array(std_x)
		# print(self.std_x)
		return self.std_x

	def standardize_with_sklearn(self):
		from sklearn.preprocessing import StandardScaler
		ss = StandardScaler()
		std_x = ss.fit_transform(self.x)
		self.std_x = std_x
		# print(std_xx)
		return self.std_x

	def get_index_list(self, shuffle=True,seed=None):
		index_list = np.arange(self.x.shape[0])
		if shuffle:
			if seed:
				np.random.seed(seed)
			np.random.shuffle(index_list)
		# print(index_list)
		return index_list

	def get_train_and_test_data(self, train_ratio=0.8, shuffle=True, seed=1):
		x = self.x
		y = self.y

		size = self.x.shape[0]
		train_size = int(size * train_ratio)
		test_size = size - train_size

		index_list = self.get_index_list(shuffle=shuffle, seed=seed)
		train_index = index_list[:train_size]
		test_index = index_list[train_size:]
		dataset = Dataset(x[train_index], y[train_index], x[test_index], y[test_index])
		return dataset

class Neighbor(object):
	def __init__(self, index, distance):
		self.index = index
		self.distance = distance

	def print_info(self):
		print(self.index, self.distance)

class KNN(object):
	def __init__(self, dataset, k=5):
		self.dataset = dataset
		self.k = k

	# 计算一个样本与训练集中所有样本的欧氏距离的平方
	def get_euclidean_distance(self, one_x):
		x = self.dataset.train_x

		# 每一行记录单独进行 sum
		distance = np.power(one_x - x, 2).sum(axis=1)
		return distance

	def get_sorted_neighbor_list(self, one_x):
		distance = self.get_euclidean_distance(one_x)
		neighbor_list = []
		for i in range(distance.shape[0]):
			neighbor = Neighbor(i, distance[i])
			neighbor_list.append(neighbor)

		sorted_neighbor_list = sorted(neighbor_list, key=lambda neighbor : neighbor.distance)
		return sorted_neighbor_list

	# 获取 k 个近邻的类别标签
	def get_k_label_list(self, k_neighbor_list):
		k_label_list = []
		for neighbor in k_neighbor_list:
			index = neighbor.index
			label = self.dataset.train_y[index]
			k_label_list.append(label)

		return k_label_list

	# 进行标签统计，得票最多的标签就是该测试样本的预测标签
	def get_majority_vote(self, one_x):
		sorted_neighbor_list = self.get_sorted_neighbor_list(one_x)
		k_neighbor_list = sorted_neighbor_list[:self.k]
		k_label_list = self.get_k_label_list(k_neighbor_list)
		d = {}
		for label in k_label_list:
			if label in d:
				d[label] += 1
			else:
				d[label] = 0

		maxcnt = 0
		maxlabel = k_label_list[0]
		for key, value in d.items():
			if maxcnt < value:
				maxcnt = value
				maxlabel = key

		majority_vote = maxlabel
		return majority_vote

	def get_prediction(self):
		train_x = self.dataset.train_x
		train_y = self.dataset.train_y
		test_x = self.dataset.test_x
		pred_y = []
		for one_x in test_x:
			label = self.get_majority_vote(one_x)
			pred_y.append(label)

		self.dataset.pred_y = np.array(pred_y)

	def get_accuracy(self):
		test_y = self.dataset.test_y
		pred_y = self.dataset.pred_y
		accu = np.sum(test_y == pred_y) / test_y.shape[0]
		print('模型准确率: ', accu)

def test_iris():
	from sklearn import datasets
	iris = datasets.load_iris()
	fe = FeatureEngineer(iris)
	fe.standardize(mean=0, std=1)
	dataset = fe.get_train_and_test_data(train_ratio=0.75, seed=None)

	knn = KNN(dataset, k=3)
	knn.get_prediction()
	knn.get_accuracy()


if __name__ == '__main__':
	test_iris()
