class Dataset(object):
	def __init__(self, option):
		if option == 'iris':
			self.gen_iris_dataset()

	def gen_MLA_dataset(self):
		self.size = 5
		self.dataset = [[1, 100, 1], [1, 100, 1], [1, 200, -1], [0, 100, -1], [0, 100, -1]]
		# self.dataset = [[1, 1, 1], [1, 1, 1], [1, 0, -1], [0, 1, -1], [0, 1, -1]]

	def gen_iris_dataset(self):
		from sklearn import datasets
		iris = datasets.load_iris()
		self.x_name_list = iris.feature_names
		self.y_name_list = iris.target_names
		self.size = len(iris.data)

		x_list = iris.data
		y_list = iris.target
		dataset = []
		for i in range(self.size):
			x = x_list[i].tolist()
			record = [ x for x in iris.data[i] ]
			y = int(y_list[i])
			record.append(y)
			dataset.append(record)
		self.dataset = dataset

	def get_index_list(self, shuffle=True, seed=None):
		import numpy as np
		index_list = np.arange(self.size)
		if shuffle:
			if seed:
				np.random.seed(seed)
			np.random.shuffle(index_list)
		return index_list

	def get_train_and_test_data(self, train_ratio=0.8, seed=0):
		size = self.size
		train_size = int(size * train_ratio)
		test_size = size - train_size

		index_list = self.get_index_list(seed=seed)
		train_index = index_list[:train_size]
		test_index = index_list[train_size:]

		dataset = self.dataset

		train_set = []
		for i in train_index:
			train_set.append(dataset[i])

		test_set = []
		for i in test_index:
			test_set.append(dataset[i])

		self.train_set = train_set
		self.test_set = test_set
		return train_set, test_set

if __name__ == '__main__':
	ds = Dataset(option='iris')
	train_set, test_set = ds.get_train_and_test_data(train_ratio=0.8, seed=2)
