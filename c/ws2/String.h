#include <stddef.h>
#ifndef __STRING_H__
#define __STRING_H__

/* Strlen - calculate the length of a string */
size_t Strlen(const char *str);

/* Strcmp - compare two strings */
int Strcmp(const char *s1, const char *s2);

/* Strcpy - copy a string */
char *Strcpy(char *dest, const char *src);

/* Strncpy - copy a string (n bytes) */
char *Strncpy(char *dest, const char *src, size_t n);

/* Strcasecmp - compare two strings ignoring case */
int Strcasecmp(const char *s1, const char *s2);

/* Strncasecmp - compare two strings ignoring case (first n bytes) */
int Strncasecmp(const char *s1, const char *s2, size_t n);

/* Strchr - locate character in string */
char *Strchr(const char *str, int c);

/* Strdup - duplicate a string */
char *Strdup(const char *s);

/* Strcat - concatenate two strings */
char *Strcat(char *dest, const char *src);

/* Strncat - concatenate two strings (use at most n bytes from src) */
char *Strncat(char *dest, const char *src, size_t n);

/* Strstr - locate a substring */
char *Strstr(const char *haystack, const char *needle);

/* Strspn - search a string for a set of bytes */
size_t Strspn(const char *s, const char *accept);

/* Strtok - extract tokens from strings */
char *Strtok(char *str, const char *delim);

#endif


