**Docker quick start ( Docker for Mac )**

<br>

##	安装 `Docker`

*	下载 `Docker` 安装包

	安装包下载地址是: [docker store](https://store.docker.com/editions/community/docker-ce-desktop-mac), 需要先注册才能下载

	下载好 `.dmg` 后，按照 [docker for mac 安装文档](https://docs.docker.com/docker-for-mac/install/) 进行操作即可

*	设置 `Proxy`

	由于众所周知的原因，国内下载 `TF` 很慢。一个方法是寻找国内的云镜像，以前似乎可以通过 `https://www.daocloud.io/mirror` 进行加速下载(未试验)。另一方面，我们可以设置代理从而下载 `TF`

	首先在 `status bar` 找到 `docker` 的小鲸鱼，然后进入 `Preferences--->Proxy--->Manual Proxy Configuration`, 其中的 `http` 和 `https` 都设置好后，就可以通过代理，加速下载镜像了。

<br><br>

##	安装 `TensorFlow Docker Image`

*	下载 `TF` 镜像

	根据 [TF 安装文档](https://www.tensorflow.org/install/docker)，当我们装好 `docker` 之后，接下来要做的是在命令行输入

	```bash
	$ docker pull tensorflow/tensorflow:latest-py3
	```

	注意加上 `:latest-py3`, 否则默认下载的是 `TF for py2.7`, 而 `Python3.4+` 无法使用 `TF`

*	测试

	镜像下载完成后，输入如下命令后，会显示 `TF` 的版本号，如 `1.11`

	```bash
	$ docker run -it --rm tensorflow/tensorflow:latest-py3 \
	python3 -c "import tensorflow as tf; print(tf.__version__)"
	```

<br><br>

##	其他

*	层级关系

	`docker --- image --- container`
	
	// 每一个 image 相当于一个 linux 系统，每个 container 相当于一个 user

*	保留数据

	根据 [Dokcer 常用命令工作原理](https://www.hi-linux.com/posts/44544.html)，每一次使用 `docker run` 都会增加一个 `container_id`，相当于 `create + start`。由于每个 `container` 之间是相互隔离的，也就是说，

	```bash
	# 将 container_id 缩写为 cid

	$ docker run --it image-name bash
	root@cid1:# touch file1
	root@cid1:# logout

	$ docker run --it image-name bash
	root@cid2:# ls

	# 没有 container1 里面的 file1
	```

	如果我们还想继续使用已有的 `container1`，就需要 `exec`

	```
	# 首先查看已有的 cid
	$ docker ps -a

	# 启动某个 cid
	$ docker start cid

	# 进入 cid
	$ docker exec -it cid bash

	# 退出 cid 后再进入 cid，可以看到之前新建的文件还在
	```

	<!-- image -> container 有点像多层的 `git`, 而 container 之间就像不同的 branch -->

*	删除 `container`

	每一次新建 `container` 会增加一部分数据(比 `commit` 要少)，如果我们要删除无用的 `container`，根据 [How to Remove Docker Images and Containers](https://tecadmin.net/remove-docker-images-and-containers/)，我们需要这么做

	```bash
	$ docker stop cid
	$ docker rm cid
	```

	如果要删除所有 `container`

	```bash
	$ docker stop $(docker ps -a -q)
	$ docker rm $(docker ps -a -q)
	```

*	安装软件

	这个 `TF docker image` 是基于 `Ubuntu 16.04` 建立的

	```bash
	$ docker exec --it image-name bash
	root@cid:# lsb_release -a
	...
	Ubuntu 16.04.5 LTS
	...
	```

	所以如果我们要安装其他软件，使用 `apt-get install` 命令即可
	
	```
	# 安装vim
	apt-get update
	apt-get intall vim
	```

	[在容器中安装新的程序](http://www.docker.org.cn/book/docker/docker-install-package-9.html)

*	端口映射

	docker启动新容器并运行ssh服务，将宿主机的6666端口映射为ssh服务端口22

	https://www.jianshu.com/p/02a5438f9d4e

	docker run -d -it -p 6666:22 --name ussh ubuntu_base_ssh /bin/start.sh

<br><br><br><br>

**Jupyter quick start**

<br>

##	安装

	`TF` 的 `image` 已经集成了 `Jupyter`, 不需要自己安装
	
	如果要在其他 `image` 里面安装 `Jupyter`，使用 `pip3` 或者 `Anaconda` 即可

<br>

##	运行

*	假设现在没有任何 container，我们重新运行一个 image，如果最后不加 bash，那么这个image会自动运行一个 run_jupyter.sh 脚本

	```bash
	# jupyter 默认监听 8888 端口
	# 把外部的 80 映射到 docker 里面的 8888，这样浏览器直接用 127.0.0.1 即可访问
	$ docker run -it -p 80:8888 tensorflow/tensorflow:latest-py3			# 自动运行 jupyter server
	# $ docker run -it -p 80:8888 tensorflow/tensorflow:latest-py3 bash	# 不运行 jupyter server
	
	# 如果 80 端口已经被占用，则需要找到监听该端口的 cid80, 然后
	# $ docker stop cid80
	```

	这样就得到了第一个容器的cid，记下来，或者通过 docker ps -a 查看

	下一次就可以通过 start - exec 进入 container 了，而且这个tf容器会默认运行一个 jupyter server
	
	```
	$ docker start cid
	$ docker exec -it cid bash
	root@cid:notebooks# jupyter notebook list	# 显示正在运行的 jupyter notebook server
	```

*	修改端口(略)

	```bash
	root@cid:notebooks# jupyter notebook --port 9876 --allow-root
	```

*	设置密码

	从浏览器进入 jupyter 需要 token 或者 password，每次都用token就比较麻烦，我们可以设置

	方法1是通过浏览器设置密码

	```bash
	# 获得 token
	root@cid:# jupyter notebook list
	... 0.0.0.0:8888/?token=abcdefg ...
	
	# 把 abcdefg 粘贴到浏览器最下面的表格，然后设置新密码，登录后，通过右上角的 Quit 退出服务器，再重新 start -exec
	$ docker start cid
	$ docker exec -it cid bash
	# 现在在浏览器上就可以用密码登录了
	```
	
	方法2，通过命令行设置密码
	
	```bash
	root@cid:# jupyter notebook password
	# 然后输入密码并确认
	
	# 退出重启 container
	root@cid:# exit
	exit
	$ docker restart cid
	# 现在在浏览器上就可以用密码登录了
	```

	jupyter将会在 `/root/.jupyter/jupyter_notebook_config.json` 中存储 `sha1(password)`

<br><br><br><br>

##	备用参考链接

*	[把jupyter-notebook装进docker里](https://www.jishux.com/p/a57631d9bfeeb4ae)

*	[修改TensorFlow官方docker image的jupyter登陆密码](https://blog.csdn.net/yangxuan0261/article/details/74276007)

*	[在 docker 中运行 Jupyter notebook](https://blog.windrunner.me/programming/jupyter-docker.html)

*	[Docker之容器常见操作](http://blog.51cto.com/qiangsh/2162565)

*	[图解 Docker 常用命令工作原理](https://www.hi-linux.com/posts/44544.html)

*	[docker rm container id](https://www.google.com/search?q=docker+rm+container+id)

*	[tf docker](https://www.tensorflow.org/install/docker)

*	[Jupyter 官方文档](https://jupyter.org/documentation)

*	[Anaconda, 水蟒](http://dict.youdao.com/w/anaconda)
