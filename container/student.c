#include "student.h"
student *student_new(const char *name, int id, int age)
{
	if (name == NULL) {
		return NULL;
	}
	student *pStu = NULL;
	pStu = (student *)malloc(sizeof(student));
	if (pStu == NULL) {
		return NULL;
	}
	pStu->id = id;
	pStu->age = age;
	strcpy(pStu->name, name);
	return pStu;
}
int student_delete(student *pStu)
{
	if (pStu == NULL) {
		return STU_POINTER_NULL;
	}
	free(pStu);
	return STU_OK;
}
int student_write(FILE *fp, student *pStu)
{
	char buffer[256];
	memset(buffer, 0, sizeof(buffer));
	sprintf(buffer, "%s %d %d\n", pStu->name, pStu->id, pStu->age);
	fputs(buffer, fp);
	return 0;
}
int student_read(FILE *fp, student *pStu)
{
	char buffer[256];
	char id[3] = "";
	char age[3] = "";
	char *p = NULL;
	char *q = NULL;
	memset(buffer, 0, sizeof(buffer));
	fgets(buffer, 26, fp);
	p = buffer;
	q = pStu->name;
	while(*p != ' ') {
		*q++ = *p++;
	}
	*q = '\0';
	p++;
	id[0] = *p++;
	id[1] = *p++;
	id[2] = '\0';
	p++;
	age[0] = *p++;
	age[1] = *p++;
	age[2] = '\0';
	pStu->id = atoi(id);
	pStu->age = atoi(age);
	return 0;
}
void student_show(student *pStu)
{
	printf("%s %d %d\n", pStu->name, pStu->id, pStu->age);
	return;
}
int student_compare(student *pStu1, student *pStu2)
{
	int id1 = pStu1->id;
	int id2 = pStu2->id;
	int flag;
	if (id1 < id2) {
		flag = -1;
	} else if(id1 > id2) {
		flag = 1;
	} else {
		flag = 0; 
	}
	return flag;
}
int student_save(const char* fileName, student *pStu)
{
	if (fileName == NULL || pStu == NULL) {
		return STU_POINTER_NULL;
	}
	FILE *fp = fopen(fileName, "w+");
	if (fp == NULL) {
		return STU_POINTER_NULL;
	}
	student_write(fp, pStu);
	fclose(fp);
	return STU_OK;
}
int student_load(const char* fileName, student *pStu)
{
	if (fileName == NULL || pStu == NULL) {
		return STU_POINTER_NULL;
	}
	FILE *fp = fopen(fileName, "r+");
	if (fp == NULL) {
		return STU_POINTER_NULL;
	}
	student_read(fp, pStu);
	fclose(fp);
	return STU_OK;
}

void student_showAdapter(void *pStu)
{
	if (pStu == NULL) {
		return;
	}
	student *stu = (student*)pStu;
	return student_show(stu);
}
int student_writeAdapter(FILE *fp,void *pStu)
{
	if (pStu == NULL || fp == NULL) {
		return 1;
	}
	student *stu = (student*)pStu;
	return student_write(fp, stu);
}

int student_readAdapter(FILE *fp, void *pStu)
{
	if (pStu == NULL || fp == NULL) {
		return 1;
	}
	student *stu = (student*)pStu;
	return student_read(fp, stu);
}

int student_compareAdapter(void *pStu1, void  *pStu2)
{
	if (pStu1 == NULL || pStu2 == NULL) {
		return 0;
	}
	student *stu1 = (student*)pStu1;
	student *stu2 = (student*)pStu2;
	return student_compare(stu1, stu2);
}
void* student_newAdapter()
{
	return (void*)student_new("student0", 0, 0);
}

int student_deleteAdapter(void *pStu)
{
	student *stu = (student*)pStu;
	return student_delete(stu);
}
