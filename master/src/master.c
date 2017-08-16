#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

int sin_size=0;
int port=0;

int get_option(int argc, char *argv[])
{
    if(argc!=2)
        return -1;

    if((port=atoi(argv[1]))<0)
        return -1;
    return 0;
}

int dbop_init()
{
    return 0;
}

int main(int argc, char *argv[])
{
    int ret=0;

    if ((ret = get_option(argc, argv))==-1)
    {
        fprintf(stderr,"Usage:%s listenport\a\n",argv[0]);
        exit(1);
    }

    if ((ret = dbop_init)==-1)
    {
        fprintf(stderr,"DB Connect Error!\a\n");
        exit(1);
    }
    mserver ms={0, port, NULL, NULL};
    ret = mserver_listen_start(ms);
    if (ret==-1)
    {
        fprintf(stderr,"Socket Listen Error!\a\n");
        exit(1);
    }
    return 0;
}
