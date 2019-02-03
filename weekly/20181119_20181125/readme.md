时间: 20181119 ~ 20181125

##	新闻

<br>

##	资源推荐

*	公众号: Python数据分析

<br>

##	其他

*	[Mac OSX终端走shadowsocks代理](https://github.com/mrdulin/blog/issues/18)

	```
	$ vim ~/.zshrc
	# proxy list
	alias proxy='export all_proxy=socks5://127.0.0.1:1080'
	alias unproxy='unset all_proxy'
	
	$ source ~/.zshrc
	$ curl cip.cc
	$ proxy
	$ curl cip.cc
	$ unproxy
	$ curl cip.cc
	```

*	[每次运行 Matplotlib 弹出警告](https://www.jianshu.com/p/2769f148983c)

	[matplotlib taking time when being imported](https://stackoverflow.com/questions/34771191/matplotlib-taking-time-when-being-imported)

    ```
    cd ~/.matplotlib
    rm fontList.cache fontList.py3k.cache
    rm -rf tex.cache 
    ```

    <br>
