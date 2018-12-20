##	准备工作

*	环境搭建

	```bash
	> cd LinuxKernel
	> git clone https://github.com/jJayyyyyyy/linuxnet.git
	> cp linux-3.18.6/vmlinux linuxnet/lab3/vmlinux
	> cd linuxnet/lab3
	> make rootfs
	```

	另外打开一个 `Terminal`, 然后运行 `gdb`

	```bash
	> gdb
	file vmlinux
	target remote:1234
	c
	```

*	`UDP` 流程图

	https://www.linuxidc.com/Linux/2018-09/154366.htm

	*	server

		```
		socket()
		bind()
		recvfrom()
		handle data
		sendto()
		close()
		```

	*	client

		```
		socket()
		sendto()
		recvfrom()
		close()
		```

	<br>

##	UDP 发送数据

*	首先在路径下进入运行 `gdb`, 导入符号表, 并连接到 `remote:1234`

	```bash
	$ gdb
	file vmlinux
	target remote:1234
	```

*	然后根据老师的提示, 在 `net/ipv4/af_inet.c:721` 处的 `inet_sendmsg()` 设置断点, 然后 `continue`

	```bash
	b inet_sendmsg
	c
	```

*	接下来, 回到 `MenuOS` 并依次运行 `udpserver`, `udpclient`

	```
	>> udpserver
	>> udpclient
	```

*	回到 `gdb`, 可以看到程序停在了 `inet_sendmsg` 这个函数。

	```c
	/*
	inet_sendmsg (iocb=0xc7859cbc, sock=0xc7631c00, msg=0xc7859d54, size=1024) at net/ipv4/af_inet.c:723
	http://codelab.shiyanlou.com/source/xref/linux-3.18.6/net/ipv4/af_inet.c#721
	*/

	int inet_sendmsg(struct kiocb *iocb, struct socket *sock, struct msghdr *msg, size_t size)
	{
		struct sock *sk = sock->sk;

		sock_rps_record_flow(sk);

		/* We may need to bind the socket. */
		if (!inet_sk(sk)->inet_num && !sk->sk_prot->no_autobind && inet_autobind(sk))
		{
			return -EAGAIN;
		}

		return sk->sk_prot->sendmsg(iocb, sk, msg, size);
	}
	```

	大致阅读代码后, 我们使用 `next` 进行单步调试, 发现程序会一直运行到 `733` 行

	```c
	/*
	net/ipv4/af_inet.c#733
	*/
	return sk->sk_prot->sendmsg(iocb, sk, msg, size);
	```

	如果我们尝试 `step in` 进入 `sendmsg()` 一探究竟，会发现 `gdb` 其实进入了 `udp_sendmsg()`

	```bash
	si
	udp_sendmsg (iocb=0xc7859cbc, sk=0xc7b58540, msg=0xc7859d54, len=1024) at net/ipv4/udp.c:865
	```

	在进入 `865` 行的 `udp_sendmsg()` 之前, 我们会发现一个问题, 之前明明调用的是 `sendmsg()`, 到这怎么变成了 `udp_sendmsg()`?

	根据 `http://codelab.shiyanlou.com/source/xref/linux-3.18.6/net/ipv4/udp.c#2219` , 我们发现在 `struct proto udp_prot` 这个结构体中, `.sendmsg = udp_sendmsg`, 也就是说如果 `sk` 是一个 `UDP` 的 `socket`, 那么它的 `sendmsg` 的方法就是 `udp_sendmsg()`, 有点像其他面向对象语言里面的重载。知道了这些，我们就可以在这里打个断点, 方便下次调试

	```
	b udp_sendmsg
	```

*	接着我们进入 `udp_sendmsg()`

	http://codelab.shiyanlou.com/source/xref/linux-3.18.6/net/ipv4/udp.c#863

	这个函数比较长, 这里就不粘贴了。我们先大致浏览一下代码, 然后寻找其中的关键点。根据前面实验的经验, `socket buff`, 也就是 `skb` 是一个很重要的结构体, 我们看到它首先出现在了 `net/ipv4/udp.c:881`。利用浏览器的搜索功能, 我们发现 `skb` 下一次出现是在第 `1039` 行

	我们先试一试程序会不会跑到这里

	```
	b net/ipv4/udp.c:1039
	c
	```

	`continue` 之后我们发现, `UDP` 真的在这儿停住了。接下来的语句是这样的:

	```c
	skb = ip_make_skb(sk, fl4, getfrag, msg->msg_iov, ulen, sizeof(struct udphdr), &ipc, &rt, msg->msg_flags);
	```

	从 `ip_make_skb` 的前缀可以看出这是要调用ip层的函数对数据进行重新封装。根据参考文献

	> UDP协议与IP层之间没有定义发送接口, 而是在udp_sendmsg函数中调用IP层发送数据包的回调函数ip_append_data,  或在udp_sendpage函数中调用IP层的回调函数ip_append_page, 将UDP数据报放入IP层。

	如果我们进入 `ip_make_skb` 所在的 `http://codelab.shiyanlou.com/source/xref/linux-3.18.6/net/ipv4/ip_output.c#1458` 就可以看到, 在 `1482` 确实调用了 `__ip_append_data()`, 不过本次实验的目的是跟踪 `UDP`, 也就是传输层的内容, 因此我们可以 step over `ip_make_skb()`

