#include <stdio.h> /* for printf() */
#include <stdlib.h> /* for malloc() */
#include "String.h" /* for string functions implementation */
#include <string.h> /* for standard string functions */

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

	/* Strcpy and Strncpy */
	printf("Strcpy = %s\n\n",Strcpy(str5,str1));

	printf("Strncpy = %s\n\n",Strncpy(str6,str1,n));	
	
	/* Strcasecmp */
	printf("str1=%s\n",str1);
	printf("str2=%s\n",str2);
	printf("Strcasecmp str1 str2=%d\n\n",Strcasecmp(str1,str2));
	
	/* Strchr */
	printf("Strchr %c in %s = %s\n\n",c,str1,Strchr(str1,c));
	
	/* Strdup */
	printf("Strdup str1 = %s\nbuffer = %s\n\n",str1,Strdup(str1));
	
	/* Strcat */
	buffer1 = malloc(Strlen(str1)+Strlen(str2)+1);
	Strcpy(buffer1,str1);
	printf("Strcat str1 str2 %s\n\n",Strcat(buffer1,str2));

	/* Strncat */
	buffer2 = malloc(Strlen(str1)+n+1);
	Strcpy(buffer2,str1);
	printf("Strncat str1 str2 %s\n\n",Strncat(buffer2,str2,n));
	
	/* Strstr */
	printf("Strstr str3 str4 %s\n\n",Strstr(str3,str4));
	
	/* Strspn */
	printf("Strspn str3 str4 %d\n\n",(int)strspn(str3,str3));

	/* Strtok */
	
	printf("%s\n",str7);
	token = Strtok(str7,";");
	while (token != NULL)
	{
		printf("%s\n",token);
		token = Strtok(NULL, ";");
	}
	

	return (0);
}
