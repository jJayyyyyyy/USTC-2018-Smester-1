#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "menu.h"

#include"syswrapper.h"
#define MAX_CONNECT_QUEUE   1024
int Replyhi()
{
    char szBuf[MAX_BUF_LEN] = "\0";
    char szReplyMsg[MAX_BUF_LEN] = "hi\0";
    InitializeService();
    while (1)
    {
        ServiceStart();
        RecvMsg(szBuf);
        SendMsg(szReplyMsg);
        ServiceStop();
    }
    ShutdownService();
    return 0;
}

int StartReplyhi(int argc, char *argv[])
{
    int pid;
    /* fork another process */
    pid = fork();
    if (pid < 0)
    {
        /* error occurred */
        fprintf(stderr, "Fork Failed!");
        exit(-1);
    }
    else if (pid == 0)
    {
        /*   child process  */
        Replyhi();
        printf("Reply hi TCP Service Started!\n");
    }
    else
    {
        /*  parent process   */
        printf("Please input hello...\n");
    }
}

int Hello(int argc, char *argv[])
{
    char szBuf[MAX_BUF_LEN] = "\0";
    char szMsg[MAX_BUF_LEN] = "hello\0";
    OpenRemoteService();
    SendMsg(szMsg);
    RecvMsg(szBuf);
    CloseRemoteService();
    return 0;
}

#include <sys/ioctl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <net/if.h>
#include <arpa/inet.h>
 
#include <unistd.h>
#include <stdio.h>
#define MAX_IFS 64
 
int BringUpNetInterface()
{
    printf("Bring up interface:lo\n");
    struct sockaddr_in sa;
    struct ifreq ifreqlo;
    int fd;
    sa.sin_family = AF_INET;
    sa.sin_addr.s_addr = inet_addr("127.0.0.1");
    fd = socket(PF_INET, SOCK_DGRAM, IPPROTO_IP);
    strncpy(ifreqlo.ifr_name, "lo",sizeof("lo"));
    memcpy((char *) &ifreqlo.ifr_addr, (char *) &sa, sizeof(struct sockaddr));
    ioctl(fd, SIOCSIFADDR, &ifreqlo);
    ioctl(fd, SIOCGIFFLAGS, &ifreqlo);
    ifreqlo.ifr_flags |= IFF_UP|IFF_LOOPBACK|IFF_RUNNING;
    ioctl(fd, SIOCSIFFLAGS, &ifreqlo);
    close(fd);
    
    printf("Bring up interface:eth0\n");
    sa.sin_family = AF_INET;
    sa.sin_addr.s_addr = inet_addr("10.0.2.15");
    fd = socket(PF_INET, SOCK_DGRAM, IPPROTO_IP);
    strncpy(ifreqlo.ifr_name, "eth0",sizeof("eth0"));
    memcpy((char *) &ifreqlo.ifr_addr, (char *) &sa, sizeof(struct sockaddr));
    ioctl(fd, SIOCSIFADDR, &ifreqlo);
    ioctl(fd, SIOCGIFFLAGS, &ifreqlo);
    ifreqlo.ifr_flags |= IFF_UP|IFF_RUNNING;
    ((unsigned char *) &ifreqlo.ifr_hwaddr.sa_data)[0] = 0x02;
    ((unsigned char *) &ifreqlo.ifr_hwaddr.sa_data)[1] = 0x42;
    ((unsigned char *) &ifreqlo.ifr_hwaddr.sa_data)[2] = 0xc0;
    ((unsigned char *) &ifreqlo.ifr_hwaddr.sa_data)[3] = 0xa8;
    ((unsigned char *) &ifreqlo.ifr_hwaddr.sa_data)[4] = 0x28;
    ((unsigned char *) &ifreqlo.ifr_hwaddr.sa_data)[5] = 0x05;
    ioctl(fd, SIOCSIFFLAGS, &ifreqlo);
    close(fd);

    printf("List all interfaces:\n");
    struct ifreq *ifr, *ifend;
    struct ifreq ifreq;
    struct ifconf ifc;
    struct ifreq ifs[MAX_IFS];
    int SockFD;
 
 
    SockFD = socket(PF_INET, SOCK_DGRAM, 0);
 
 
    ifc.ifc_len = sizeof(ifs);
    ifc.ifc_req = ifs;
    if (ioctl(SockFD, SIOCGIFCONF, &ifc) < 0)
    {
        printf("ioctl(SIOCGIFCONF): %m\n");
        return 0;
    }
 
    ifend = ifs + (ifc.ifc_len / sizeof(struct ifreq));
    for (ifr = ifc.ifc_req; ifr < ifend; ifr++)
    {
        printf("interface:%s\n", ifr->ifr_name);
#if 0
        if (strcmp(ifr->ifr_name, "lo") == 0)
        {
            strncpy(ifreq.ifr_name, ifr->ifr_name,sizeof(ifreq.ifr_name));
            ifreq.ifr_flags == IFF_UP;
            if (ioctl (SockFD, SIOCSIFFLAGS, &ifreq) < 0)
            {
              printf("SIOCSIFFLAGS(%s): IFF_UP %m\n", ifreq.ifr_name);
              return 0;
            }           
        }
#endif
        if (ifr->ifr_addr.sa_family == AF_INET)
        {
            strncpy(ifreq.ifr_name, ifr->ifr_name,sizeof(ifreq.ifr_name));
            if (ioctl (SockFD, SIOCGIFHWADDR, &ifreq) < 0)
            {
              printf("SIOCGIFHWADDR(%s): %m\n", ifreq.ifr_name);
              return 0;
            }
 
            printf("Ip Address %s\n", inet_ntoa( ( (struct sockaddr_in *)  &ifr->ifr_addr)->sin_addr)); 
            printf("Device %s -> Ethernet %02x:%02x:%02x:%02x:%02x:%02x\n", ifreq.ifr_name,
                (int) ((unsigned char *) &ifreq.ifr_hwaddr.sa_data)[0],
                (int) ((unsigned char *) &ifreq.ifr_hwaddr.sa_data)[1],
                (int) ((unsigned char *) &ifreq.ifr_hwaddr.sa_data)[2],
                (int) ((unsigned char *) &ifreq.ifr_hwaddr.sa_data)[3],
                (int) ((unsigned char *) &ifreq.ifr_hwaddr.sa_data)[4],
                (int) ((unsigned char *) &ifreq.ifr_hwaddr.sa_data)[5]);
        }
    }
 
    return 0;
}
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <net/route.h>
#include <sys/types.h>
#include <sys/ioctl.h>

