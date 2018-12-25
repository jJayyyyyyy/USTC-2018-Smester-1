import numpy as np
import pandas as pd
import random

w = np.zeros(104)
b = 0
lr = 0.5


def sign(vec, y):
	global w, b
	return y * (np.matmul(w, vec.T) + b)


def update(vec, y):
	global w, b, lr
	w = w + lr * y * vec
	b = b + lr * y


# 标准化数据
def standardize(data):
	data_std = np.zeros(data.shape)
	data = data.astype(int)
	mean = data.mean(axis=0)
	std = data.std(axis=0)
	for col in range(data.shape[1]):
		if std[col]:
			data_std[:, col] = (data[:, col] - mean[col]) / std[col]
	return data_std


# 分割数据集
def splitDataset(data, data_y, split_ratio):
	data = data.tolist()
	data_y = data_y.tolist()
	train_size = int(len(data) * split_ratio)
	train_std = []
	train_y = []
	data_copy = list(data)
	data_y_copy = list(data_y)
	while len(train_std) < train_size:
		index = random.randrange(len(data_copy))
		train_std.append(data_copy.pop(index))
		train_y.append(data_y_copy.pop(index))
	return np.array(train_std), np.array(train_y), np.array(data_copy), np.array(data_y_copy)


def get_label_and_income(data, columns):
	income_list = data[:, 14]
	data = np.delete(data, -1, axis=1)
	columns = columns.reshape(1, -1)
	columns = np.delete(columns, -1, axis=1)
	return data, columns, income_list


# 转化为one-hot
def convert_to_one_hot(data, columns, income_list):
	df = pd.DataFrame(data.tolist())
	df.columns = columns.tolist()

	df = pd.get_dummies(df, columns=['work_class', 'marriage', 'occupation', 'relationship',
									 'sex', 'native_country'])
	# print(df)
	df_income = pd.DataFrame(income_list.tolist())
	df_income.columns = ['income']
	df_income['income'] = df_income['income'].map({'>50K': 1, '<=50K': -1})
	df_income = pd.get_dummies(df_income)
	return np.array(df), np.array(df_income)


# 删除标签
def del_label(data, columns):
	for val in ['fnlwgt', 'education', 'race', 'capital_gain']:
		index = columns.tolist()[0].index(val)
		data = np.delete(data, index, axis=1)
		columns = np.delete(columns, index, axis=1)
	return data, columns

# 返回标准化之后的 数据集和 标签
def get_data():
	with open("adult.data", "r") as obj:
		lines = []
		for line in obj:
			lines.append(line.strip("\n"))

	data = []
	columns = ['age', 'work_class', 'fnlwgt', 'education', 'education_number', 'marriage', 'occupation', 'relationship', 'race', 'sex', 'capital_gain', 'capital_loss', 'hours_per_week', 'native_country', 'income']
	# 去掉有缺失的数据
	for val in lines:
		if not len(val) == 0 and '?' not in val:
			temp = val.split(', ')
			data.append(temp)
	data, columns, income_list = get_label_and_income(np.array(data), np.array(columns))
	data, columns = del_label(data, columns)
	data, income_list = convert_to_one_hot(data, columns, income_list)
	# print(income_list)
	return standardize(data), income_list

def test(data_std, data_y):
	global w, b
	num = 0
	for idx, val in enumerate(data_std[:10000]):
		res = np.matmul(w, val.T) + b
		if res > 0 and data_y[idx] == 1:
			num = num + 1
		if res < 0 and data_y[idx] == -1:
			num = num + 1
	return num /10000


def main():
	global w
	times = 1
	count = 0
	for i in range(times):
		data, data_y = get_data()
		train_std, train_y, test_std, test_y = splitDataset(data, data_y, 0.7)
		w = np.zeros(train_std.shape[1])
		print(len(w))
		for idx, ele in enumerate(train_std):
			res = sign(ele, train_y[idx])
			if not res > 0:
				update(ele, train_y[idx])
		res = test(test_std, test_y)
		# print(res)
		count = count + res

	print(count/times)


if __name__ == "__main__":
	main()
