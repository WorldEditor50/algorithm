#include"pool.h"
/*空闲任务*/
static void* do_nothing(void* arg)
{

	return NULL;
}
/*判断线程存活*/
static int is_alive(pthread_t tid) {
	int ret = pthread_kill(tid,0);
	if(ret == ESRCH) {
		return 0;
	}
	return 1;
}
/*工作线程*/
static void* tpool_working(void* tp)
{
	if(tp == NULL) {
		debug("tpool_working: pool is null");
		return NULL;
	}
	tpool* pool = (tpool*)tp;
	while (1) {
		pthread_mutex_lock(&pool->lock);
		//等待队列不为空
		while (pool->queue_num == 0 && pool->shutdown != 1) {
			pthread_cond_wait(&pool->queue_not_empty, &pool->lock);
		}
		//从任务队列中取出任务
		task_t *ptask = NULL;
		ptask = pool->queue_head;
		pool->queue_head = ptask->next;
		pool->queue_num--;
		//广播任务队列不满  
		if(pool->queue_num < pool->queue_max_num) {
			pthread_cond_broadcast(&pool->queue_not_full);
		}
		//如果任务队列为空
		if(pool->queue_num==0) {
			pthread_cond_signal(&pool->queue_empty);
		}
		pthread_mutex_unlock(&pool->lock);
		//执行任务
		ptask->execute(ptask->arg);

		pthread_mutex_lock(&pool->lock);
		free(ptask);
		ptask = NULL;
		//清理空余线程
		if(pool->thread_cur_num > pool->thread_min_num) {
			if(pool->thread_cur_num > 2*pool->queue_num) {
				int id = pthread_self();
				int i = 0;
				for(i=0; i < pool->thread_max_num; i++) {
					if(pool->tid[i].id == id) {
						pool->tid[i].alive = 0;
						break;
					}
				}
				pool->thread_cur_num--;
				pthread_mutex_unlock(&(pool->lock));
				break;
			}
		}
		//如果线程池关闭或者任务队列关闭
		if(pool->shutdown || pool->queue_close) {
			pool->thread_cur_num--;
			pthread_mutex_unlock(&pool->lock);
			break;
		}
		pthread_mutex_unlock(&pool->lock);
	}
	pthread_exit(NULL);
}

/*管理线程*/
static void* tpool_admin(void* tp)
{
	if(tp == NULL) {
		debug("tpool_admin: pool is null");
		return NULL;
	}
	tpool* pool = (tpool*)tp;
	while (1) {
		int i = 0;
		int num = 0;
		int count = 0;
		int flag = 0;
		pthread_mutex_lock(&(pool->lock));
		//判断线程池的忙碌情况
		if (pool->thread_cur_num < pool->thread_max_num) {
			if (pool->queue_num >= pool->thread_max_num) {
				num = pool->thread_max_num - pool->thread_cur_num;
				flag = 1;
			} else {
				if (pool->queue_num > pool->thread_cur_num) {
					num = pool->queue_num - pool->thread_cur_num;
					flag = 1;
				}
			}
			pthread_mutex_unlock(&pool->lock);
			if (flag == 1) {
				//增加线程数量
				for(i = 0; i < pool->thread_max_num; i++) {
					if (pool->tid[i].alive == 0) {
						pool->thread_cur_num++;
						if (count == num) {
							break;
						}
						pool->tid[i].id = 0;
						pthread_create(&(pool->tid[i].id), &pool->attr, tpool_working,(void*)pool);
						pool->tid[i].alive = 1;
						count++;
					}
				}
			}
		}
		pthread_mutex_unlock(&pool->lock);
		pthread_mutex_lock(&pool->lock);
		if (pool->shutdown == 1) {
			printf("%s\n","admin logout");
			pthread_mutex_unlock(&pool->lock);
			break;
		}
		pthread_mutex_unlock(&pool->lock);
		usleep(1000);
	}
	pthread_exit(NULL);
}

/*释放线程池*/
static int tpool_free(tpool* tp)
{
	if (tp == NULL) {
		debug("tpool_free: pool is null");
		return -1;
	}
	int ret = 1;
	//释放队列
	if (tp->queue_head != NULL) {
		task_t *del = tp->queue_head;
		task_t *tmp = NULL;
		while (del->next != NULL) {
			tmp = del->next;
			free(del);
			del = tmp;
		}
	}
	if (tp->tid != NULL) {
		//释放互斥锁
		pthread_mutex_lock(&tp->lock);
		pthread_mutex_destroy(&tp->lock);
		//释放条件变量
		pthread_cond_destroy(&tp->queue_empty);
		pthread_cond_destroy(&tp->queue_not_empty);
		pthread_cond_destroy(&tp->queue_not_full);
		//释放线程属性
		ret = pthread_attr_destroy(&tp->attr);
		if (ret != 0) {
			perror("pthread_attr destroy");
		}
		//释放线程列表
		free(tp->tid);
	}
	return 0;
}

