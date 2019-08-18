#include <ctype.h>	/* for tolower() */
#include <stdio.h>	/* for printf() */
#include <stdlib.h>	/* for malloc() */
#include <string.h>	/* for strspn() strcspn() */
#include "String.h"	/* for string functions implementation */

size_t Strlen(const char *s)
{
	size_t i = 0;

	for (i = 0; *(s + i) != '\0'; i++) /* loop string up to '\0' */
	{};

	return (i);
}

/* ******************** */

int Strcmp(const char *s1, const char *s2)
{	
	for ( ; *s1 != '\0' && *s2 != '\0'; s1++, s2++)
	{
		if (*s1 != *s2) /* check if chars are different */
		{
			return (*s1 - *s2); /* return char diff */
		}
	}

	return (*s1 - *s2); /* return char diff if one or both strings ended */
}
