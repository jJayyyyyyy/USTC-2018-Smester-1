#	人工智能实验3: 基于TensorFlow的cpatcha注册码识别

##	实验报告内容

*	给出你自己第一个完整的神经网络构建过程，包括

	*	生成训练数据集
	*	定义网络模型
	*	训练模型参数并保存
	*	读入参数并测试新数据

*	描述实验结果

	<br>

##	神经网络构建过程

*	注:

	感谢 [lpty 的 tensorflow_tutorial-captchaCnn 例程](https://github.com/lpty/tensorflow_tutorial/tree/master/captchaCnn) 和 [Arfer 的 TensorFlow CAPTCHA](https://github.com/Arfer-ustc/captcha), 本次实验的代码由此改编而来

	实验文档采用 `markdown` 格式进行编写

0.	实验环境

	*	Ubuntu 16.04, x64
	*	docker 18.09.0
	*	tensorflow-py3 1.12.0
	*	python 3.5.2
	*	captcha 0.3
	*	PIL 5.3.0
	*	matplotlib 3.0.1
	*	numpy 1.15.4
	*	Jupyter Notebook 5.7.0

1.	生成训练数据集

	*	`Captcha`（全自动区分计算机和人类的图灵测试，俗称验证码）是目前用于区分人和机器主要办法，其工作原理是通过提供模糊或是有歧义的图片，并要求用户进行回答，以此来区分人和机器

		本次实验使用 `Python` 的第三方库 `captcha` 来生成图片验证码。由于计算能力有限，生成的验证码中只包含数字，且验证码长度为 `4`

	*	生成验证码及其对应标签的 `Python` 代码及注释如下

		```python
		import random
		import numpy as np
		from PIL import Image
		from captcha.image import ImageCaptcha

		# 验证码仅包含数字字符
		NUMBER = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9']
		CAPTCHA_LIST = NUMBER
		# 验证码字符串长度为 4
		CAPTCHA_LEN = 4
		# 验证码图片高度为 60px, 宽度为 160px
		CAPTCHA_HEIGHT = 60
		CAPTCHA_WIDTH = 160

		def random_captcha_text(char_set=CAPTCHA_LIST, captcha_size=CAPTCHA_LEN):
			# 生成验证码文本
			captcha_text = [random.choice(char_set) for _ in range(captcha_size)]
			return ''.join(captcha_text)

		def gen_captcha_text_and_image(width=CAPTCHA_WIDTH, height=CAPTCHA_HEIGHT,save=False):
			# 定义验证码图像的尺寸
			image = ImageCaptcha(width=width, height=height)
			# 验证码文本
			captcha_text = random_captcha_text()
			# 生成验证码图像
			captcha = image.generate(captcha_text)
			# 保存图像
			if save:
				image.write(captcha_text, captcha_text + '.jpg')
			captcha_image = Image.open(captcha)
			# 为了加快训练速度，我们还可以将验证码转为灰度图
			captcha_image = captcha_image.convert('L')
			# 转化为np数组
			captcha_image = np.array(captcha_image)
			return captcha_text, captcha_image
		
		if __name__ == '__main__':
			t, im = gen_captcha_text_and_image(save=True)
			print(t, im)
		```

	*	生成的验证码如图

		![captcha_2592](https://github.com/jJayyyyyyy/USTC-2018-Smester-1/blob/master/AI/exp/04_Captcha/assets/captcha_2592.png)

2.	定义网络模型

	*	卷积层的代码如下

		```python
		def cnn_graph(x, keep_prob, size, captcha_list=CAPTCHA_LIST, captcha_len=CAPTCHA_LEN):
			# 三层卷积神经网络计算图
			# keep_prob 是 dropout 的保留比例

			# 首先将图片 reshape 为 4 维向量
			image_height, image_width = size
			x_image = tf.reshape(x, shape=[-1, image_height, image_width, 1])

			# 第 1 层
			# 3x3 的卷积核, 输入为 1, 输出32个特征, 即有 32 个卷积核
			w_conv1 = weight_variable([3, 3, 1, 32])
			# 偏置
			b_conv1 = bias_variable([32])
			# relu 激活函数
			h_conv1 = tf.nn.relu(tf.nn.bias_add(conv2d(x_image, w_conv1), b_conv1))
			# 2x2 的 max 池化层
			h_pool1 = max_pool_2x2(h_conv1)
			# dropout 防止过拟合, 同时加快训练速度
			h_drop1 = tf.nn.dropout(h_pool1, keep_prob)

			# 第 2 层
			# 3x3 的卷积核, 输入为 32, 输出 64 个特征, 即有 2 个卷积核
			w_conv2 = weight_variable([3, 3, 32, 64])
			# 偏置
			b_conv2 = bias_variable([64])
			# relu 激活函数
			h_conv2 = tf.nn.relu(tf.nn.bias_add(conv2d(h_drop1, w_conv2), b_conv2))
			# 2x2 的 max 池化层
			h_pool2 = max_pool_2x2(h_conv2)
			# dropout 防止过拟合, 同时加快训练速度
			h_drop2 = tf.nn.dropout(h_pool2, keep_prob)

			# 第 3 层
			# 3x3 的卷积核, 输入为 64, 输出 64 个特征, 即有 1 个卷积核
			w_conv3 = weight_variable([3, 3, 64, 64])
			b_conv3 = bias_variable([64])
			h_conv3 = tf.nn.relu(tf.nn.bias_add(conv2d(h_drop2, w_conv3), b_conv3))
			# 2x2 的 max 池化层
			h_pool3 = max_pool_2x2(h_conv3)
			h_drop3 = tf.nn.dropout(h_pool3, keep_prob)

			# 全连接层
			# 输入 image_height*image_width*64
			# 输出 1024
			image_height = int(h_drop3.shape[1])
			image_width = int(h_drop3.shape[2])
			w_fc = weight_variable([image_height*image_width*64, 1024])
			b_fc = bias_variable([1024])
			h_drop3_re = tf.reshape(h_drop3, [-1, image_height*image_width*64])
			h_fc = tf.nn.relu(tf.add(tf.matmul(h_drop3_re, w_fc), b_fc))
			h_drop_fc = tf.nn.dropout(h_fc, keep_prob)

			# 输出层
			# 输入 1024
			# 输出 10x4 = 40 (验证码仅含数字)
			w_out = weight_variable([1024, len(captcha_list)*captcha_len])
			b_out = bias_variable([len(captcha_list)*captcha_len])
			y_conv = tf.add(tf.matmul(h_drop_fc, w_out), b_out)
			return y_conv
		```

	*	总体模型图如下

		![model](https://github.com/jJayyyyyyy/USTC-2018-Smester-1/blob/master/AI/exp/04_Captcha/assets/model.jpg)

3.	训练模型参数并保存

	*	优化器计算图

		```python
		def optimize_graph(y, y_conv):
			# 交叉熵计算 loss 注意 logits 输入是在函数内部进行sigmod操作
			# sigmod_cross适用于每个类别相互独立但不互斥，如图中可以有字母和数字
			# softmax_cross 适用于每个类别独立且互斥的情况，如数字和字母不可以同时出现
			loss = tf.reduce_mean(tf.nn.sigmoid_cross_entropy_with_logits(logits=y_conv, labels=y))
			# 最小化loss优化
			optimizer = tf.train.AdamOptimizer(learning_rate=0.001).minimize(loss)
			return optimizer
		```

	*	准确率计算图, 这里判断准确率的标准是所有字符都相同, 当然也有一些算法是按照单个对应位置的字符相同就算正确的方法来计算准确率的, 后者的训练速度更快一点, 但是最后的性能可能比不上前者(4 个字符都相同), 但是个人感觉, 这个差距可以通过多试几个验证码来弥补，因为就算是人类识别，有时候也不能每次都保证正确。

		```python
		def accuracy_graph(y, y_conv, width=len(CAPTCHA_LIST), height=CAPTCHA_LEN):
			# 预测值
			predict = tf.reshape(y_conv, [-1, height, width])
			max_predict_idx = tf.argmax(predict, 2)
			# 实际值(标签)
			label = tf.reshape(y, [-1, height, width])
			max_label_idx = tf.argmax(label, 2)
			correct_p = tf.equal(max_predict_idx, max_label_idx)
			accuracy = tf.reduce_mean(tf.cast(correct_p, tf.float32))
			return accuracy
		```

	*	训练过程

		```python
		def train(height=CAPTCHA_HEIGHT, width=CAPTCHA_WIDTH, y_size=len(CAPTCHA_LIST)*CAPTCHA_LEN):
			# cnn在图像大小是2的倍数时性能最高, 如果图像大小不是2的倍数，可以在图像边缘补无用像素
			# 在图像上补2行，下补3行，左补2行，右补2行
			# np.pad(image,((2,3),(2,2)), 'constant', constant_values=(255,))

			# 在准确度达到 95% 时开始保存模型
			acc_rate = 0.95
			# 按照图片大小申请占位符
			x = tf.placeholder(tf.float32, [None, height * width])
			y = tf.placeholder(tf.float32, [None, y_size])
			# 防止过拟合 训练时启用 测试时不启用, keep_prob 是 dropout 的保留比例
			keep_prob = tf.placeholder(tf.float32)
			# cnn模型
			y_conv = cnn_graph(x, keep_prob, (height, width))
			# 优化器
			optimizer = optimize_graph(y, y_conv)
			# 偏差
			accuracy = accuracy_graph(y, y_conv)
			# 启动会话.开始训练
			saver = tf.train.Saver()
			sess = tf.Session()
			sess.run(tf.global_variables_initializer())
			step = 0
			while 1:
				batch_x, batch_y = next_batch(64)
				sess.run(optimizer, feed_dict={x: batch_x, y: batch_y, keep_prob: 0.75})
				# 每训练 100 次测试一次, 即进行一次性能评估
				if step % 100 == 0:
					batch_x_test, batch_y_test = next_batch(100)
					acc = sess.run(accuracy,feed_dict={x:batch_x_test,y:batch_y_test,keep_prob:1.0})
					print(datetime.now().strftime('%c'), ' step:', step, ' accuracy:', acc)
					# 准确率高于 0.95 时开始保存模型
					if acc > acc_rate:
						model_path = os.getcwd() + os.sep + str(acc_rate) + "captcha.model"
						saver.save(sess, model_path, global_step=step)
						acc_rate += 0.01
						# 当准确率大于 0.99 时结束训练
						if acc_rate > 0.99:
							break
				step += 1
			sess.close()
		```

4.	读入参数并测试新数据

	*	通过训练好的模型, 将验证码图片转化为文本

		```python
		def captcha2text(image_list, height=CAPTCHA_HEIGHT, width=CAPTCHA_WIDTH):
			x = tf.placeholder(tf.float32, [None, height * width])
			keep_prob = tf.placeholder(tf.float32)
			y_conv = cnn_graph(x, keep_prob, (height, width))
			saver = tf.train.Saver()
			with tf.Session() as sess:
				# 读取模型
				saver.restore(sess, tf.train.latest_checkpoint('.'))
				predict = tf.argmax(tf.reshape(y_conv, [-1, CAPTCHA_LEN, len(CAPTCHA_LIST)]), 2)
				vector_list = sess.run(predict, feed_dict={x: image_list, keep_prob: 1})
				vector_list = vector_list.tolist()
				text_list = [vec2text(vector) for vector in vector_list]
				return text_list

		if __name__ == '__main__':
			# 生成测试图片和标签
			text, image = gen_captcha_text_and_image()
			plt.figure('color')
			plt.imshow(image, cmap='gray')
			plt.axis('off')
			# 显示图片
			plt.show()

			# 图片转为灰度图
			image = convert2gray(image)
			image = image.flatten() / 255

			# 输出标签和预测值
			# 输出格式为  
			pred_text = captcha2text([image])
			print('Label:', text, ' Predict:', pred_text)
		```

	<br>

##	实验结果

1.	补充分析

	在进行了 `7900` 个 `step` 的训练之后, 模型达到了 `99%` 的准确率, 每一个 `step` 中用到了 `next_batch(100)`, 即 `batch_count=64`, 因此一共训练了 `7900 * 64 = 505600` 张图片

	同时可以看到, 每经过 `100` 个 `step`, 都会进行一次测试, 每次测试用到了 `next_batch(100)`, 即每次阶段性测试都使用了 `100` 张图片进行测试, 以判断准确率是否达到要求

2.	测试结果截图

	部分测试结果截图如下，其中 `7991` 被识别成了 `2991`, 其他的都识别正确

	![0000](https://github.com/jJayyyyyyy/USTC-2018-Smester-1/blob/master/AI/exp/04_Captcha/assets/0000.png)
	![0263](https://github.com/jJayyyyyyy/USTC-2018-Smester-1/blob/master/AI/exp/04_Captcha/assets/0263.png)
	![2059](https://github.com/jJayyyyyyy/USTC-2018-Smester-1/blob/master/AI/exp/04_Captcha/assets/2059.png)
	![2189](https://github.com/jJayyyyyyy/USTC-2018-Smester-1/blob/master/AI/exp/04_Captcha/assets/2189.png)
	![4293](https://github.com/jJayyyyyyy/USTC-2018-Smester-1/blob/master/AI/exp/04_Captcha/assets/4293.png)
	![4531](https://github.com/jJayyyyyyy/USTC-2018-Smester-1/blob/master/AI/exp/04_Captcha/assets/4531.png)
	![4567](https://github.com/jJayyyyyyy/USTC-2018-Smester-1/blob/master/AI/exp/04_Captcha/assets/4567.png)
	![6613](https://github.com/jJayyyyyyy/USTC-2018-Smester-1/blob/master/AI/exp/04_Captcha/assets/6613.png)
	![6918](https://github.com/jJayyyyyyy/USTC-2018-Smester-1/blob/master/AI/exp/04_Captcha/assets/6918.png)
	![7383](https://github.com/jJayyyyyyy/USTC-2018-Smester-1/blob/master/AI/exp/04_Captcha/assets/7383.png)
	![7991_2991](https://github.com/jJayyyyyyy/USTC-2018-Smester-1/blob/master/AI/exp/04_Captcha/assets/7991_2991.png)
	![8371](https://github.com/jJayyyyyyy/USTC-2018-Smester-1/blob/master/AI/exp/04_Captcha/assets/8371.png)

	注：由于本地机器性能较差，上述实验结果是通过ssh登陆到远程主机后运行得到的，由于没有图形界面，所以只能通过命令行截图的方式展现，另外由于终端透明度设置的问题，背景上会有一些其他窗口的字，还请见谅。

	<br>

##	补充问题

*	灰度怎么转，为什么使用灰度

	可以通过 `PIL.Image.convert('L')` 将图片转为灰度图，也可以将图片转为 `np.array` 后，用 `img = np.mean(img, -1)` 转换为灰度图

	使用灰度图可以减少多余的信息，从而减少计算量

*	如何定义训练的准确率，准确率的定义会不会影响训练

	关于准确率的描述，在 `训练模型参数并保存` 一节中已有描述，即，这里判断准确率的标准是所有字符都相同, 当然也有一些算法是按照单个对应位置的字符相同就算正确的方法来计算准确率的, 后者的训练速度更快一点, 但是最后的性能可能比不上前者(4 个字符都相同), 但是个人感觉, 这个差距可以通过多试几个验证码来弥补，因为就算是人类识别，有时候也不能每次都保证正确。

*	每层的激活函数为什么用 `Relu` 函数不使用 `Sigmoid` 函数

	根据 [为什么使用ReLU而不是sigmoid](https://blog.csdn.net/PKU_Jade/article/details/78213797) 和 [CNN on TensorFlow](https://www.jianshu.com/p/95c79381ab4f), 在 `CNN` 中

	*	`sigmoid` 计算量过大
	*	对于深层网络，`sigmoid` 函数反向传播时，很容易就会出现梯度消失的情况
	*	`Relu` 会使一部分神经元的输出为 `0`，这样就造成了网络的稀疏性，并且减少了参数的相互依存关系，缓解了过拟合问题的发生

	<br>

##	参考资料

*	[lpty 的 tensorflow_tutorial-captchaCnn 例程](https://github.com/lpty/tensorflow_tutorial/tree/master/captchaCnn)

*	[Arfer 的 TensorFlow CAPTCHA](https://github.com/Arfer-ustc/captcha)

*	[TensorFlow API](https://www.tensorflow.org/api_docs/python/)

*	[docker for Ubuntu](https://docs.docker.com/install/linux/docker-ce/ubuntu/)

*	[为什么使用ReLU而不是sigmoid](https://blog.csdn.net/PKU_Jade/article/details/78213797)

*	[CNN on TensorFlow](https://www.jianshu.com/p/95c79381ab4f)

*	[ProcessOn](https://www.processon.com/)

	<br>

##	TODO

*	本次实验为什么不使用 `softmax_cross` 作为 `loss` 而用 `sigmoid_cross` 作为 `loss function`

	代码中有如下注释

	```python
	# 交叉熵计算 loss 注意 logits 输入是在函数内部进行sigmod操作
	# sigmod_cross适用于每个类别相互独立但不互斥，如图中可以有字母和数字
	# softmax_cross 适用于每个类别独立且互斥的情况，如数字和字母不可以同时出现
	```

	但是还没有完全理解, 需要查阅更多资料, 也希望老师和学长学姐能够不吝赐教

*	如果要使用 `softmax_cross` 作为 `loss function`，应该怎么改变训练方法

	<br>
