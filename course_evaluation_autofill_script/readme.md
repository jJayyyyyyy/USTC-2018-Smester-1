##	简介

*	每一门课程结束后, 软院信息化平台都会要求我们填写一个长长的问卷调查, 地址是

	http://mis.sse.ustc.edu.cn/Teaching/Survey/SurveyInfo/MyForceAttendList.aspx

	如果不完成这个问卷调查, 就没法正常使用信息化平台(每次登陆都会强制跳转到这里, 而且无法退出)

*	下面这个脚本可以帮你省去填写问卷的时间

	```javascript
	function doSelection(table, len)
	{
		for( var i = 0; i < len; i++ )
		{
			var child = table.children[i];
			var tr = child.getElementsByTagName("tr")[1];
			if( tr )
			{
				var radio = tr.getElementsByTagName("input")[0];
				radio.click();
			}
		}
	}

	function doTextarea(tale, len)
	{
		for( var i = 0; i < len; i++ )
		{
			var child = table.children[i];
			var td_list = child.getElementsByTagName("td");
			var td_len = td_list.length;
			var td = td_list[td_len - 1];
			var textarea = td.getElementsByTagName("textarea")[0]
			textarea.value = "好";
		}
	}

	var ifm = document.getElementsByTagName("iframe")[0];
	var doc = ifm.contentDocument;
	var table = doc.getElementById("ext-gen56");
	var len = table.children.length;
	doSelection(table, len);
	doTextarea(table, len);
	```

	<br>

##	食用方法

1.	以 `Chrome` 浏览器为例, 首先按下 `F12` 进入开发者工具, 然后点击 `Console` 标签

2.	登陆信息化系统, 进入问卷调查页面

3.	点击表格中的【填写反馈】, 打开问卷填写窗口 ()

4.	将上一节的代码复制到开发者工具的 `Console` 中, 按下 `Enter` 执行脚本

	你会发现问卷已经填写好了, 评分是 `5`, 反馈意见是 `好`

5.	点击左上角的保存按钮

6.	重复 `1~5`, 完成所有问卷的填写

	<br>