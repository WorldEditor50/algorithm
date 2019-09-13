#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "student.h"

int main()
{
	int ret = 0;
	student p;
	student *stu = student_new("google", 11, 20);
	if (stu == NULL) {
		printf("stu malloc failed\n");
		return 0;
	}
	ret = student_save("class.txt", stu);
	if (ret != 0) {
		printf("stu write failed\n");
		return 0;
	}
	ret = student_load("class.txt", &p);
	if (ret != 0) {
		printf("stu read failed\n");
		return 0;
	}
	student_show(&p);
	ret = student_delete(stu);
	if (ret != 0) {
		printf("stu delete failed\n");
		return 0;
	}
	return 0;
}
