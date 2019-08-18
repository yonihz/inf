#include <ctype.h>	/* for tolower() */
#include <stdio.h>	/* for printf() */
#include <stdlib.h>	/* for malloc() */
#include <string.h>	/* for strspn() strcspn() */
#include "String.h"	/* for string functions implementation */

char *Strdup(const char *s)
{
	char *buffer = NULL;

	buffer = (char *)malloc(Strlen(s)+1); /* allocate memory to new string */
	
	if (NULL == buffer) /* return null if malloc failed */
	{
		return (NULL);
	}

	return (Strcpy(buffer,s));
}

/* ******************** */

char *Strcat(char *dest, const char *src)
{
	Strcpy((dest+Strlen(dest)), src); /* append src to dest end */

	return (dest);
}

/* ******************** */

char *Strncat(char *dest, const char *src, size_t n)
{
	Strncpy((dest+Strlen(dest)), src, n); /* append n bytes of src to dest end */

	return (dest);
}

/* ******************** */

char *Strstr(const char *haystack, const char *needle)
{
	int i = 0,j = 0;

	for (i = 0; *(haystack + i) != '\0'; i++)
	{
		if (*(haystack + i) == *needle) /* loop haystack until equal to first char of needle */
		{
			for (j = 0;
			*(needle + j) != '\0' && *(needle + j) == *(haystack + i + j);
			j++); /* check all chars of needle match */
			if (*(needle + j) == '\0')
			{
				return ((char *)(haystack + i));
			}
		}
	}

	return (NULL);	
}

/* ******************** */

size_t Strspn(const char *s, const char *accept)
{
	size_t i = 0, j = 0;

	for (i = 0; *(s + i) != '\0'; i++)
	{
		for (j = 0; *(s + i) != *(accept + j); j++) /* check each char on s if equal to any char on accept */
		{		
			if (*(accept + j) == '\0')
			{
				return (i);
			}
		}
	}
	return (i);
}

/* ******************** */

char *Strtok(char *str, const char *delim)
{
	static char* ptr = NULL;
	char* tok = NULL;	
	int n = 0, m = 0;

	
	if (str != NULL)
	{
		ptr = str;
		n = strspn(ptr, delim);
		ptr = ptr + n;
		
		if (*ptr == '\0')
		{
			return (NULL);
		}
		
		tok = ptr;

		m = strcspn(ptr, delim);
		ptr = ptr + m;

		n = strspn(ptr, delim);
		ptr = ptr + n;

		*(ptr-n) = '\0';
		
		return (tok);
	}
	else
	{
		if (*ptr == '\0')
		{
			return (NULL);
		}

		tok = ptr;		
	
		m = strcspn(ptr, delim);
		ptr = ptr + m;

		n = strspn(ptr, delim);
		ptr = ptr + n;

		*(ptr-n) = '\0';

		return (tok);
	}
}
	
