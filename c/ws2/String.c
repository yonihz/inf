#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "String.h"

size_t Strlen(const char *s)
{
	size_t i;
	for (i=0; *(s+i) != '\0'; i++);
	return i;
}

int Strcmp(const char *s1, const char *s2)
{
	int i;
	int d;
	for (i=0; *(s1+i) != '\0' && *(s2+i) != '\0'; i++);
	{
		d = *(s1+i) - *(s2+i);
		if (d != 0)
		{
			return d;
		}
	}
	if (*(s1+i) != '\0')
	{
		return *(s1+i);
	}
	else if (*(s2+i) != '\0')
	{
		return -*(s2+i);
	}
	else
	{
		return 0;
	}
}

char *Strcpy(char *dest, const char *src)
{	
	int i;
	for (i=0; *(src+i) != '\0'; i++)
	{	
		*(dest+i)=*(src+i);
	}
	*(dest+i)='\0';
	return dest;
}

char *Strncpy(char *dest, const char *src, size_t n)
{	
	size_t i;
	for (i=0; *(src+i) != '\0' && i < n ; i++)
	{	
		*(dest+i)=*(src+i);
	}
	*(dest+i)='\0';
	return dest;
}

int Strcasecmp(const char *s1, const char *s2)
{
	int i;
	int d;
	for (i=0; *(s1+i) != '\0' && *(s2+i) != '\0'; i++)
	{
		d = tolower(*(s1+i)) - tolower(*(s2+i));
		if (d != 0)
		{
			return d;
		}
	}
	if (*(s1+i) != '\0')
	{
		return *(s1+i);
	}
	else if (*(s2+i) != '\0')
	{
		return -*(s2+i);
	}
	else
	{
		return 0;
	}
}

char *Strchr(const char *str, int c)
{
	int i;
	for (i=0; *(str+i) != '\0'; i++)
	{
		if (c==*(str+i))
		{
			return (char *)(str+i);
		}
	}
	return 0;
} 

char *Strdup(const char *s)
{
	char *s_t;	
	s_t = (char *)malloc(sizeof(s));
	return Strcpy(s_t,s);
	
}

char *Strcat(char *dest, const char *src)
{
	Strcpy((dest+(int)Strlen(dest)),src);
	return dest;
}

char *Strncat(char *dest, const char *src, size_t n)
{
	Strncpy((dest+(int)Strlen(dest)),src,n);
	return dest;
}






