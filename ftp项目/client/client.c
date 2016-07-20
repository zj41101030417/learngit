#include "func.h"

int main(int argc,char* argv[])
{
	check_arg(argc,3);
	int sfd;
	sfd=socket(AF_INET,SOCK_STREAM,0);
	if(-1==sfd)
	{
		perror("socket");
		return -1;
	}
	struct sockaddr_in ser;
	bzero(&ser,sizeof(ser));
	ser.sin_family=AF_INET;
	ser.sin_port=htons(atoi(argv[2]));
	ser.sin_addr.s_addr=inet_addr(argv[1]);//将点分10进制转成32位网络字节序
	int ret;
	ret=connect(sfd,(struct sockaddr*)&ser,sizeof(ser));
	if(-1==ret)
	{
		perror("connect");
		return -1;
	}
	char buf[128]={0};
	label1:scanf("%s",buf);
	send(sfd,buf,sizeof(buf),0);

 	char tmp=buf[0];
    int len=strlen(buf);
	if(3==len&&('p'==tmp))
	{
		system("reset");
        char buf4[128]={0};
        recv(sfd,buf4,sizeof(buf4),0);
        printf("%s\n",buf4);
    }
	else if(4==len&&('p'==tmp))
	{
		bzero(buf,sizeof(buf));
        scanf("%s",buf);
        send_file(sfd,buf);
	}
	switch(tmp)
	{
	case 'r':
	{
		char buf2[128]={0};
		scanf("%s",buf2);
		send(sfd,buf2,sizeof(buf2),0);
		printf("对应文件删除成功\n");
	}break;	
	case 'l':
	{
		system("reset");
		while(1)
		{
			bzero(buf,sizeof(buf));
			recv(sfd,buf,sizeof(buf),0);
			if(strcmp(buf,"hello")!=0)
			{
				printf("%s",buf);
			}else{
				goto label1;
			}
		}
	}break;
	case 'c':
	{
		char buf2[128]={0};
      	scanf("%s",buf2);
      	send(sfd,buf2,sizeof(buf2),0);
      	bzero(buf2,sizeof(buf2));
      	recv(sfd,buf2,sizeof(buf2),0);
      	system("reset");
      	printf("%s\n",buf2);
   	}break;
	case 'g':
	{
		bzero(buf,sizeof(buf));
		scanf("%s",buf);
		send(sfd,buf,sizeof(buf),0);
		data d;
		bzero(&d,sizeof(d));
		recv_n(sfd,&d.len,sizeof(int));
		recv_n(sfd,d.buf,d.len);
		int fd=open(d.buf,O_RDWR|O_CREAT,0666);
		if(-1==fd)
		{
			perror("open");
			return -1;
		}
		while(1)
		{
			bzero(&d,sizeof(d));
			recv_n(sfd,&d.len,sizeof(int));	
			if(d.len >0)
			{
				recv_n(sfd,d.buf,d.len);
				write(fd,d.buf,d.len);
			}else{
				goto label1;
			}
		}
	}break;
	}
	goto label1;
}

