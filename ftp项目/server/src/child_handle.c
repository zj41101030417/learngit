#include "func.h"

void child_handle(int fdr)
{
	int new_fd;
	int flag=1;
	int s[2];
	socketpair(AF_LOCAL,SOCK_STREAM,0,s);
	while(1)
	{
		recv_fd(fdr,&new_fd);
		send_fd(s[0],new_fd);
		char buf[128]={0};
		label:recv(new_fd,buf,sizeof(buf),0);
		char tmp=buf[0];
		int len=strlen(buf);
		if(3==len&&('p'==tmp))
		{
			bzero(buf,sizeof(buf));
			strcpy(buf,getcwd(NULL,0));//getcwd(NULL,0)是获取当前目录
			send(new_fd,buf,sizeof(buf),0);
		} 
		else if(4==len&&('p'==tmp))
		{
			data d;
            bzero(&d,sizeof(d));
            recv_n(new_fd,&d.len,sizeof(int));
            recv_n(new_fd,d.buf,d.len);
            int fd;
            fd=open(d.buf,O_RDWR|O_CREAT,0666);
            while(1)
            {
				bzero(&d,sizeof(d));
                recv_n(new_fd,&d.len,sizeof(int));
                if(d.len>0)
                {
					recv_n(new_fd,d.buf,d.len);
                    write(fd,d.buf,d.len);
                }else{
                     goto label;
                     }
            }
		}
		switch(tmp)
		{
			case 'r':
			{
				bzero(buf,sizeof(buf));
              	recv(new_fd,buf,sizeof(buf),0);
              	unlink(buf);
          	}break;
			case 'g':
			{
				bzero(buf,sizeof(buf));
             	recv(new_fd,buf,sizeof(buf),0);
              	send_file(new_fd,buf);
          	}break;
			case 'c': 
			{
				bzero(buf,sizeof(buf));
				recv(new_fd,buf,sizeof(buf),0);
				chdir(buf);//将当前工作目录改变成buf所指目录
				char buf2[128]={0};
				strcpy(buf2,getcwd(NULL,0));//将当前工作目录绝对路径复制到buf2所指空间
				send(new_fd,buf2,sizeof(buf2),0);
			}break;
			case 'l':
			{
				stat_t(new_fd);
			}break;
		}
		goto label;
	}
}

	
