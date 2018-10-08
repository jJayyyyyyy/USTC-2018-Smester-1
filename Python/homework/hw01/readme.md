##	题目

*	Write a program to calculate the volume and surface area of a sphere from its radius, given as input. Here are some formulas that might be useful:

	```
	V = (4 / 3) * pi * r^3
	A = 4 * pi * r^2
	```

*	Then write your.py files, carry out them and give me the results. 

<br>

##	程序说明

*	功能

	由用户输入球的半径，根据相关公式，最后由程序输出球的体积和表面积

*	代码

	```python
	#!/usr/bin/python3
	# -*- coding: utf-8 -*-
	from math import pi as PI

	class Solution(object):
		# 构造函数
		def __init__(self):
			self.radius = self.get_radius()
			self.volume = self.get_volumn()
			self.area = self.get_area()

		# 获取半径
		def get_radius(self):
			radius = int(input('Please input radius: '))
			if radius < 0:
				print('Invalid radius!')
				exit()
			else:
				return radius

		# 计算体积
		def get_volumn(self):
			volume =  PI * pow(self.radius, 3) * 4 / 3
			return volume

		# 计算面积
		def get_area(self):
			area = PI * pow(self.radius, 2) * 4
			return area

		# 显示结果
		def display(self):
			print("radius:\t%.2lf" % self.radius)
			print("volume:\t%.2lf" % self.volume)
			print("area:\t%.2lf" % self.area)

	# 测试
	if __name__ == '__main__':
		solution = Solution()
		solution.display()
	```

*	运行结果截图

	![sphere](https://github.com/jJayyyyyyy/USTC-2018-Smester-1/blob/master/Python/homework/hw01/assets/sphere.jpg)

<br>