##	题目1: 打印出 `GPA` 最高的同学的信息

*	One unresolved issue:This program only reports back a single student. If multiple students are tied for the best GPA, only the first one found is reported. Can you to modif the program so that it reports all students having the highest GPA?

	原程序只能求出一名 `GPA` 最高的同学, 而实际上可能存在好几位同学并列第一的情况。我们需要对原程序进行修改，使其能够显示所有并列第一的同学的信息。

<br>

##	思路

*	首先从文件 `stu.dat` 读取信息, 得到 `infoList`

	```python
	filename = 'stu.dat'
	with open(filename) as f:
		infoList = f.read().split('\n')
	```

*	通过 `infoList` 中的每一条 `info`, 逐个构造学生对象 `stu`, 并形成数组 `stuList`
	
	```python
	stuList = []
	for info in infoList:
		if info != '':
			# 每一条 info 的格式是 'name\thours\tqpoints'
			stu = Student(info)
			stuList.append(stu)
	```

*	根据 `stu.getGPA()` 对 `stuList` 进行降序排序

	```python
	sortedStuList = sorted(stuList, key=lambda stu: stu.getGPA(), reverse=True)
	```

*	最后打印出所有并列第一的学生的信息

<br>

##	程序运行方法

*	进入 `src` 文件夹, 然后运行 `student.py`

	```bash
	$ python3 student.py
	```

<br>

##	运行结果演示

![student](https://github.com/jJayyyyyyy/USTC-2018-Smester-1/blob/master/Python/homework/hw04/part1/assets/student.png)

<br>

##	代码及注释

*	`student.py`, 程序入口

	```python
	#!/usr/bin/python3
	# -*- coding: utf-8 -*-

	class Student(object):
		"""构造函数, 从 info 中解析出 name, hours, qpoints, 并计算出 GPA"""
		def __init__(self, info):
			# 每一条 info 的格式是 'name\thours\tqpoints'
			name, hours, qpoints = info.split('\t')
			self.name = name
			self.hours = float(hours)
			self.qpoints = float(qpoints)
			# 根据公式计算 GPA
			self.GPA = self.qpoints/self.hours

		# 返回学生姓名
		def getName(self):
			return self.name

		# 返回学时
		def getHours(self):
			return self.hours

		# 返回 quality points
		def getQPoints (self):
			return self.qpoints

		# 返回 GPA
		def getGPA(self):
			return self.GPA

		# 打印学生信息
		def show(self):
			print('%s: %.2f' % (self.name, self.GPA) )

	if __name__ == '__main__':
		# 首先从文件 `stu.dat` 读取信息, 得到 `infoList`
		filename = 'stu.dat'
		with open(filename) as f:
			infoList = f.read().split('\n')

		# 通过 `infoList` 中的每一条 `info`, 逐个构造学生对象 `stu`, 并形成数组 `stuList`
		stuList = []
		for info in infoList:
			if info != '':
				# 每一条 info 的格式是 'name\thours\tqpoints'
				stu = Student(info)
				stuList.append(stu)

		print('排序前的 [姓名, GPA]')
		for stu in stuList:
			stu.show()

		# 根据 `stu.getGPA()` 对 `stuList` 进行降序排序
		sortedStuList = sorted(stuList, key=lambda stu: stu.getGPA(), reverse=True)

		print('\n排序后的 [姓名, GPA]')
		for stu in stuList:
			stu.show()

		# 最后打印出所有并列第一的学生的信息
		print('\nGPA 最高的同学(们)')
		highestGPA = sortedStuList[0].getGPA()
		for stu in sortedStuList:
			if( stu.getGPA() == highestGPA ):
				stu.show()
	```

##	参考资料

*	[Python Docs: Sorting HOW TO](https://docs.python.org/3/howto/sorting.html#sortinghowto)