int    SetDefaultGateway()
{
    int sockfd;
    struct rtentry route;
    struct sockaddr_in *addr;
    int err = 0;

    if(((sockfd = socket(AF_INET, SOCK_DGRAM, 0)))<0){
        perror("socket");
        exit(1);
    }

    memset(&route, 0, sizeof(route));
    addr = (struct sockaddr_in*) &route.rt_gateway;
    addr->sin_family = AF_INET;
    addr->sin_addr.s_addr = inet_addr("10.0.2.2");
    addr = (struct sockaddr_in*) &route.rt_dst;
    addr->sin_family = AF_INET;
    addr->sin_addr.s_addr = INADDR_ANY;
    addr = (struct sockaddr_in*) &route.rt_genmask;
    addr->sin_family = AF_INET;
    addr->sin_addr.s_addr = INADDR_ANY;
    route.rt_dev = "eth0";
    route.rt_flags = RTF_UP | RTF_GATEWAY;
    route.rt_metric = 0;
    if ((err = ioctl(sockfd, SIOCADDRT, &route)) != 0) {
         perror("SIOCADDRT failed");
         exit(1);
    }
    printf("Default gateway %s\n", inet_ntoa( ( (struct sockaddr_in *)  &route.rt_gateway)->sin_addr)); 
}

#include "getroute.c"
#include "dnsquery.c"


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

int httpclient(int argc, char *argv[]){
    printf("hello http0\n");
    int pid = fork();
    if( pid < 0 ){
        exit(1);
    }else if( pid == 0 ){
        char recvbuf[1024];
        char sendbuf[] = "GET / HTTP/1.1\r\nHost: github.com\r\nConnection: close\r\n\r\n";
        unsigned char hostname[32] = "github.com";
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
        // struct hostent * hostInfo = gethostbyname(hostname);
        // serverSockaddr_in.sin_addr = * (struct in_addr *)hostInfo->h_addr;
        // unsigned char ip_addr1[32] = "192.30.253.113";

        unsigned char * ip_addr2 = Gethostbyname(hostname);
        printf("ip2 in main: %s\n\n\n", ip_addr2);

        if( ip_addr2 != NULL ){
        // if( 1 ){
            serverSockaddr_in.sin_addr.s_addr = inet_addr(ip_addr2);

            // 服务器端口号
            serverSockaddr_in.sin_port = htons(80);

            /*创建客户端套接字--IPv4协议，面向连接通信，TCP协议*/
            clientSockfd = socket(AF_INET, SOCK_STREAM, 0);

            serverSockaddr = (struct sockaddr *)(&serverSockaddr_in);
            lenSockaddr = sizeof(struct sockaddr);
            connect( clientSockfd, serverSockaddr, lenSockaddr );
            send(clientSockfd, sendbuf, sendlen, 0);

            recvlen = recv(clientSockfd, recvbuf, 1024, 0);
            recvbuf[recvlen] = 0;
            printf("%s\n", recvbuf);

            
        }
        /*关闭套接字*/
        close(clientSockfd);
    }else{
        
    }
    
    return 0;
}

int main()
{
    BringUpNetInterface();
    SetDefaultGateway();
    GetRoute();
    SetPrompt("MenuOS>>");
    MenuConfig("version","MenuOS V1.0(Based on Linux 3.18.6)",NULL);
    MenuConfig("replyhi", "Reply hi TCP Service", StartReplyhi);
    MenuConfig("hello", "Hello TCP Client", Hello);
    MenuConfig("dns", "DNS Query github.com", Gethostbyname);
    MenuConfig("http", "http", httpclient);
    ExecuteMenu();
}
