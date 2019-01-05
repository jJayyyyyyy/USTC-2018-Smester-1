# first download iris dataset as [iris.txt] from the link below
# https://www.csie.ntu.edu.tw/~cjlin/libsvmtools/datasets/multiclass/iris.scale
# then run this script to generate train and test set

def get_index_list(shuffle=True, seed=None):
	import numpy as np
	index_list = np.arange(150)
	if shuffle:
		if seed:
			np.random.seed(seed)
		np.random.shuffle(index_list)
	return index_list

def get_train_and_test_data(train_ratio=0.8, shuffle=True, seed=1):
	size = 150
	train_size = int(size * train_ratio)
	test_size = size - train_size

	index_list = get_index_list(shuffle=shuffle, seed=seed)
	train_index = index_list[:train_size]
	test_index = index_list[train_size:]

	with open('iris.txt') as f:
		dataset = f.read().split('\n')

	# train_set
	with open('iris_train.txt', 'w') as f:
		for i in train_index:
			f.write(dataset[i] + '\n')

	# test_set
	with open('iris_test.txt', 'w') as f:
		for i in test_index:
			f.write(dataset[i] + '\n')

if __name__ == '__main__':
	get_train_and_test_data(train_ratio=0.7, shuffle=True, seed=2)
