#ifndef __FUNC_H__
#define __FUNC_H__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/epoll.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <sys/uio.h>
#include <dirent.h>
#include <strings.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
typedef struct{
	pid_t pid;
	int fds;
	int busy;
}child,*pchild;

typedef struct{
	int len;
	char buf[1000];
}data,*pdata;
#endif
