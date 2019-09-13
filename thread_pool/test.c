#include "pool.h"
void* hello(void* word)
{
	char* str = word;
	printf("%s\n",str);
	//sleep(2);
	return NULL;
}
int main()
{
	int ret = 0;
	int i = 0;
	//创建线程池
	tpool *pool = NULL;
	pool = tpool_create(100,200);
	if(!pool)
	{
		printf("%s\n","pool create failed");
		return 1;
	}
	printf("%s\n","create pool");
	//添加任务
	for(i=0;i<50000;i++)
	{
		ret = tpool_add_task(pool,hello,"hello");
		if(ret!=0)
		{
			printf("%s\n","pool create failed");
			return 1;
		}
	}
	printf("%s\n","added task");
	//释放线程池
	getchar();
	ret = tpool_destroy(pool);
	if(ret!=0)
	{
		printf("%s\n","pool create failed");
	}
	printf("%s\n","destroy pool");
	return 0;
}
