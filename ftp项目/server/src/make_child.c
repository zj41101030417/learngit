#include "func.h"		

void make_child(pchild p,int n)
{
	int i;
	int fds[2];
	pid_t pid;
	int ret;
	for(i=0;i<n;i++)
	{
		socketpair(AF_LOCAL,SOCK_STREAM,0,fds);
		pid=fork();
		if(pid==0)
		{
			close(fds[1]);
			child_handle(fds[0]);//子进程的流程
		}//子进程必须在该括号之前结束
		close(fds[0]);
		p[i].fds=fds[1];
		p[i].pid=pid;
		p[i].busy=0;
	}	
}
