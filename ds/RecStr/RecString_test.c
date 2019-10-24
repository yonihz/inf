#include <stdio.h> /* printf */
#include "RecStr.h"

void CheckStrcmp();
void CheckStrcpy();
void CheckStrcat();
void CheckStrstr();

int main()
{
	printf("CheckStrcmp() check:\n");
	CheckStrcmp();
	printf("CheckStrcpy() check:\n");
	CheckStrcpy();
	printf("Strcat() check:\n");
	CheckStrcat();
	printf("Strstr() check:\n");
	CheckStrstr();
	
	return 0;
}

void CheckStrcmp()
{
	char *str1 = "abc";
	char *str2 = "abc";
	char result = 0;

	printf("The value of the first stirng is: :%s\n", str1);
	printf("The value of the second string is: :%s\n", str2);
	result = RecStrcmp(str1, str2);
	printf("and the result is: :%d\n", result);
}


void CheckStrcpy()
{
	char *test_arr[] = {"first", "second", "", "5$%^%^(&/0kjk"};
	char dest[50];
	int i;
	
	for (i = 0; i < 4; i++)
	{
		RecStrcpy(dest, *(test_arr+i));
		printf("The result of copy is - :%s\n", dest);
	}

}


void CheckStrcat()
{
	const char src[] = "string";
	char dest[50] = "just a ";
	printf("dest: :%s\n", dest);
	printf("source: :%s\n", src);	
	RecStrcat(dest, src);
	printf("The new string is :%s\n", dest); 
}

void CheckStrstr()
{
	char str[] = "just three words";
	char str_prob[] = "three";
	char* temp = NULL;

	printf("The haystack is :%s\n", str);
	printf("The needle is :%s\n", str_prob);
	temp = RecStrstr(str, str_prob);
	printf("The matching value is :%s\n", temp);	
}