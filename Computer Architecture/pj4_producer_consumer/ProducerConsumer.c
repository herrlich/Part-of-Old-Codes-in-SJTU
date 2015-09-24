#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
#include <time.h>
#include <stdlib.h>

typedef int buffer_item;
/*信号量*/
//空的信号量和满的信号量
sem_t empty_sem, full_sem;   
//静态创建条件变量
pthread_cond_t full = PTHREAD_COND_INITIALIZER;        //满的变量
pthread_cond_t empty = PTHREAD_COND_INITIALIZER;       //空的变量
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;      //互斥锁

#define BUFFERNUM 10    

//缓冲区队列
struct Buffer_Queue {
	char production[BUFFERNUM];  //产品
	int front, rear;             //头指针和尾指针
	int num;                     //缓冲区里面字母数量        
};

int buffer[BUFFERNUM];

//输出设计者信息
void printDesign()
{
	printf("   ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
	printf("   ┃            生产者-消费者问题实现                 ┃\n");
	printf("   ┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫\n");
}

//随机产生生产字符
char getRandChar()
{
	int temp = rand()%26;
	return ('a'+temp);
}

//打印进程运行结果
void printTime()
{
	//打印时间
	time_t now;
	struct tm *timenow;         //实例化tm结构指针
	time(&now);
	timenow = localtime(&now);
	printf("执行时间： %s ",asctime(timenow));
}

//生产者1
void *producer1(void *arg)
{
	struct Buffer_Queue *q;
	q = (struct Buffer_Queue *) arg;
	while(1)
	{
		pthread_mutex_lock(&lock);       
		while (q->num == BUFFERNUM)    //缓冲区已经满了，等待
		{            
			pthread_cond_wait(&full, &lock);
		}
		sem_wait(&empty_sem);

		/*生产产品*/
		char c = getRandChar();                                      //随机获取字母
		q->rear = (q->rear + 1) % BUFFERNUM;                         //计算新的尾指针   
		q->production[q->rear] = c;                                  //写入新产品
		q->num++;
		
		/*打印输出结果*/
		printf("-------------------------------------------------------------\n");
		printTime();              //程序运行时间
		int i;
		printf("缓冲区数据（%d个）：",q->num);                  //打印缓冲区中的数据
		if(q->front < q->rear)
		{
			for(i = q->front; i <= q->rear; i++)
				printf("%c ",q->production[i]);
		}
		else
		{
			for(i = q->front; i < BUFFERNUM; i++)
				printf("%c ",q->production[i]);
			for(i = 0; i <= q->rear; i++)
				printf("%c ",q->production[i]);
		}
		printf("\n当前执行的进程：生产者1\n");   //打印当前执行的进程
		printf("产生的数据：%c\n",c);      //打印产生或消费的数据
		printf("-------------------------------------------------------------\n");

		sem_post(&full_sem);

		if (q->num == 1) {
			pthread_cond_signal(&empty);    
		}
		pthread_mutex_unlock(&lock); 

		sleep(rand() % 2);            
	}
}


//消费者1
void *consumer1(void *arg)
{
	struct Buffer_Queue *q;
	q = (struct Buffer_Queue *) arg;
	while(1)
	{
		pthread_mutex_lock(&lock);        
		while (q->num == 0)           //缓冲区已经空了，等待
		{        
			pthread_cond_wait(&empty, &lock);
		}
		sem_wait(&full_sem);

		/*消费产品*/
		q->front = (q->front + 1) % BUFFERNUM;    //计算新的头指针
		char c = q->production[q->front];         //消费产品
		q->production[q->front] = ' ';            //
		q->num--;

		/*打印输出结果*/
		printf("-------------------------------------------------------------\n");
		printTime();              //程序运行时间
		int i;
		printf("缓冲区数据（%d个）：",q->num);                   //打印缓冲区中的数据
		if(q->front < q->rear)
		{
			for(i = q->front; i <= q->rear; i++)
				printf("%c ",q->production[i]);
		}
		else
		{
			for(i = q->front; i < BUFFERNUM; i++)
				printf("%c ",q->production[i]);
			for(i = 0; i <= q->rear; i++)
				printf("%c ",q->production[i]);
		}
		printf("\n当前执行的进程：消费者1\n");   //打印当前执行的进程
		printf("消耗的数据：%c\n",c);      //打印产生或消费的数据
		printf("-------------------------------------------------------------\n");


		sem_post(&empty_sem);
		if (q->num == BUFFERNUM - 1) {
			pthread_cond_signal(&full);
		}
		pthread_mutex_unlock(&lock);
		sleep(rand() % 2);
	}
}



int main(int argc, char *argv[])
{
    //输出设计者
	printDesign();

	/*创建缓冲区*/
	//定义
	struct Buffer_Queue *q;
	q = (struct Buffer_Queue *) malloc(sizeof(struct Buffer_Queue));
	//初始化队列
	q->front = q->rear = BUFFERNUM - 1;
	q->num = 0;

	/*执行进程*/
	//定义四个线程
	pthread_t pid1, cid1;
	//初始化信号量
	sem_init(&empty_sem, 0, BUFFERNUM);   
	sem_init(&full_sem, 0, 0);   
	//创建线程
	pthread_create(&pid1, NULL, producer1, (void *) q);
	pthread_create(&cid1, NULL, consumer1, (void *) q);
	//销毁线程
	pthread_join(pid1, NULL);
	pthread_join(cid1, NULL);
	//销毁信号量
	sem_destroy(&empty_sem);
	sem_destroy(&full_sem);

	return 0;
}
