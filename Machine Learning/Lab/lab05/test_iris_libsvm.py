# https://github.com/cjlin1/libsvm/tree/master/python
# wget https://codeload.github.com/cjlin1/libsvm/zip/v323
# 7z x v323.zip

import sys
path = "/root/libsvm/libsvm-323/python"
sys.path.append(path)
from svmutil import *
from svm import *

train_y, train_x = svm_read_problem('iris_train.txt')

print('C')
for i in range(1, 100, 5):
	m = svm_train(y, x, '-s 0 -t 2 -c %d -g 1' % i )
	test_y, test_x = svm_read_problem('iris_test.txt')
	pred_y, accu, p_val = svm_predict(test_y, test_x, m)


print('\n\ngamma')
for i in range(1, 100, 5):
	m = svm_train(y, x, '-s 0 -t 2 -c 1 -g %d' % i )
	test_y, test_x = svm_read_problem('iris_test.txt')
	pred_y, accu, p_val = svm_predict(test_y, test_x, m)

