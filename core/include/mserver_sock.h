#ifndef MSERVER_SOCK_H
#define MSERVER_SOCK_H


typedef mserver_connect_cb  (void*)f (void*pridata);

typedef struct mserver
{
    int sockfd;
    int port;
    char * addr;

    void * pridata;

}mserver;

int mserver_listen_start(mserver *ms);

#endif
