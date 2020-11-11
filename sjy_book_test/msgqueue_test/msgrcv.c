#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#define BUFFER_SIZE 512
struct message //建立一个结构体 一个type 一个text
{
	long msg_type;
	char msg_text[BUFFER_SIZE];
};
int main()
{
	int qid;
	key_t key;
	struct message msg;
	//根据路径和关键字产生标准的key 转换为一个key_t值 称为IPC键值
	if((key = ftok(".",'a'))==-1)
	{
		//perror在stdio.h头文件 作用是将错误信息打印在标准设备(stderr)上
		perror("ftok");
		exit(1);
	}
	//用于创建一个新的或打开一个已经存的消息队列
	//key是消息队列关联的键	
	//IPC_CREAT如果内核中没有这个队列就创建它
	//0666是权限 0是8进制 6是用户权限 6=二进制的110 所以6代表可读可写不可执行
	if((qid=msgget(key,IPC_CREAT|0666))==-1)
	{
		perror("msgget");
		exit(1);	
	}
	printf("Open queue %d\n",qid);
	do
	{
		//初始化 msg.msg_text的内容为0
		memset(msg.msg_text,0,BUFFER_SIZE);
		//msgrcv从消息队列中取出消息
		//qid消息队列标示符
		//大小
		//指定请求的消息类型 
//msgtyp=0收到的第一条消息 >0收到的第一条msgtyp类型的消息 <0收到的第一条最低类型的消息
			
		if((msgrcv(qid,(void*)&msg,BUFFER_SIZE,0,0))<0)
		{
			perror("msgrcv");
			exit(1);
		}
		printf("The message from process %d:%s",msg.msg_type,msg.msg_text);
	}while(strncmp(msg.msg_text,"quit",4));
	if((msgctl(qid,IPC_RMID,NULL))<0)
	{
		perror("msgctl");
		exit(1);	
	}
	exit(0);
}

