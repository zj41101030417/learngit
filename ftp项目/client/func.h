#ifndef __FUNC_H__
#define __FUNC_H__
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <pwd.h>
#include <sys/stat.h>
#include <grp.h>
#include <dirent.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <strings.h>

typedef struct{
	pid_t pid;
	int fds;
	int busy;
}child,*pchild;

typedef struct{
	int len;
	char buf[1000];
}data,*pdata;
void child_handle(int);

#endif

