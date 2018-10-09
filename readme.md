##	序

It's my honor and pleasure to share my experience with you.

这里记录了科大软院(苏州)2018年第一学期的学习生活, 欢迎你分享各种笔记和学习资源

欢迎各种 `Issue` 和 `PR` ^_^

<br>

##	Tips

*	教辅系统无法登陆的问题

	mis给出的解决方案是，每次都把 `url` 前面的 `ssea.ustcsz.edu.cn` 手动换成 `219.219.220.50`

	更加便捷的方法是修改 `host` 文件, 这样就能做到自动跳转了

	*	Windows

		打开 C:\Windows\System32\drivers\etc\hosts 文件，在文件最后添加如下内容后保存

		```
		219.219.220.50	ssea.ustcsz.edu.cn
		```

	*	Linux / macOS

		首先打开 hosts 文件

		```
		$ vi /etc/hosts
		```

		然后在文件末尾添加如下内容

		```
		219.219.220.50	ssea.ustcsz.edu.cn
		```

	*	20180924注: 只要能确定文件路径，不需要登录即可GET课件资源，如修改Linux的hosts文件，然后
	
		```bash
		$ wget http://ssea.ustcsz.edu.cn:443/UploadFiles/courseResources/20180917/1.%20Introduction%20to%20Bitcoin_201891713365697.pptx
		```

		即可获取区块链的相关课件(注：课程作业也可以通过这种方式下载，无需验证，所以理论上你可以通过brute force获得所有人提交的作业)

	*	20181001注：晚上8点开始，教辅系统无法登陆，而且国庆期间似乎没有值班人员，无法修复问题。

		问题在于，国庆期间还有需要提交的作业，而且作业只能通过教辅系统提交。这就非常尴 ~~(kēng)~~ 尬 ~~(diē)~~ 了。

		<!-- 怎么感觉自己来到了一所yeji学校 -->

		因此，建议每次作业都尽早提交，并在本地创建副本(题目、格式要求、作业内容等，并上传到 GitHub，这样至少有时间戳证明你是已经做过作业的)

<br>

##  我的课表

![timetable](https://github.com/jJayyyyyyy/USTC-2018-Smester-1/blob/master/assets/timetable.jpg)

![syllabus](https://github.com/jJayyyyyyy/USTC-2018-Smester-1/blob/master/assets/syllabus.png)

*	红色为已选课程，蓝色为旁听课程

*	区块链和人工智能的时间有冲突，周二的区块链无法参加，希望上课的同学帮忙补充下笔记~非常感谢！

<br>

##	电子书、其他资源

*	周再达同学整理的人脸识别，目标检测和目标追踪的论文以及对应的论文解读

	*	https://zhuanlan.zhihu.com/p/44093862
	*	https://zhuanlan.zhihu.com/p/36402362
	*	https://zhuanlan.zhihu.com/p/44781302

TODO: 分类上传电子书

<br>

##  Contributors

*	周再达


(欢迎分享各种笔记和学习资源)

<br>

##	License

[MIT License](https://github.com/jJayyyyyyy/USTC-2018-Smester-1/blob/master/LICENSE)
