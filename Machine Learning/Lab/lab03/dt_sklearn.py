import numpy as np

class Dataset(object):
	def __init__(self, train_x, train_y, test_x, test_y):
		self.train_x = train_x
		self.train_y = train_y
		self.test_x = test_x
		self.test_y = test_y
		self.pred_y = None

class FeatureEngineer(object):
	def __init__(self, iris):
		self.x = iris.data[:]
		self.y = iris.target[:]

	def standardize_with_sklearn(self):
		from sklearn.preprocessing import StandardScaler
		ss = StandardScaler()
		std_x = ss.fit_transform(self.x)
		self.std_x = std_x
		return self.std_x

	def get_index_list(self, shuffle=True,seed=None):
		index_list = np.arange(self.x.shape[0])
		if shuffle:
			if seed:
				np.random.seed(seed)
			np.random.shuffle(index_list)
		# print(index_list)
		return index_list

	def get_train_and_test_data(self, train_ratio=0.8, shuffle=True, seed=0):
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

def test_iris():
	from sklearn import datasets
	from sklearn.tree import DecisionTreeClassifier
	iris = datasets.load_iris()
	fe = FeatureEngineer(iris)
	fe.standardize_with_sklearn()
	dataset = fe.get_train_and_test_data(train_ratio=0.70)

	dt = DecisionTreeClassifier(criterion='entropy')
	dt.fit(dataset.train_x, dataset.train_y)
	pred_y = dt.predict(dataset.test_x)
	dataset.pred_y = pred_y

	from sklearn.metrics import accuracy_score
	print("准确率: ", accuracy_score(dataset.test_y, dataset.pred_y))

if __name__ == '__main__':
	test_iris()