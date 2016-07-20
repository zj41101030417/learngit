#include "func.h"


void send_file(int new_fd,char* FILENAME)
{
	data d;
	bzero(&d,sizeof(d));
	d.len=strlen(FILENAME);
	strcpy(d.buf,FILENAME);
	send(new_fd,&d,4+d.len,0);
	int fd=open(FILENAME,O_RDONLY);
	if(-1==fd)
	{
		perror("open");
		exit(-1);
	} 
	while(bzero(&d,sizeof(d)),(d.len=read(fd,d.buf,sizeof(d.buf)))>0)
	{
		send_n(new_fd,&d,4+d.len);  
	}
	int flag=0;               
	send_n(new_fd,&flag,sizeof(int));
}

