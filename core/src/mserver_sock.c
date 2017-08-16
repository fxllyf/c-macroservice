#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include "mserver_sock.h"

int mserver_listen_start(mserver *ms)
{
    int sockfd = 0;
    int sin_size = 0;

    /* 服务器端开始建立socket描述符 */
    if((sockfd=socket(AF_INET,SOCK_STREAM,0))==-1)
    {
        fprintf(stderr,"Socket error:%s\n\a",strerror(errno));
        return -1;
    }

    /* 服务器端填充 sockaddr结构  */
    struct sockaddr_in server_addr;
    bzero(&server_addr,sizeof(struct sockaddr_in));
    server_addr.sin_family=AF_INET;
    server_addr.sin_addr.s_addr=htonl(INADDR_ANY);
    server_addr.sin_port=htons(ms->port);

    /* 捆绑sockfd描述符  */
    if(bind(sockfd,(struct sockaddr *)(&server_addr),sizeof(struct sockaddr))==-1)
    {
        fprintf(stderr,"Bind error:%s\n\a",strerror(errno));
        return -1;
    }
    /* 监听sockfd描述符  */
    if(listen(sockfd,5)==-1)
    {
        fprintf(stderr,"Listen error:%s\n\a",strerror(errno));
        return -1;
    }
    ms->sockfd = sockfd;


    while(1)
    {
       /* 服务器阻塞,直到客户程序建立连接  */
       sin_size=sizeof(struct sockaddr_in);
       if((new_fd=accept(sockfd,(struct sockaddr *)(&client_addr),&sin_size))==-1)
       {
           fprintf(stderr,"Accept error:%s\n\a",strerror(errno));
           exit(1);
       }
       fprintf(stderr,"Server get connection from %s\n", inet_ntoa(client_addr.sin_addr));

       if(write(new_fd,hello,strlen(hello))==-1)
       {
           fprintf(stderr,"Write Error:%s\n",strerror(errno));
           exit(1);
       }
       /* 这个通讯已经结束     */
       close(new_fd);
       /* 循环下一个     */
    }
    close(sockfd);
    return 0;
}