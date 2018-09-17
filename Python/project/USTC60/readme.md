##	Intro

最近正值科大校庆，昨天看到有同学分享了一个[链接](http://static.zhang-chu.com/kd/index.html)，可以在自己的头像中加入科大60年校庆的图标。

由于之前浙大校庆的时候写过一个类似的小程序，稍加改造即可实现上面描述的功能。

这个程序代码本身并不复杂，可以作为入门 `Python` 的练手项目。

同时，也借此机会祝科大生日快乐, Happy Birthday to USTC! 🍰🎂🎉

<br>

##	Dependency

https://github.com/jJayyyyyyy/USTC-2018-Smester-1/blob/master/Python/project/USTC60/demo/sp1.png

*	![badge](https://github.com/jJayyyyyyy/USTC-2018-Smester-1/blob/master/Python/project/USTC60/demo/Python-3.4%2B-brightgreen.svg)

*	Pillow

	```bash
	$ pip3 install pillow
	```

<br>

##	Usage

1.	长按微信头像保存, 然后发送到电脑, 默认是 640x640 的 jpg 图像, 假设图片文件名 filename 是 `portrait.jpg`

	下载 `ustc60.png` 和 `stamp.py`, 此时当前目录包含如下文件

	```
	-
	|--- portrait.jpg
	|--- stamp.py
	|--- ustc60.png
	```

2.	运行程序

	```bash
	python3 stamp.py portrait.jpg
	```

3.	程序运行后, 会生成 `stamped_portrait.jpg`, 这就是加上校庆图标后的新头像

<br>

##	Demo

<table>
	<tr>
		<td><img src="https://github.com/jJayyyyyyy/USTC-2018-Smester-1/blob/master/Python/project/USTC60/p1.png" width="320"/></td>
		<td><img src="https://github.com/jJayyyyyyy/USTC-2018-Smester-1/blob/master/Python/project/USTC60/demo/sp1.png" width="320"/></td>
	</tr>
	<tr>
		<td><img src="https://github.com/jJayyyyyyy/USTC-2018-Smester-1/blob/master/Python/project/USTC60/p2.png" width="320"/></td>
		<td><img src="https://github.com/jJayyyyyyy/USTC-2018-Smester-1/blob/master/Python/project/USTC60/demo/sp2.png" width="320"/></td>
	</tr>
	<tr>
		<td><img src="https://github.com/jJayyyyyyy/USTC-2018-Smester-1/blob/master/Python/project/USTC60/p3.png" width="320"/></td>
		<td><img src="https://github.com/jJayyyyyyy/USTC-2018-Smester-1/blob/master/Python/project/USTC60/demo/sp3.png" width="320"/></td>
	</tr>
</table>

<br>

##	Workflow

1.	命令行参数 `argv[1]` 是头像图片的文件名, `img` 是其对应的 `Image对象` 的实例

2.	由于 `ustc60.png` 是 `886x886` 的尺寸, 我们将 `img` 也进行扩展(`resize()`)

3.	以 `RGBA mode` 打开 `ustc60.png`, 保留原有的透明度信息, 获得 `stamp` 对象

4.	将 `stamp` 盖到 `img` 上面, 由于原来的 `ustc60.png` 中间是透明的, 所以能够显示原头像中间的一个圆

	而 `ustc60.png` 的可见部分, 即 `60周年校庆` 图标, 将会覆盖 `portrait.jpg` 中对应的区域

5.	生成含有校庆标志的图片

<br>

##  Reference

*	[RGBA color space](https://en.wikipedia.org/wiki/RGBA_color_space)

*	[Image.convert()](https://pillow.readthedocs.io/en/latest/reference/Image.html#PIL.Image.Image.convert)

*	[RGBA mode](https://pillow.readthedocs.io/en/latest/handbook/concepts.html#concept-modes)

<br>

##	PS

*	本项目改编自另一个 repo: [zju_portrait](https://github.com/jJayyyyyyy/zju_portrait), 其灵感来自于浙大校庆，当时浙大同学的头像的右下角都印上了校徽

	若使用该方法, 则最后的效果如下

	<table>
		<tr>
			<td><img src="https://github.com/jJayyyyyyy/USTC-2018-Smester-1/blob/master/Python/project/USTC60/demo/sp4_rb.png" width="320"/></td>
			<td><img src="https://github.com/jJayyyyyyy/USTC-2018-Smester-1/blob/master/Python/project/USTC60/demo/sp4_rb.png" width="320"/></td>
		</tr>
	</table>

<br>

*	感谢王鹏焜、文晓雅、蔡怡雯同学提供的头像

	感谢 `Octocat`

<br>
