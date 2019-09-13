#ifndef _BASIC_H
#define _BASIC_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#ifdef __cplusplus
extern "C" {
#endif
/* BASIC definition */
#define TRUE  1;
#define FALSE 0;
/* debug log */

#define FATAL		0x01
#define ALARM		0x02
#define ERROR		0x03
#define WARNING		0x04
#define INFO		0x05
#define DEBUG		0x06

#define BIT_SET(x, position)		((x) | (unsigned int*)(1 << ((position) - 1)))
#define BIT_CLEAR(x, position)		((x) & (unsigned int*)(~(1 << ((position) - 1))))
#define BIT_ON(x, position)			(((x) & (unsigned int*)(1 << ((position) - 1))) != 0)

#define DEBUG_MESSAGE(message) do { \
	printf("file: %s\t function: %s\t line: %d\n",__FILE__, __FUNCTION__, __LINE__); \
	printf("message: %s\n", message); \
} while (0)

#define LOG(level, fmt, args...) do { \
	if (BIT_ON(debug_flag, level)) { \
		printf("function: %s\t line: %d\n", __FUNCTION__, __LINE__); \
		printf("message: "); \
		printf(fmt, ##args); \
	} \
} while (0)

#define DEBUG_ASSERT(condition, errorCode) do { \
	if (!(condition)) { \
		printf("function: %s\t line: %d\n", __FUNCTION__, __LINE__); \
		return errorCode; \
	} \
} while (0)
typedef void* (*func)();
typedef int (*func1)(void*);
typedef int (*func2)(void*, void*);
typedef int (*funcIO)(FILE*, void*);
void log_writeToFile(const char *fileName, const char *message);
#ifdef __cplusplus
}
#endif// __cplusplus
#endif// _BASIC_H
