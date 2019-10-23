#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "recstr.h"

int main()
{
	char* str1="Hello world";
	char* str2="HELLO world";
	char* str3="This is a very long string";
	char* str4="very";
	char str5[100];
	char str6[100];
	char str7[]="This;is;;a;very;long;;;string";
	char c = 'w';
	char *buffer1;
	char *buffer2;
	char *buffer3;	
	int n = 2;
	char *token;

	/* Strlen */
	printf("str1 = %s\n",str1);
	printf("Strlen str1 = %lu\n\n",Strlen(str1));

	/* Strcmp */
	printf("str1=%s\n",str1);
	printf("str2=%s\n",str2);
	printf("Strcmp str1 str1 = %d\n",Strcmp(str1,str1));
	printf("Strcmp str1 str2 = %d\n\n",Strcmp(str1,str2));

	/* Strcpy */
	printf("Strcpy = %s\n\n",Strcpy(str5,str1));
	
	/* Strcat */
	buffer1 = malloc(Strlen(str1)+Strlen(str2)+1);
	Strcpy(buffer1,str1);
	printf("Strcat str1 str2 %s\n\n",Strcat(buffer1,str2));
	free(buffer1);
	
	/* Strstr */
	printf("Strstr str3 str4 %s\n\n",Strstr(str3,str4));
	

	return (0);
}