*	接着我们来到了 `net/ipv4/udp.c:1043`

	```c
	if (!IS_ERR_OR_NULL(skb))
	{
		err = udp_send_skb(skb, fl4);
	}
	goto out;
	```

	通过 next 我们发现程序会进入 `if` 语句, 也就是说非空的 `skb` 没有错误。接下来将要执行的就是 `udp_send_skb()` 函数了, 我们使用 `si` 进入函数体。

	```c
	/*
	si
	udp_send_skb (skb=0xc7aff540, fl4=0xc0039c20) at net/ipv4/udp.c:784
	*/
	static int udp_send_skb(struct sk_buff *skb, struct flowi4 *fl4){
		...
	}
	```

	在定义了一堆变量之后, 这个函数开始构造 `UDP` 的 `header`. `header` 由 `源端口、目的端口、长度、校验和` 这 4 个字段组成, 每个字段 2 字节, 一共 `8` 个字节。下面的代码是对这四个字段的赋值

	```c
	/*
	 * Create a UDP header
	 */
	// 初始化 udp header 结构体 uh
	uh = udp_hdr(skb);
	// sport 是 source port
	uh->source = inet->inet_sport;
	// dport 是 dest port
	uh->dest = fl4->fl4_dport;
	// 将无符号短整形数转换成网络字节序
	uh->len = htons(len);
	uh->check = 0;
	```

	如果继续 `next` 单步执行, 程序会进入 `811` 行, 进行校验和 `csum` 的计算

	```c
	else if (skb->ip_summed == CHECKSUM_PARTIAL)
	{   /* UDP hardware csum */
		// 计算校验和
		udp4_hwcsum(skb, fl4->saddr, fl4->daddr);
		// 准备发送
		goto send;
	}
	```

	然后我们看看 `goto send` 之后会发生什么

	```c
	static int udp_send_skb(struct sk_buff *skb, struct flowi4 *fl4)
	{
		/* ... */

	// #825
	send:
		err = ip_send_skb(sock_net(sk), skb);
		if (err) {
			if( err == -ENOBUFS && !inet->recverr ){
				UDP_INC_STATS_USER(sock_net(sk), UDP_MIB_SNDBUFERRORS, is_udplite);
			err = 0;
			}
		} else{
			UDP_INC_STATS_USER(sock_net(sk), UDP_MIB_OUTDATAGRAMS, is_udplite);
		}

		return err;
	}
	```

	也就是说, 首先通过 `ip_send_skb()` 把数据交给下面的网络层进行发送, 然后判断底层会回复一个是否成功, 如果成功了就执行 `UDP_INC_STATS_USER()` 并逐步退出函数栈, 也就是回到刚才的 `udp:1044`, 向下执行 `ip_rt_put(rt)`, 从 `udp_sendmsg` 返回, 再从 `inet_sendmsg` 返回, 再回到更上层的函数。

*	我们可以用 `finish` 逐步退出函数栈, 可以发现, 最终在执行完 `SyS_socketcall(` 之后, 数据被正式发出（此时可以看到程序停在了 `server` 准备发送数据的 `inet_sendmsg`, 接下来的过程和 `client` 发送数据的过程是一样的）。

	以上就是 `UDP` 发送数据的过程, 总结一下就是

	```c
	SyS_socketcall()
	    /* ... */
	        inet_send_msg()
	            udp_sendmsg()
	                ip_make_skb()
	                udp_send_skb()
	                    /* ... */
	                    udp4_hwcsum()
	                    ip_send_skb()
	                    UDP_INC_STATS_USER()
	                    
	                    return
	```

	下面我们来观察一下数据接收的过程

	<br>

##	UDP 接收数据

*	TODO

	<br>

##	参考

*	cork, 软木塞

	```c
	/* net/ipv4/udp.c:879 */
	int corkreq = up->corkflag || msg->msg_flags&MSG_MORE;

	/* net/ipv4/udp.c:1037 */
	/* Lockless fast path for the non-corking case. */
	if( !corkreq ){
		skb = ip_make_skb(sk, fl4, getfrag, msg->msg_iov, ulen, sizeof(struct udphdr), &ipc, &rt, msg->msg_flags);
		// ...
	}
	```

*	bt, backtrace, 可以查看函数调用栈

*	[Linux网络 - 数据包的发送过程](https://blog.csdn.net/lishanmin11/article/details/77162108)

*	[udp协议栈源码追踪浅析](https://hujianboo.github.io/2018/12/20/udp%E5%8D%8F%E8%AE%AE%E6%A0%88%E6%BA%90%E7%A0%81%E8%BF%BD%E8%B8%AA%E6%B5%85%E6%9E%90/)

*	[Linux协议栈--UDP协议的发送和接收](https://cxd2014.github.io/2016/08/13/network-udp/)

*	[np2018](https://github.com/mengning/linuxnet/blob/master/np2018.md)

*	[af_inet.c](http://codelab.shiyanlou.com/source/xref/linux-3.18.6/net/ipv4/af_inet.c)

*	[udp.c](http://codelab.shiyanlou.com/source/xref/linux-3.18.6/net/ipv4/udp.c)

*	[TCP和UDP以及IP报文格式](https://blog.csdn.net/kernel_jim_wu/article/details/7447377)
