##	题目2: 求 cannonball 的最大高度

*	Modify the cannonball simulation from the chapter so that it also calculates the maximum height achieved by the cannonball.

<br>

##	思路

*	修改 `Projectile` 类, 增加一个 `maxHeight` 属性, 初值设为 `0`.
	
*	每次更新 `posY` 后, 比较 `posY` 和 `maxHeight`, 更新并记录 `maxHeight`
	
	```python
	if self.maxY < self.posY:
		self.maxY = self.posY
	```

<br>

##	程序运行方法

*	进入 `src` 文件夹, 然后运行 `animation.py`

	```bash
	$ python3 animation.py
	```

<br>

##	运行结果演示

![animation](https://github.com/jJayyyyyyy/USTC-2018-Smester-1/blob/master/Python/homework/hw04/part2/assets/animation.gif)

注: 使用了参考资料中的 `Gifox` 对运行动画和结果进行了保存

##	代码及注释

*	本次作业的代码由6个文件组成, 由于代码较多, 报告中只对程序入口文件 `animation.py` 进行说明与展示, 其他文件已放入 `src` 文件夹, 并且在书中都有详细说明, 这里不再赘述

*	`animation.py`, 程序入口

	```python
	#!/usr/bin/python3
	# -*- coding: utf-8 -*-

	# 导入其他的类. 根据功能要求, 将不同的组件划分为不同的类, 并放入不同的文件, 简化主程序
	from graphics import *
	from button import Button
	from shot_tracker import ShotTracker
	from input_dialog import InputDialog

	# 主程序
	def main():
		# 新建主体窗口, 大小为 640x480, 并关闭自动界面刷新
		win = GraphWin('Animation', 640, 480, autoflush=False)
		
		# 坐标重映射
		# 将 X 轴的 [0, 640] 映射为 [-10, 210]
		# 将 Y 轴的 [0, 480] 映射为 [-10, 155]
		win.setCoords(-10, -10, 210, 155)

		# 画出数轴基线
		Line(Point(-10, 0), Point(210, 0)).draw(win)
		for x in range(0, 210, 50):
			Text(Point(x, -5), str(x)).draw(win)
			Line(Point(x, 0), Point(x, 2)).draw(win)


		while True:
			# 获取用户输入, 设置发射角度、初始速度、初始高度
			inputWin = InputDialog(90, 30, 0)

			# 获取下一步选项
			choice = inputWin.interact()

			# 关闭用户输入窗口
			inputWin.close()

			if choice == 'Fire':
				# choice 为 'Fire' 则进入模拟发射过程

				# 设置发射角度、初始速度、初始高度
				angle, vel, height = inputWin.getValues()

				# shot 就是用于模拟炮弹发射过程的对象
				shot = ShotTracker(win, angle, vel, height)

				# 当 shot 的 Y > 0 (位于地平面以上), 且 -10<X<210 (炮弹在显示窗口内)
				while 0 <= shot.getY() and shot.getX() > -10 and shot.getX() <= 210:
					# 以 1/30 s 的时间间隔不断更新 shot 坐标
					shot.update(1/30)

					# 窗口刷新频率设为 30fps 
					update(30)
				
				# 当炮弹 shot 落地后, 在新的窗口中显示 shot 能够到达的最大高度
				maxHeight = "最大高度: %.2f 米" % shot.proj.maxY
				maxHeightWin = GraphWin('Max Height', 240, 180)
				Text(Point(120, 90), maxHeight).draw(maxHeightWin)
			else:
				# 若 choice 为 'Quit' 则退出程序
				break

	if __name__ == '__main__':
		main()
	```

##	参考资料

*	[graphics.py source code](http://mcsp.wartburg.edu/zelle/python/graphics.py)

*	[Python Programming: An Introduction to Computer Science](http://mcsp.wartburg.edu/zelle/python/)

*	[Gifox, Delightful GIF Recording and Sharing App for Mac](https://gifox.io/)
