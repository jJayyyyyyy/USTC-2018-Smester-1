import numpy as np
import pandas as pd
from sklearn.preprocessing import StandardScaler
from sklearn.linear_model import Perceptron
from sklearn.metrics import accuracy_score

def get_data():
	train_path = "adult.data"
	test_path = "adult.test"
	headers = ['age', 'workclass', 'fnlwgt', 'education', 'education-num', 'marital-status', 'occupation', 'relationship', 'race', 'sex', 'capital-gain', 'capital-loss', 'hours-per-week', 'native-country', 'predclass']
	train_set = pd.read_csv('adult.data', header=None, names=headers, sep=',\s', na_values=["?"], engine='python')
	test_set = pd.read_csv('adult.test', header=None, names=headers, sep=',\s', na_values=["?"], engine='python', skiprows=1)

	col_labels = ['age', 'workclass', 'fnlwgt', 'education', 'education_num', 'marital_status', 'occupation', 'relationship', 'race', 'sex', 'capital_gain', 'capital_loss', 'hours_per_week', 'native_country', 'wage_class']
	train_set.columns = col_labels
	test_set.columns = col_labels

	# 训练集以及测试集中的缺失值都是用 ? 替换的，删除缺失数据行
	train_set = train_set.replace(' ?', np.nan).dropna()
	test_set = test_set.replace(' ?', np.nan).dropna()
	
	# 测试集中是 "50K."
	# 训练集中是 "50K"
	test_set['wage_class'] = test_set.wage_class.replace({' <=50K.': ' <=50K', ' >50K.': ' >50K'})


	# 字符串类型转化为数值类型,为了保证测试集和训练集的encoding类型一致，我们首先将两个表join，编码完成之后，在分开到原始的表中
	combined_set = pd.concat([train_set, test_set], axis=0)
	# 合并完成将表中的object数据转化为int类型
	for feature in combined_set.columns:
		if combined_set[feature].dtype == 'object':
			combined_set[feature] = pd.Categorical(combined_set[feature]).codes

	# 将数据转回原有的训练集以及测试集中
	train_set = combined_set[:train_set.shape[0]]
	test_set = combined_set[train_set.shape[0]:]

	# 得到数据对应的标签
	y_train = train_set.pop('wage_class')
	y_test = test_set.pop('wage_class')
	y_test = [ y - 1 for y in y_test.tolist()]

	return train_set, y_train, test_set, y_test


reduced_train_x_data, train_y_data, reduced_test_x_data, test_y_data = get_data()


# 对训练数据和测试数据进行标准化，保证每个维度的特征数据方差为1，均值为0，使得预测结果不会被某些维度过大的特征值而主导
ss = StandardScaler()
# fit_transform()先计算训练集的均值和方差，再执行数据标准化
reduced_train_x_data_std = ss.fit_transform(reduced_train_x_data)
# transform()直接用上面的均值和方差对数据进行标准化，这里是认为测试数据和训练数据具有同样的均值和方差
reduced_test_x_data_std = ss.transform(reduced_test_x_data)


# eta0 学习率，random_state是随机数种子,max_iter最大迭代次数，tol为损失函数值下界，小于则停止训练
ppn = Perceptron(max_iter = 1, eta0 = 0.01, tol = 1e-3, random_state = 0)
ppn.fit(reduced_train_x_data_std, train_y_data)
y_pred = ppn.predict(reduced_test_x_data_std).tolist()

print("准确率：", accuracy_score(test_y_data, y_pred))
