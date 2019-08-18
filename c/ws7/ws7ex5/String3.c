#include <ctype.h>	/* for tolower() */
#include <stdio.h>	/* for printf() */
#include <stdlib.h>	/* for malloc() */
#include <string.h>	/* for strspn() strcspn() */
#include "String.h"	/* for string functions implementation */

char *Strchr(const char* str, int c)
{
	for (; *str != '\0'; str++)
	{
		if (*str == c)
		{
			return ((char *)str); /* return pointer to c location in str */
		}
	}

	return (0);
}

/* ******************** */

char *Strcpy(char *dest, const char *src)
{	
	char* org = dest;

	for ( ; *src != '\0'; src++, dest++)
	{	
		*dest = *src; /* copy from src to dest */
	}

	*dest = '\0'; /* put null at string end */

	return (org);
}

