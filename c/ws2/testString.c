#include <stdio.h>
#include <stdlib.h>
#include "String.h"
#include <string.h>

int main()
{
	char str1[]="Hello world";
	char str2[]="Welcome to the jungle";
	char str3[]="Hello bob";
	char str_dest[100];
	char str4[]="HELLO world";
	char c = '-';
	char str5[]="Xl";

	
	printf("str1=%s\n",str1);
	printf("str2=%s\n",str2);
	printf("str3=%s\n",str3);
	printf("str4=%s\n",str4);
	printf("str5=%s\n",str5);
	printf("\n");
	
	/*
	printf("Strlen str1=%lu\n",Strlen(str1));
	printf("Strlen str2=%lu\n",Strlen(str2));
	printf("Strlen str3=%lu\n",Strlen(str3));
	printf("\n");
	*/
	
	/*
	printf("Strcmp str1 str1=%d\n",Strcmp(str1,str1));
	printf("Strcmp str1 str2=%d\n",Strcmp(str1,str2));
	printf("Strcmp str1 str3=%d\n",Strcmp(str1,str3));
	printf("\n");
	*/

	/*
	printf("Strcpy str_dest str1=%s\n",Strcpy(str_dest,str1));
	printf("\n");
	*/

	/*
	printf("Strncpy str_dest str1 2=%s\n",Strncpy(str_dest,str1,2));
	printf("\n");
	*/
	
	/*
	printf("Strcmp str1 str2=%d\n",Strcmp(str1,str2));
	*/

	/*
	printf("Strchr str1 o=%s\n",Strchr(str1,c));
	*/

	/*
	printf("Strdup str1 %s %s\n",str1,Strdup(str1));
	*/

	/*
	printf("Strncat str1 str2 %s\n",Strncat(str1,str2,2));
	*/

	/*
	printf("Strstr str2 str5 %s\n",Strstr(str2,str5));
	*/

	printf("Strspn str1 str5 %d\n",Strspn(str1,str5));

	return 0;
}
