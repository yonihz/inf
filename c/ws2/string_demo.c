#include <stdio.h>
#include <string.h>

int main()
{
	char str1[]="Apple Banana";
	char str2[]="Tomato";
	char str3[100];
	
	printf("str1: %s\n",str1);
	printf("str2: %s\n",str2);
	printf("str1 length: %ld\n",strlen(str1));
	printf("str2 length: %ld\n",strlen(str2));
	printf("strcmp str1 to str2: %d\n",strcmp(str2,str1));
	printf("strcpy str2 to str3: %s\n",strcpy(str3,str2));
	printf("strcpy str2 to str3: %s\n",str3);
	return 0;
}