/*创建线程池*/
tpool* tpool_create(const int min_num,const int max_num)
{
	tpool* tp = NULL;
	int i = 0;
	int ret = 1;
	int flag = 0;
	do {
		//内存初始化
		tp = (tpool*)malloc(sizeof(tpool));
		if(tp == NULL) {
			debug("tpool_create: pool malloc failed");
			break;
		}
		//变量初始化
		tp->thread_cur_num = min_num;
		tp->thread_min_num = min_num;
		tp->thread_max_num = max_num;
		tp->queue_head = NULL;
		tp->queue_tail = NULL;
		tp->queue_num = 0;
		tp->queue_max_num = 2*max_num;
		tp->queue_close = 0;
		tp->shutdown = 0;
		tp->admin = 0;
		tp->tid = NULL;
		//互斥锁初始化
		pthread_mutex_init(&tp->lock, NULL);
		//条件变量初始化
		ret = pthread_cond_init(&tp->queue_empty, NULL);
		if (ret != 0) {
			debug("tpool_create: pthread_cond_init failed");
			break;
		}
		ret = pthread_cond_init(&tp->queue_not_empty, NULL);
		if (ret != 0) {
			debug("tpool_create: pthread_cond_init failed");
			break;
		}
		ret = pthread_cond_init(&tp->queue_not_full, NULL);
		if(ret != 0) {
			debug("tpool_create: pthread_cond_init failed");
			break;
		}
		//初始化线程
		tp->tid = (thread_t*)malloc(sizeof(thread_t)*max_num);
		if (tp->tid == NULL) {
			debug("tpool_create: tid malloc failed");
			break;		
		}
		for (i = 0; i < max_num; i++) {
			tp->tid[i].id = 0;
			tp->tid[i].alive = 0;
		}
		//设置线程属性
		ret = pthread_attr_init(&tp->attr);
		if (ret != 0) {
			debug("tpool_create: pthread_attr_init failed");
			break;
		}
		ret = pthread_attr_setdetachstate(&tp->attr, PTHREAD_CREATE_DETACHED);
		if (ret != 0) {
			debug("tpool_create: pthread_attr_setdetachstate failed");
			break;
		}
		//启动线程
		for (i = 0;i < min_num; i++) {
			ret = pthread_create(&tp->tid[i].id, &tp->attr, tpool_working, (void*)tp);
			if (ret != 0) {
				debug("tpool_create: pthread_create failed");
				flag = 1;
				break;
			}
			tp->tid[i].alive = 1;
		}
		if (flag == 1) {
			break;
		}
		//启动管理线程
		ret = pthread_create(&tp->admin, &tp->attr, tpool_admin,(void*)tp);
		if (ret != 0) {
			debug("tpool_create: pthread_create admin failed");
			break;
		}
		return tp;
	} while (0);
	ret = tpool_free(tp);
	if (ret != 0) {
		debug("tpool_create: tpool_free");
	}
	return NULL;
}

/*添加任务*/
int tpool_add_task(tpool* tp, func execute, void* arg)
{
	if(tp == NULL||execute == NULL) {
		debug("tpool_add_task: parameter is null");
		return -1;
	}
	pthread_mutex_lock(&tp->lock);
	//等待队列未满
	while(tp->queue_num == tp->queue_max_num) {
		pthread_cond_wait(&tp->queue_not_full, &tp->lock);
	}
	//添加任务
	task_t *ptask = NULL;
	ptask = (task_t*)malloc(sizeof(task_t));
	if (ptask == NULL) {
		debug("tpool_add_task: task malloc failed");
		return -1;
	}
	ptask->execute = execute;
	ptask->arg = arg;
	ptask->next = NULL;
	//加入队列
	if (tp->queue_num == 0) {
		tp->queue_head = ptask;
		tp->queue_tail = tp->queue_head;
	} else {
		tp->queue_tail->next = ptask;
		tp->queue_tail = ptask;
	}
	tp->queue_num++;
	//广播队列不为空
	if(tp->queue_num != 0) {
		pthread_cond_broadcast(&tp->queue_not_empty);
	}
	if(tp->shutdown == 1||tp->queue_close == 1) {
		pthread_mutex_unlock(&tp->lock);
		return 0;
	}
	pthread_mutex_unlock(&tp->lock);
	return 0;
}

/*关闭线程池*/
static int tpool_close(tpool* tp)
{
	if (tp == NULL) {
		debug("tpool_destroy: parameter is null");
		return -1;
	}
	pthread_mutex_lock(&(tp->lock));
	tp->queue_close = 1;
	while(tp->queue_num !=0 ) {
		printf("queue_num = %d\n",tp->queue_num);
		pthread_cond_wait(&tp->queue_empty, &tp->lock);
	}
	tp->shutdown = 1;
	pthread_mutex_unlock(&tp->lock);
	pthread_cond_broadcast(&tp->queue_not_full);
	pthread_cond_broadcast(&tp->queue_not_empty);
	return 0;
}

/*释放线程池*/
int tpool_destroy(tpool* tp)
{
	if (tp == NULL) {
		debug("tpool_destroy: parameter is null");
		return -1;
	}
	int ret = 1;
	ret = tpool_close(tp);
	if (ret != 0) {
		debug("tpool_destroy: tpool_close");
		return -1;
	}
	ret = tpool_free(tp);
	if (ret != 0) {
		debug("tpool_destroy: tpool_free");
		return -1;
	}
	return 0;
}
