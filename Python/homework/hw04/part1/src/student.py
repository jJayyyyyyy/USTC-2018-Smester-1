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

	def getName(self):
		return self.name

	def getHours(self):
		return self.hours

	def getQPoints (self):
		return self.qpoints

	def getGPA(self):
		return self.GPA

	def show(self):
		"""打印学生信息"""
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
	for stu in sortedStuList:
		stu.show()

	# 最后打印出所有并列第一的学生的信息
	print('\nGPA 最高的同学(们)')
	highestGPA = sortedStuList[0].getGPA()
	for stu in sortedStuList:
		if( stu.getGPA() == highestGPA ):
			stu.show()
