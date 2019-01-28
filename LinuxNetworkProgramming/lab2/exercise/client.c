/* client */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include "client.h"

int simple_client(){
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
