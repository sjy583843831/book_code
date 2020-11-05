#include<unistd.h>
#define MAX_DATA_LEN 256
#define DELAY_TIME 1
int main()
{
	pid_t pid;
	int pipe_fd[2]; //定义管道号 一个读 一个写
	char buf[MAX_DATA_LEN];
	char data[] = "Pipe Test Program"; //测试输入样例
	int real_read,real_write;

	memset((void*)buf,0,sizeof(buf));
	if(pipe(pipe_fd)<0) //建立俩管道
	{
		printf("create pipe error\n");
		exit(1);
	}
	//新建一个进程
	if((pid = fork())==0)//子进程读管道
	{
		printf("0");
		close(pipe_fd[1]);
		sleep(DELAY_TIME*3);
		if((real_read = read(pipe_fd[0],buf,MAX_DATA_LEN))>0)//从fd[1]读
		{
			printf("%d bytes read from the pipe is '%s'\n",real_read,buf);
		}
		close(pipe_fd[0]);
		exit(0);
	}
	else if(pid>0) //父进程写管道
	{
		printf("1");
		close(pipe_fd[0]);
		sleep(DELAY_TIME);
		if((real_write = write(pipe_fd[1],data,strlen(data)))!=-1)//往fd[0]写
		{
			printf("%d bytes: '%s'\n",real_write,data);
		}
		close(pipe_fd[1]);
		waitpid(pid,NULL,0);
		exit(0);
	}
}
