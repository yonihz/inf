#include <ctype.h>	/* for tolower() */
#include <stdio.h>	/* for printf() */
#include <stdlib.h>	/* for malloc() */
#include <string.h>	/* for strspn() strcspn() */
#include "String.h"	/* for string functions implementation */

char *Strncpy(char *dest, const char *src, size_t n)
{	
	size_t i = 0;	
	char* org = dest;

	for (i = 0; *src != '\0' && i < n; src++, dest++, i++)
	{	
		*dest = *src; /* copy from src to dest */
	}

	*dest = '\0'; /* put null at string end */

	return (org);
}

/* ******************** */

int Strcasecmp(const char *s1, const char *s2)
{	
	for ( ; *s1 != '\0' && *s2 != '\0'; s1++, s2++)
	{
		if (tolower(*s1) != tolower(*s2)) /* check if chars are different (both lower case) */
		{
			return (tolower(*s1) - tolower(*s2)); /* return char diff (both lower case) */
		}
	}

	return (tolower(*s1) - tolower(*s2)); /* return char diff (both lower case) if one or both strings ended */
}
