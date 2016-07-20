#include "func.h"
void check_arg(int argc,int aim)
{
	if(argc!=aim)
	{
		printf("error args\n");
		exit(-1);
	}
}
