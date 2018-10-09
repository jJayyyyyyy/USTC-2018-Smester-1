#!/usr/bin/python3
# -*- coding: utf-8 -*-

class Chaos(object):
	def __init__(self):
		# 以下定义的是默认初始值
		self.x1 = 0.25
		self.x2 = 0.26
		self.numIter = 10
		self.filename = 'chaos.txt'

	# 获取用户输入
	def getInput(self):
		x1 = eval(input('Please input x1: '))
		x2 = eval(input('Please input x2: '))
		numIter = int(input('Please input number of iterations: '))
		return x1, x2, numIter

	# 测试函数
	def test(self):
		x1, x2, numIter = self.getInput()

		print('\nindex\t%f\t%f' % (x1, x2))				# 格式化输出 Title
		print('--------------------------------')			# 输出分隔符

		for i in range(numIter):
			x1 = 3.9 * x1 * (1 - x1)
			x2 = 3.9 * x2 * (1 - x2)
			print('%d\t%.6f\t%.6f' % (i+1, x1, x2))			# 输出每一次迭代后的结果

	# 附加题，将输出结果保存到 filename
	def testWriteToFile(self):
		x1, x2, numIter = self.x1, self.x2, self.numIter
		with open(self.filename, 'w') as f:
			line = '\nindex\t%f\t%f' % (x1, x2)
			f.write(line + '\n')
			
			line = '--------------------------------'
			f.write(line + '\n')

			for i in range(numIter):
				x1 = 3.9 * x1 * (1 - x1)
				x2 = 3.9 * x2 * (1 - x2)
				line = '%d\t%.6f\t%.6f' % (i+1, x1, x2)
				f.write(line + '\n')

	# 附加题，从 filename 读取结果并输出到屏幕
	def testReadFromFile(self):
		with open(self.filename, 'r') as f:
			line = f.readline()
			while line:
				print(line.rstrip('\n'))
				line = f.readline()

if __name__ == '__main__':
	chaos = Chaos()
	chaos.test()
	# chaos.testWriteToFile()
	# chaos.testReadFromFile()
