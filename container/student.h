#ifndef _STUDENT_H
#define _STUDENT_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef enum {
	STU_OK,
	STU_ERR,
	STU_POINTER_NULL,
	STU_MEM_ERR
}STU_EUM;
typedef struct student student;
struct student {
	int id;
	int age;
	char name[20];
	void (*setName)(student* pStu, const char *name);
	void (*setAge)(student* pStu, int age);
	void (*setId)(student* pStu, int id);
	void (*show)(student* pStu);
};
student *student_new(const char *name, int id, int age);
int student_delete(student *pStu);
int student_write(FILE *fp,student *pStu);
int student_read(FILE *fp, student *pStu);
void student_show(student *pStu);
void student_setName(student* pStu, const char *name);
void student_setAge(student* pStu, int age);
void student_setId(student* pStu, int id);
int student_compare(student *pStu1, student *pStu2);
int student_save(const char* fileName, student *pStu);
int student_load(const char* fileName, student *pStu);
/* adapter */
extern void student_showAdapter(void *pStu);
extern int student_writeAdapter(FILE *fp,void *pStu);
extern int student_readAdapter(FILE *fp, void *pStu);
extern int student_compareAdapter(void *pStu1, void  *pStu2);
extern void* student_newAdapter();
extern int student_deleteAdapter(void *pStu);
#endif// _STUDENT_H
