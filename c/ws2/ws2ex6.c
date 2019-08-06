#include <stdio.h>
#include <stdlib.h>
#include "String.h"

char* AddIntStr(const char* s1, const char* s2);

int main()
{
	printf("%s\n",AddIntStr("129","234"));
	return (0);
}

char* AddIntStr(const char* s1, const char* s2)
{
		
	size_t len1 = Strlen(s1);
	size_t len2 = Strlen(s2);
	size_t len3;
	char* s1_org = (char *)s1;
	char* s2_org = (char *)s2;	
	int add;
	char* s3;
	
	len3 = len1;

	if (len2 > len1)
	{
		len3 = len2;
	}
	else if (len1 == len2)
	{			
		if (*s1 + *s2 > 9)
		{
			len3 = len1 + 1;
		}
	}
	
	s3 = malloc(len3+1);
	*(s3+len3+1) = '\0';

	s1 = s1 + len1;
	s2 = s2 + len2;
	s3 = s3 + len3;


	while (s1 != s1_org && s2 != s2_org)
	{
		add = ((int)*s1 + (int)*s2 - 96);

		if (add > 9)
		{
			add -= 10;
			*(s3-1) = 1;				
		}

		*s3 = *s3 + add + 48;
		printf("%c\n",*s3);
		s1--;
		s2--;
		s3--;	
	}
	
	while (s1 != s1_org)
	{
		*s3 = *s1;
		s1--;
		s3--;
	}
	
	while (s2 != s2_org)
	{
		*s3 = *s2;
		s2--;
		s3--;
	}

	return (s3);
}

