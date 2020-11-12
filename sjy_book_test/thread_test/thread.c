#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#define THREAD_NUMBER 3
#define REPEAT_NUMBER 5
#define DELAY_TIME_LEVELS 10.0
void *thrd_func(void *arg)
{
	int thrd_num = (int)arg;
	int delay_time = 0;
	int count = 0;
	
	printf("Thread %d is starting\n",thrd_num);
	for(count = 0;count<REPEAT_NUMBER;count++)
	{
		delay_time = (int)(rand()*DELAY_TIME_LEVELS/(RAND_MAX))+1;
		sleep(delay_time);
		printf("\tThread %d:job %d delay = %d\n",thrd_num,count,delay_time);
	}
	printf("Thread %d finished\n",thrd_num);
	pthread_exit(NULL);	//这个函数的参数就是会返回给pthread_join中第二个参数(这个玩意得有个东西来接，不能是NULL)
}
int main()
{
	//首先 建立了一个线程数组
	pthread_t thread[THREAD_NUMBER];
	int no = 0,res;
	void *thrd_ret;
	srand(time(NULL));
	for(no = 0;no<THREAD_NUMBER;no++)
	{	
		//创建线程 实际上就是确定调用该线程函数的入口点
		//第一个参数 创建的线程号
		//第二个参数 线程的属性
		//第三个参数 线程的入口函数起始地址
		//第四个参数 参数
		res = pthread_create(&thread[no],NULL,thrd_func,(void*)no);
		if(res!=0)	//创建成功返回0 失败返回出错编号
		{
			printf("Create thread %d failed\n",no);
			exit(res);
		}
	}
	printf("Create threads sucess\n Waiting for threads to finish...\n");
	for(no=0;no<THREAD_NUMBER;no++)
	{
		//以阻塞等待的方式等待一个线程的结束
		//第一个参数是线程id号 第二个参数是用来接收线程的返回值的
		res = pthread_join(thread[no],&thrd_ret);
		if(!res)
		{
			printf("Thread %d joined\n",no);
		}
		else
		{
			printf("Thread %d join failed\n",no);
		}
	}
	return 0;
}
