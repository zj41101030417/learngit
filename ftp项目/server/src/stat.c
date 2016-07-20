#include "func.h"

void stat_t(int new_fd)
{
	DIR* dir=opendir("./");
	struct dirent *p;//定义指向目录里每个节点的指针
	char buf1[128];
	while((p=readdir(dir))!=NULL)
	{
		bzero(buf1,sizeof(buf1));
		sprintf(buf1,"%s/%s","./",p->d_name);//路径拼接
		struct stat buf;
		bzero(&buf,sizeof(buf));
		stat(buf1,&buf);
		char s;
		if(8==p->d_type)//普通文件
		{
			s='-';
		}
		else if(4==p->d_type)
		{
			s='d';
		}
		char buf2[256]={0};
		sprintf(buf2,"%-3c%-25s%ld%c%30s",s,buf1+3,buf.st_size,'B',ctime(&buf.st_mtime)+4);
		send(new_fd,buf2,sizeof(buf2),0);
	}
	char buf[10]="hello";
	send(new_fd,buf,sizeof(buf),0);
	closedir(dir);//关闭目录文件
}

