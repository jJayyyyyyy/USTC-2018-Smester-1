##	题目: gray_scaler, 将彩色图片转为灰度图

*	Write a program that converts a color image to grayscale. The user supplies the name of a file containing a GIF or PPM image, and the program
loads the image and displays the file. At the click of the mouse, the program converts the image to grayscale. The user is then prompted for a file name to store the grayscale image in. 

	打开一幅格式为 `gif` 或 `ppm` 的彩色图像, 用如下公式将其转换为灰度图

	```
	brightness = int(round(0.299r + 0.587g + 0.1 14b))
	```

*	代码及注释 (源文件名为 `my_gray_scaler.py` )

	```python
	from graphics import *

	class MyGrayScaler(object):
		# 构造函数, 注意 graphics 只支持 gif 和 ppm 格式的图片, 默认的图像文件名为 'color.gif'
		def __init__(self, filename='color.gif'):
			# 图像中心位于(200, 200)
			self.img = Image(Point(200, 200), filename)
			width = self.img.getWidth()
			height = self.img.getHeight()
			# 新建一个背景窗口, 长款分别为彩色图像的 2 倍
			self.winImage = GraphWin('Color Image', width*2, height*2)

		# 显示图像
		def showImg(self):
			# 先撤掉(可能)已经画过的图像
			self.img.undraw()
			# 然后在背景窗口中画出 img
			self.img.draw(self.winImage)

		# 进行灰度转换
		def convert(self):
			text = self.setHint('在窗口内单击鼠标进行灰度转换')
			self.winImage.getMouse()

			text.undraw()
			text = self.setHint('转换中...')

			img = self.img
			# 根据公式进行灰度转换
			for x in range(img.getHeight()):
				for y in range(img.getWidth()):
					r, g, b = img.getPixel(x, y)
					grayscale = int(round(0.299*r + 0.587*g + 0.114*b))
					img.setPixel(x, y, color_rgb(grayscale, grayscale, grayscale))
			
			text.undraw()
			text = self.setHint('转换完成, 单击鼠标进入保存窗口')
			self.winImage.getMouse()

		# 设置提示
		def setHint(self, hint=''):
			text = Text(Point(200, 50), hint)
			text.draw(self.winImage)
			return text

		# 保存图像
		def saveImg(self):
			win2 = GraphWin('另存为', 400, 400)
			Text(Point(200, 150), '请输入文件名').draw(win2)
			Text(Point(200, 250), '然后单击空白处退出').draw(win2)
			inputText = Entry(Point(200, 200), 10)
			Text(Point(250, 200), '.gif').draw(win2)
			inputText.setText("gray image")
			inputText.draw(win2)
			win2.getMouse()
			filename = inputText.getText()
			self.img.save(filename+'.gif')

	if __name__ == '__main__':
		# 创建对象
		mgs = MyGrayScaler()
		# 显示彩色图像
		mgs.showImg()
		# 转换为灰度图
		mgs.convert()
		# 保存图像
		mgs.saveImg()
	```

*	运行结果截图

	<img src="https://github.com/jJayyyyyyy/USTC-2018-Smester-1/blob/master/Python/homework/hw03/assets/click_to_start.png" alt="converted" width="480px"><br>

	<img src="https://github.com/jJayyyyyyy/USTC-2018-Smester-1/blob/master/Python/homework/hw03/assets/converted.png" alt="converted" width="480px"><br>

	<img src="https://github.com/jJayyyyyyy/USTC-2018-Smester-1/blob/master/Python/homework/hw03/assets/save_to_file.png" alt="converted" width="480px"><br>

<br>

##	参考

*	[graphics.py source code](http://mcsp.wartburg.edu/zelle/python/graphics.py)

*	[Python Programming: An Introduction to Computer Science](http://mcsp.wartburg.edu/zelle/python/)
