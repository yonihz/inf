#include <stddef.h>
#ifndef __STRING_H__
#define __STRING_H__


size_t Strlen(const char *str);
int Strcmp(const char *s1, const char *s2);
char *Strcpy(char *dest, const char *src);
char *Strncpy(char *dest, const char *src, size_t n);
int Strcasecmp(const char *s1, const char *s2);
int Strncasecmp(const char *s1, const char *s2, size_t n);
char *Strchr(const char *str, int c);
char *Strdup(const char *s);
char *Strcat(char *dest, const char *src);
char *Strncat(char *dest, const char *src, size_t n);

#endif


