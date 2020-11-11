#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#define BUFFER_SIZE 512
struct message
{
	long msg_type;
	char msg_text[BUFFER_SIZE];
};
int main()
{
	int qid;
	key_t key;
	struct message msg;
	if((key = ftok(".",'a'))==-1)
	{
		perror("ftok");
		exit(1);
	}
	
	if((qid=msgget(key,IPC_CREAT|0666))==-1)
	{
		perror("msgget");
		exit(1);	
	}
	printf("Open queue %d\n",qid);
	while(1)
	{
		printf("Enter some message to the queue:");
		//从标准输入(stdin)键盘流中读取数据 
		if((fgets(msg.msg_text,BUFFER_SIZE,stdin))==NULL)
		{
			puts("No message");
		}
		//msg_type的值就是发送进程的进程号
		msg.msg_type = getpid();
		//qid由消息队列标示符生成
		//第二个参数msg是要发送的用户自定义的缓冲区
		//接受消息的大小
		//msgtyp 如果为0则调用进程挂起操作，直到达到系统规定的最大值
		if((msgsnd(qid,&msg,strlen(msg.msg_text),0))<0)
		{
			perror("message posted");
			exit(1);
		}
		//strcncmp只比较两个字符串中n(第三个参数)位
		if(strncmp(msg.msg_text,"quit",4)==0)
		{
			break;
		}
	}
	exit(0);
}

