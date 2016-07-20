#include "func.h"
	
int main(int argc,char* argv[])
{
	check_arg(argc,2);
	FILE *fp;
	fp=fopen(argv[1],"rb");//*打开已存在文件只能读
	char buf[128]={0};
	fgets(buf,sizeof(buf),fp);
	int s;
	char *m=buf+9;
	char buf1[128]={0};
	strcpy(buf1,m);
	fgets(buf,sizeof(buf),fp);
	char *n=buf+14;
	fgets(buf,sizeof(buf),fp);
	char* l=buf+10;
	int num=atoi(l);                                 
	pchild p=(pchild)calloc(num,sizeof(child));             
	make_child(p,num);                                     
	int sfd=socket(AF_INET,SOCK_STREAM,0);
	if(-1==sfd)
	{
		perror("socket");
		return -1;
	}
	struct sockaddr_in ser;
	bzero(&ser,sizeof(ser));
	ser.sin_family=AF_INET;
	ser.sin_port=htons(atoi(n));
	printf("客户机需要输入的port=%d\n",atoi(n));
	ser.sin_addr.s_addr=inet_addr(buf1);
	int ret;
	ret=bind(sfd,(struct sockaddr*)&ser,sizeof(struct sockaddr));
	if(-1==ret)
	{
		perror("bind");
		return -1;
	}
	int epfd=epoll_create(1);
	struct epoll_event event;
	struct epoll_event* evs=(struct epoll_event*)calloc(num+1,sizeof(event));
	event.events=EPOLLIN;
	event.data.fd=sfd;
	ret=epoll_ctl(epfd,EPOLL_CTL_ADD,sfd,&event);	   
	if(-1==ret)
	{
		perror("epoll_ctl");
		return -1;
	}
	int i;
	ret=listen(sfd,num);                               
	if(-1==ret)
	{
		perror("listen");
		return -1;
	}
	int new_fd;
	int j;
	int flag;
	while(1)
	{
		bzero(evs,(num+1)*sizeof(event));                 
		int ret=epoll_wait(epfd,evs,num+1,-1);              
		if(ret >0)
		{
			for(i=0;i<ret;i++)
			{
				if(evs[i].data.fd == sfd)                     
				{
					new_fd=accept(sfd,NULL,NULL);            
					for(j=0;j<num;j++)                      
					{
						if(p[j].busy ==0)
							break;                         
					}
					send_fd(p[j].fds,new_fd);              
					p[j].busy=1;
					int count;
					count=num-j-1;                          
					printf("成功连入一个客户端，还能连入%d个客户端\n",count);         
				}
			}
		}
	}
}									

