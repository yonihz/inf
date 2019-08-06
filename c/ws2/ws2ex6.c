#include <stdio.h> /* for printf() */
#include <stdlib.h> /* for malloc() */
#include "String.h" /* for Strlen() */

char* AddIntStr(const char* s1, const char* s2);

int main()
{
	/* test */
	printf("%s\n\n",AddIntStr("111","222"));
	printf("%s\n\n",AddIntStr("11","2222"));
	printf("%s\n\n",AddIntStr("2222","11"));
	printf("%s\n\n",AddIntStr("999","1"));
	printf("%s\n\n",AddIntStr("9999","1111"));
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

	printf("%s + %s\n",s1, s2); /* print for tests */

	len3 = len1 + 1; /* New string could be longer by 1 than the the longest between the two */

	if (len2 > len1)
	{
		len3 = len2 + 1;
	}
	
	s3 = malloc(len3+1);
	*(s3+len3+1) = '\0';

	s1 = s1 + len1 - 1; /* start of addition from the string end - where the smallet digit is */
	s2 = s2 + len2 - 1;
	s3 = s3 + len3 - 1;

	*s3 = '0'; /* init string for later addition */

	while ((s1 - s1_org) >= 0 && (s2 - s2_org) >= 0)
	{
		add = ((int)*s1 + (int)*s2 + (int)*s3 - 3*'0'); /* add two digits + 1 (if last add was 10 or more) */ 
		
		if (add > 9) /* if adding 10 or more add 1 to the next digit */
		{
			add -= 10;
			*(s3-1) = 1 + '0';				
		}
		else /* if adding less than 10 init the next digit with 0 */
		{
			*(s3-1) = 0 + '0';
		}	
			
		*s3 = add + '0';

		s1--;
		s2--;
		s3--;	
	}
	
	while ((s1 - s1_org) >= 0) /* if one string ended continue with the second one */
	{
		add = ((int)*s1 + (int)*s3 - 2*'0');
		if (add > 9)
		{
			add -= 10;
			*(s3-1) = 1 + '0';				
		}
		else
		{
			*(s3-1) = 0 + '0';
		}
		*s3 = add + '0';
		s1--;
		s3--;
	}
	
	while ((s2 - s2_org) >= 0)
	{
		add = ((int)*s2 + (int)*s3 - 2*'0');
		if (add > 9)
		{
			add -= 10;
			*(s3-1) = 1 + '0';				
		}
		else
		{
			*(s3-1) = 0 + '0';
		}
		*s3 = add + '0';
		s2--;
		s3--;
	}
	if (*s3 == '0') /* if largest digit is 0 return string string after it */
	{
		return (s3+1);
	}
	return (s3);
}

