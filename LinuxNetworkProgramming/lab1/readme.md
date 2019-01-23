##	通过TCP协议进行C/S模式的网络通信

*	我们可以直接将整个工程 clone 到本地进行测试

	进入 lab1

	```
	cd ~/LinuxKernel
	git clone https://github.com/mengning/linuxnet
	cd linuxnet/lab1
	gcc server.c -o server
	gcc client.c -o client
	```

	然后先运行 server, 再新开一个 shell 运行 client, 就可以看到通信结果了

	```
	recv "hello" from 127.0.0.1:58911
	rely "hi" to 127.0.0.1:58911
	```

	作为练习, 我们也可以自己动手写生成 server 和 client

*	首先写 server

	```c
	/* server */
	#include <stdio.h>
	#include <string.h>
	#include <stdlib.h>
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <arpa/inet.h>
	#include <netdb.h>

	int main(int argc, char *argv[]){
		char recvbuf[BUFSIZ];
		char sendbuf[] = "hello from server";

		int len_sendbuf = strlen(sendbuf), len_recvbuf;
		int client_sockfd, server_sockfd;

		// 服务器端网络地址结构体
		struct sockaddr_in server_sockaddr_in, client_sockaddr_in;
		struct sockaddr * server_sockaddr = (struct sockaddr *)(&server_sockaddr_in);
		struct sockaddr * client_sockaddr = (struct sockaddr *)(&client_sockaddr_in);
		socklen_t len_sockaddr_in = (socklen_t)( sizeof(struct sockaddr_in) );
		size_t len_sockaddr = sizeof(struct sockaddr);

		// 数据初始化清零
		memset( &server_sockaddr_in, 0, sizeof(server_sockaddr_in) );

		server_sockaddr_in.sin_family = AF_INET;
		server_sockaddr_in.sin_addr.s_addr = inet_addr("127.0.0.1");
		server_sockaddr_in.sin_port = htons(8000);

		/* 创建服务端套接字 */
		server_sockfd = socket(AF_INET, SOCK_STREAM, 0);
		bind( server_sockfd, server_sockaddr, len_sockaddr );
		listen(server_sockfd, 5);

		/* 接收连接 */
		client_sockfd = accept(server_sockfd, client_sockaddr, &len_sockaddr_in);

		/* server 先接收数据 */
		len_recvbuf = recv(client_sockfd, recvbuf, BUFSIZ, 0);
		recvbuf[len_recvbuf] = 0;
		printf("%s %s:%d\n", recvbuf, inet_ntoa(client_sockaddr_in.sin_addr), ntohs(client_sockaddr_in.sin_port));

		/* server 再发送自己的数据 */
		send(client_sockfd, sendbuf, len_sendbuf, 0);

		/*关闭套接字*/
		close(client_sockfd);
		return 0;
	}
	```

	然后编译生成 server

	```
	gcc server.c -o server
	```

*	接着生成 client

	```c
	/* client */
	#include <stdio.h>
	#include <string.h>
	#include <stdlib.h>
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <arpa/inet.h>
	#include <netdb.h>

	int main(int argc, char *argv[]){
		char recvbuf[BUFSIZ];
		char sendbuf[] = "hi from client";
		size_t len_sockaddr;
		int len_sendbuf = strlen(sendbuf), len_recvbuf;
		int client_sockfd;

		// 服务器端网络地址结构体
		struct sockaddr_in server_sockaddr_in;
		struct sockaddr * server_sockaddr;

		// 数据初始化清零
		memset( &server_sockaddr_in, 0, sizeof(server_sockaddr_in) );

		server_sockaddr_in.sin_family = AF_INET;
		server_sockaddr_in.sin_addr.s_addr = inet_addr("127.0.0.1");
		server_sockaddr_in.sin_port = htons(8000);

		/*创建客户端套接字--IPv4协议，面向连接通信，TCP协议*/
		client_sockfd = socket(AF_INET, SOCK_STREAM, 0);

		server_sockaddr = (struct sockaddr *)(&server_sockaddr_in);
		len_sockaddr = sizeof(struct sockaddr);
		connect( client_sockfd, server_sockaddr, len_sockaddr );
		send(client_sockfd, sendbuf, len_sendbuf, 0);

		len_recvbuf = recv(client_sockfd, recvbuf, BUFSIZ, 0);
		recvbuf[len_recvbuf] = 0;
		printf("%s %s:%d\n", recvbuf, inet_ntoa(server_sockaddr_in.sin_addr), ntohs(server_sockaddr_in.sin_port));

		/*关闭套接字*/
		close(client_sockfd);    
		return 0;
	}

	```

	然后编译生成 client

	```
	gcc client.c -o client
	```

*	测试运行

	首先在 shell 中运行 server, 再在另一个 shell 中运行 client, 如果一切顺利, 就能在 server 端收到 client 发来的信息

	```
	hi from client 127.0.0.1:60992
	# 端口号可能不一样
	```

	也能在 client 端收到 server 发来的回复信息

	```
	hello from server 127.0.0.1:8000
	```

	<br>

##	参考链接

*	[通过TCP协议进行C/S模式的网络通信](https://www.shiyanlou.com/courses/1198/labs/8921/document)

*	[lab1](https://github.com/mengning/linuxnet/tree/master/lab1)

*	[linux下C/C++网络编程基本：socket实现tcp和udp的例子](https://blog.csdn.net/u012234115/article/details/54142273)
