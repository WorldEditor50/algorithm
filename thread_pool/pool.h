#ifndef __POOL_H
#define __POOL_H
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include<unistd.h>
#include<errno.h>
#include<signal.h>
#ifdef __cplusplus
extern "C" {
#endif
#define debug(msg) do { \
	printf("%s\n", msg); \ 
} while (0)
typedef void* (*func)(void* arg);
//线程任务
typedef struct task {
	func execute;
	void* arg;
	struct task *next;
}task_t;
//线程
typedef struct thread {
	pthread_t id;
	int alive;
} thread_t;
//线程池
typedef struct threadpool {
	//线程列表
	thread_t *tid;
	pthread_t admin;
	pthread_attr_t attr;
	pthread_mutex_t lock;
	int thread_cur_num;
	int thread_min_num;
	int thread_max_num;
	//任务队列
	task_t *queue_head;
	task_t *queue_tail;
	int queue_num;
	int queue_max_num;
	int queue_close;
	pthread_cond_t queue_empty;
	pthread_cond_t queue_not_empty;
	pthread_cond_t queue_not_full;
	int shutdown;
} tpool;
/* 创建线程池 */
tpool* tpool_create(const int min_num,const int max_num);
/* 添加任务 */
int tpool_add_task(tpool* tp,func execute,void* arg);
/* 释放线程池 */
int tpool_destroy(tpool* tp);
#ifdef __cplusplus
}
#endif
#endif //__THREADPOOL_H

