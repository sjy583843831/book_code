#include<sys/types.h>
#include<unistd.h>
int main()
{
	pid_t result;
	//调用fork函数
	result = fork();//通过result的值来判断fork()函数的返回情况
	if(result==-1) //首先进行出错处理
	{
		printf("Fork error\n");
	}
	else if(result==0) //返回值为0代表子进程 son
	{
		printf("The returned value is %d\n In child process!!\nMy PID is %d\n",result,getpid());
	}
	//返回值大于0代表父进程 father
	else{
		printf("The returned value is %d\n In father process!!\nMy pid is %d\n",result,getpid());
	}
	return result;
}
