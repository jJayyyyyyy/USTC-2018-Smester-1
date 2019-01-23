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