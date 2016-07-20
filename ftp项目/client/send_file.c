#include "func.h"

void send_file(int new_fd,char* FILENAME)
{
	data d;
	bzero(&d,sizeof(d));
//发送文件名
	d.len=strlen(FILENAME);
	strcpy(d.buf,FILENAME);
	send(new_fd,&d,4+d.len,0);
	int fd;
	fd=open(FILENAME,O_RDONLY);
	if(-1==fd)
	{
		perror("open");
		exit(0);
	}
	int ret;
	//发送文件内容 
	while(bzero(&d,sizeof(d)),(d.len=read(fd,d.buf,sizeof(d.buf)))>0)
	{
		ret=send_n(new_fd,&d,4+d.len);
		if(-1==ret)
		{
			close(new_fd);
			exit(0);
		}
	}
	int flag=0;
	send_n(new_fd,&flag,4);//发送文件结束标志
}

