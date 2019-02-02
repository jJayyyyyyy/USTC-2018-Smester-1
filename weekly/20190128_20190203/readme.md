时间: 20190128 ~ 20190203

##	新闻

*	[流星雨服务](https://www.v3.co.uk/v3-uk/news/3069575/japanese-firm-sends-micro-satellites-into-space-to-deliver-artificial-meteor-showers-on-demand)

*	[在监狱里退休的日本老人](https://www.solidot.org/story?sid=59505)

	<br>

##	资源推荐

*	参考: http://www.ruanyifeng.com/blog/2019/02/weekly-issue-42.html

	[Notable](https://github.com/fabiospampinato/notable)

	A note-taking app based on Markdown syntax.

	[为什么电路板大多是绿色的？](http://www.seeedstudio.com/blog/2017/07/23/why-are-printed-circuit-boards-are-usually-green-in-colour/)

*	[Linux 中 TTY 是什么意思](https://www.cnblogs.com/dongguolei/p/7975488.html)

	[What does “TTY” stand for?](https://askubuntu.com/questions/481906/what-does-tty-stand-for)

	<br>

##	其他

*	Sublime Text, Record Macro 录制宏, Key Bindings - User 自定义快捷键

	目标:

	*	新建快捷键, 使得按下 `alt + .` 后, 可以自动完成 `Convert Indentation to Tabs` 的功能

	步骤:

	*	点击 Tools --- Record Macro

	*	点击 View --- Indentation --- Convert Indentation to Tabs

	*	点击 Tools --- Stop Recording Macro, 然后 Save Macro

	*	打开刚才保存的文件, 可以得到如下内容

		```json
		[
			{
				"args":
				{
					"set_translate_tabs": true
				},
				"command": "unexpand_tabs"
			}
		]
		```

		复制以上内容

	*	点击 Preferences --- Key Bindings - User, 参考 Key Bindings - Default, 我们可以写出如下配置文件

		```json
		[
			{
				"keys": ["alt+."],
				"args":
				{
					"set_translate_tabs": true
				},
				"command": "unexpand_tabs"
			}
		]
		```

		保存后即可生效

	参考资料:

	*	https://blog.csdn.net/ROCKMOSTER/article/details/52155613

	*	https://blog.csdn.net/zhezhebie/article/details/71636983

	<br>
