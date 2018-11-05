时间: 20181008 ~ 20181014

##	新闻

*	[Parkour Atlas](https://www.youtube.com/watch?v=LikxFZZO2sk)

	BostonDynamics 的 Atlas 又有了新的进步.
	
	我们知道, 10 个月前, Atlas 学会了让人咋舌的后空翻. 而5个月前的上一次亮相, Atlas 只是展示了如何在草地上跑步, 并且在跑步的时候可以调整身体重心, 似乎没有什么惊艳的地方(误)
	
	这一次, Atlas 可以连续跳上多个平台, 而且可以在这个过程中调整重心, 使姿态更加稳定. 这对人类来说可能没什么, 但是对于机器人, 这可是一个不小的进步.

	附: 评论区的彩蛋
	
	> I'm surprised y'all weren't shooting tennis balls at it while it tried jumping.

<br>

##	资源推荐

*	[Python3 Docs --- functions](https://docs.python.org/3.7/library/functions.html)

*	[Python Programming An Introduction to Computer Science 3rd Edition](http://ssea.ustcsz.edu.cn:443/UploadFiles/courseResources/20180912/Python.Programming.An.Introduction.to.Computer.Science.3rd.Edition_2018912212757838.pdf)

	书还没怎么看, 这里不能算推荐吧(因为在书中出现了 `windowing system`, 不知道巨硬怎么想)
	
	不过在书的 P19 (pdf P35) 提到了 `chaos functions` 挺有意思的
	
	```
	def main():
	x = eval(input('Enter a number between 0 and 1: '))
	for i in range(10):
		x = 3.9 * x * (1 - x)
		print(x)
	```
	
	> The function computed by this program has the general form: k(x)(l- x), where k in this case is 3. 9. This is called a logistic function. It models certain kinds of unstable electronic circuits and is also sometimes used to model population variation under limiting conditions. Repeated application of the logistic function can produce chaos.

<br>

##	其他

*	> IA32 is short for "Intel Architecture, 32-bit", sometimes also called i386

	https://baike.baidu.com/item/IA-32
	
	https://en.wikipedia.org/wiki/IA-32
	
*	[C语言中的逻辑右移和算术左移](https://blog.csdn.net/zyings/article/details/47084485)

	逻辑左移，算术右移

*	python, 参数，引用参数，费引用参数

	```python
	def change(param):
		if isinstance(param, list):
			l[0] = 4
	
	l = [1, 2, 3]
	t = (1, 2, 3)
	change(l)
	change(t)
	print(l, t)
	```

	Python参数传递方式：传递对象引用（传值和传址的混合方式），如果是数字，字符串，元组则传值；如果是列表，字典则传址；
	
	copy使用场景：列表或字典，且内部元素为数字，字符串或元组
	
	deepcopy使用场景：列表或字典，且内部元素包含列表或字典
	
	https://www.cnblogs.com/CheeseZH/p/5165283.html

	[functions, P53](http://ssea.ustcsz.edu.cn:443/UploadFiles/courseResources/20180928/Chapter06_201892816364922.pdf), 参数为 list 时, `+` 和 `append` 的区别
	
	下面举几个例子
	
	```python
	# 数字，字符串，元组则传值, 出函数后肯定不变
	# 列表，字典看情况
	
	# 出函数后 v1, v2 不变
	def fun1(v1, v2):
		v1 = [2]
		v2 = {2:'2'}
	
	# 变
	def fun2(v1, v2):
		v1[0] = 2		# 出函数后 v1 变成了 [2], 而不是 [1]
		v2[1] = '2'		# 出函数后 v1 变成了 {1:'2'}, 而不是 {1:'1'}
		
	# 变
	def fun3(v1, v2):
		v1.append(2)	# 出函数后 v1 变成 [1, 2], 而不是 [1]
		v2[2] = '2'		# 出函数后 v2 变成 {1:'1', 2:'2'}, 而不是 {1:'1'}
	
	# 另外, if a is b, 用于判断 a, b 是否为同一个 obj, 即两者是否有同一个id, id(a) == id(b)
	# 而 if a == b 是判断 a 和 b 的值是否相等
	
	# Python 的 is 相当于 Java 的 ==
	# Python 的 == 相当于 Java 的 .isEqual()
	
	v1 = [1]
	v2 = {1:'1'}
	
	fun1(v1, v2)
	print(v1, v2)		# [1] {1: '1'}
	
	v1 = [1]
	v2 = {1:'1'}
	
	fun2(v1, v2)
	print(v1, v2)		# [2] {1: '2'}
	
	v1 = [1]
	v2 = {1:'1'}
	
	fun3(v1, v2)
	print(v1, v2)		# [1, 2] {1: '1', 2: '2'}
	```

*	python 判断类型

	isinstance(l, list)
	
	[isinstance(object, classinfo), 可用于 subclass](https://docs.python.org/3.7/library/functions.html#isinstance)
	
	https://segmentfault.com/q/1010000000127305

*	[id(), Return the “identity” of an object](https://docs.python.org/3.7/library/functions.html#id)

	追踪对象id	

*	[python, eval()](https://docs.python.org/3.7/library/functions.html#eval)

*	Windows 底部任务栏，放到侧边时，会在2018年10月10日发生边框溢出，需要修改时间格式

*	什么是 `rogue like` 游戏

*	[汇编总结:lea指令](https://my.oschina.net/guonaihong/blog/508907)

	[知乎: 汇编语言中mov和lea的区别有哪些？](https://www.zhihu.com/question/40720890)

*	[Shift (sal, shl, sar, shr), IA-32 Assembly Language Reference Manual, Oracle](https://docs.oracle.com/cd/E19455-01/806-3773/instructionset-27/index.html)

*	[x64 Cheat Sheet, Brown University](https://cs.brown.edu/courses/cs033/docs/guides/x64_cheatsheet.pdf)

*	[asm64-handout, CMU](https://www.cs.cmu.edu/~fp/courses/15213-s07/misc/asm64-handout.pdf)

*	[CS:APP3e Student Site](http://csapp.cs.cmu.edu/3e/students.html)

*	[vim cheatsheet](https://www.cs.cmu.edu/~213/recitations/vi-vim-cheat-sheet.gif)

*	[Unix/Linux Command Reference](https://www.cs.cmu.edu/~213/recitations/fwunixref.pdf)

*	[CSAPP, Resources](https://www.cs.cmu.edu/~213/resources.html)

*	[Beej's Quick Guide to GDB](http://beej.us/guide/bggdb/)

*	[Hypersonic Missile Nonproliferation](https://www.youtube.com/watch?v=FyUTNRIuAqc)

<br>