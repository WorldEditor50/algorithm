#include<pthread.h>
#include<stdio.h>
#include<unistd.h>
int num = 0;
char p1[10]="pthread1";
char p2[10]="pthread2";
pthread_mutex_t mutex;
void* counting(void* arg)
{
	char* p = (char*)arg;
	while(num<40)
	{
		pthread_mutex_lock(&mutex);
		num++;
		printf("num=%d id=%s\n",num,p);
		pthread_mutex_unlock(&mutex);
	}
	pthread_exit(0);
}
int main()
{
	pthread_t tid1;
	pthread_t tid2;
	pthread_mutex_init(&mutex,NULL);
	pthread_create(&tid1,NULL,counting,(void*)p1);
	pthread_create(&tid2,NULL,counting,(void*)p2);
	sleep(1);
	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);
	printf("num=%d\n",num);
	pthread_mutex_destroy(&mutex);
	return 0;
}

