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
	char sendbuf[] = "GET / HTTP/1.1\r\nHost: github.com\r\nConnection: close\r\n\r\n";
	char * hostname = "github.com";
	size_t lenSockaddr;
	int sendlen = strlen(sendbuf), recvlen, i;
	int clientSockfd;

	// 服务器端网络地址结构体
	struct sockaddr_in serverSockaddr_in;
	struct sockaddr * serverSockaddr;

	// 数据初始化清零
	memset( &serverSockaddr_in, 0, sizeof(serverSockaddr_in) );

	// IPv4
	serverSockaddr_in.sin_family = AF_INET;

	// https://www.gnu.org/software/libc/manual/html_node/Inet-Example.html
	struct hostent * hostInfo = gethostbyname(hostname);
	serverSockaddr_in.sin_addr = * (struct in_addr *)hostInfo->h_addr;
	// serverSockaddr_in.sin_addr.s_addr = inet_addr("192.30.253.113");

	// 服务器端口号
	serverSockaddr_in.sin_port = htons(80);

	/*创建客户端套接字--IPv4协议，面向连接通信，TCP协议*/
	clientSockfd = socket(AF_INET, SOCK_STREAM, 0);

	serverSockaddr = (struct sockaddr *)(&serverSockaddr_in);
	lenSockaddr = sizeof(struct sockaddr);
	connect( clientSockfd, serverSockaddr, lenSockaddr );
	send(clientSockfd, sendbuf, sendlen, 0);

	recvlen = recv(clientSockfd, recvbuf, BUFSIZ, 0);
	recvbuf[recvlen] = 0;
	printf("%s\n", recvbuf);

	/*关闭套接字*/
	close(clientSockfd);
    
	return 0;
}