##	题目1, quiz score and grade

*	A certain CS professor gives 5-point quizzes that are graded on the scale 5-A, 4-B, 3-C, 2-D, 1-E, 0-F. Write a program that accepts a quiz score as an input and prints out the corresponding grade.

	输入 `5~0` 的分数，输出 `A~F` 的成绩

*	代码及注释

	```python
	#!/usr/bin/python3
	# -*- coding: utf-8 -*-

	class Quiz(object):
		def __init__(self):
			pass

		# 把 `5~0` 的分数转换成 `A~F` 的成绩
		def getGrade(self, score):
			grade = None
			if score <= 5 and score >= 0:
				# 利用 chr(), ord(), 以及 ASCII 码进行转换
				grade = chr(ord('F') - score)
			return grade

		# 测试函数
		def test(self):
			# 预期结果
			expScore = {5:'A', 4:'B', 3:'C', 2:'D', 1:'E', 0:'F', 6:None, -1:None}

			print('Test function getGrade()')
			print('Score\t\tExpected Grade\t\tTest Grade\tIs Same')

			for score, grade in expScore.items():
				tmpGrade = self.getGrade(score)		# getGrade() 得到的结果
				isSame = bool(grade == tmpGrade)	# 与预期结果进行对比
				print(score, '\t\t', grade, '\t\t\t', tmpGrade, '\t\t', isSame)

	if __name__ == '__main__':
		quiz = Quiz()
		quiz.test()
	```

*	运行结果截图

	![quiz_score_and_grade](https://github.com/jJayyyyyyy/USTC-2018-Smester-1/blob/master/Python/homework/hw02/assets/quiz_score_and_grade.png)

<br>

##	题目2, improved chaos

*	Write an improved version of the `chaos.py` program that allows a user to input two initial values and the number of iterations and then prints a nicely formatted table showing how the values change over time. For example, if the starting values were `.25` and `.26` with `10` iterations, the table might look like this:

	![demo_improved_chaos](https://github.com/jJayyyyyyy/USTC-2018-Smester-1/blob/master/Python/homework/hw02/assets/demo_improved_chaos.png)

	原来的 `chaos.py` 只有一个输入值，现在可以输入 `x1, x2`，方便对比每一次迭代后值的变化。另外，还可以由用户输入迭代次数。

*	代码及注释

	```python
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
		# chaos.testReadFromFile()
	```

*	运行结果截图

	![improved_chaos](https://github.com/jJayyyyyyy/USTC-2018-Smester-1/blob/master/Python/homework/hw02/assets/improved_chaos.png)

<br>
