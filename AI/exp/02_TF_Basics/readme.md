TensorFlow 基础编程

##	名词解释

*	TF系统架构

	TODO: 截图与说明

*	Tensor, 张量

	高维数组

*	什么是 rank

	阶数, 数组维数

*	编程模型

	TODO: 截图与说明

	*	边

	*	节点

	*	图

	*	会话

	*	变量

	*	设备

	<br>

##	基本练习

*	流程图

	TODO: 创建会话-创建图-创建op-启动会话-run

*	`hello world`

	```python
	import tensforflow as tf

	hello = tf.constant('hello world')
	with tf.Session() as sess:
		result = sess.run(hello)
		print(result)
		# b'hello world'
	```

*	`tf.add`, 标量加法

	```python
	import tensforflow as tf

	scaleA = tf.constant(1)
	scaleB = tf.constant(2)
	# 定义标量加法op
	scaleAdd = tf.add(scaleA, scaleB)

	matrixA = tf.constant([1, 2])
	matrixB = tf.constant([3, 4])
	# 定义矩阵(向量)加法op
	matrixAdd = tf.add(matrixA, matrixB)

	with tf.Session() as sess:
		result = sess.run(scaleAdd)
		print(result)
		result = sess.run(matrixAdd)
		print(result)
	print(result)
	```

*	`tf.Variable`, 变量

	```python3
	import tensforflow as tf

	var1 = tf.Variable(0)
	var2 = tf.add(var1, 2)
	updateVar1 = tf.assign(var1, var2)

	# 定义初始化变量的op
	initVar = tf.global_variables_initializer()

	with tf.Session() as sess:
		# 首先初始化变量
		sess.run(initVar)
		result = sess.run(updateVar1)
		print(result)
	```

*	`c = a - b`, 标量减法

	```python
	import tensorflow as tf

	a = tf.Variable(3.)
	b = tf.Variable(2.)
	c = tf.subtract(a, b)
	init = tf.global_variables_initializer()

	with tf.Session() as sess:
		sess.run(init)
		result = sess.run(c)
		print(result)
	```

*	`c = a * b`, 标量乘法

	```python
	import tensorflow as tf

	a = tf.Variable(3.)
	b = tf.Variable(4.)
	c = tf.multiply(a, b)
	init = tf.global_variables_initializer()

	with tf.Session() as sess:
		sess.run(init)
		result = sess.run(c)
		print(result)
	```

*	`c = a / b`, 标量除法

	```python
	import tensorflow as tf

	a = tf.Variable(3.)
	b = tf.Variable(2.)
	c = tf.div(a, b)
	init = tf.global_variables_initializer()

	with tf.Session() as sess:
		sess.run(init)
		result = sess.run(c)
		print(result)
	```

*	矩阵加法(同标量加法)

	计算 `A3 = A1 + A2`, 其中 `A1` 是 `2x2` 的矩阵, `A2` 是 `2x2` 的矩阵

	```python
	import tensorflow as tf

	A1 = tf.Variable([[2, 2], [3, 3]])
	A2 = tf.Variable([[1, 1], [2, 2]])
	A3 = tf.add(A1, A2)
	init = tf.global_variables_initializer()

	with tf.Session() as sess:
		sess.run(init)
		result = sess.run(A3)
		print(result)
	```

*	矩阵乘法

	计算 `A3 = A1 · A2`, 其中 `A1` 是 `3x2` 的矩阵, `A2` 是 `2x2` 的矩阵

	```python
	import tensorflow as tf

	A1 = tf.Variable([[1, 1], [2, 2], [3, 3]])
	A2 = tf.Variable([[1, 1], [2, 2]])
	A3 = tf.matmul(A1, A2)
	init = tf.global_variables_initializer()

	with tf.Session() as sess:
		sess.run(init)
		result = sess.run(A3)
		print(result)
	```

*	`tf.placeholder`, 占位符

	```python
	import tensforflow as tf
	# 从上一个例子可以看出, 变量是最后统一初始化的, 一开始的声明则类似于结构体
	# 感觉只是描绘了逻辑关系, 没有实际占用那么多的空间
	# 占位符也是类似, 直到最后才用 feed_dict 给它传入数据
	
	var1 = tf.placeholder('float')
	var2 = tf.placeholder('float')
	# 定义乘法 op
	var3 = tf.multiply(var1, var2)

	with tf.Session() as sess:
		result = sess.run(var3, feed_dict={var1:1., var2:2.})
		print(result)
	```

*	`get_shape()` 与 `tf.rank()`

	```python
	import tensforflow as tf
	# rank 就是 tensor 的阶数, 也可以理解为维数
	# shape 就是每一维里面有几个分量
	
	# var3d 是一个三维张量, shape=(1, 2, 3), rank=size(shape)=3
	var3d = tf.constant([[[1.0, 2.0, 3.0], [4.0, 5.0, 6.0]]])
	getRank = tf.rank(var3d)

	with tf.Session() as sess:
		result = sess.run(getRank)
		print(var3d.get_shape())    # (1, 2, 3)
		print(result)               # 3
	```

*	计算 `z = e ^ x`

	```python
	import tensorflow as tf

	x = tf.placeholder('float')
	# # 计算 e 的 x 次方，参数必须是浮点数
	z = tf.exp(x)

	with tf.Session() as sess:
		result = sess.run(z, feed_dict={x:1})
		print(result)
	```

*	计算 `z = x ^ y`

	```python
	import tensorflow as tf
	# z = x ^ y = e ^ (y * ln(x))

	x = tf.placeholder('float')
	y = tf.placeholder('float')

	lnx = tf.log(x)
	expo = tf.multiply(y, lnx)
	z = tf.exp(expo)

	with tf.Session() as sess:
		result = sess.run(z, feed_dict={x:2., y:4.})
		print(result)

*	`concat`, 拼接

	https://www.tensorflow.org/api_docs/python/tf/concat

	```python
	import tensorflow as tf
	t1 = [[1, 2, 3], [4, 5, 6]]  
	t2 = [[7, 8, 9], [10, 11, 12]] 

	t3 = tf.concat([t1, t2], 1)  # 1, 行不变, 列增加

	with tf.Session() as sess:
		result = sess.run(t3)
		print(result)            # [[1, 2, 3,  7,  8,  9]
		                         #  [4, 5, 6, 10, 11, 12]]
		print(t3.get_shape())    # (2, 6)

		# 若 tf.concat([t1, t2], 0), 则列不变, 行增加
		# [[ 1,  2,  3]
		#  [ 4,  5,  6]
		#  [ 7,  8,  9]
		#  [10, 11, 12]]
		# (4, 3)
	```

*	`image`, 图像

	https://www.tensorflow.org/api_guides/python/image

	```python
	import matplotlib.image as mpimg
	import tensorflow as tf
	
	filename = 'example.jpg'
	image = mpimg.imread(filename)

	x = tf.Variable(image, name='x')
	init = tf.global_variables_initializer()

	with tf.Session() as sess:
		sess.run(init)
		result = sess.run(x)
		print(x.get_shape)
		# (201, 268, 4)
		# (height, width, channels)
	```

	<br>

##	线性回归原理和实践

*	TODO

	<br>

##	课后提问

*	TODO

	<br>

##	参考资料

*	[tensorflow python api docs](https://www.tensorflow.org/api_docs/python/tf)
