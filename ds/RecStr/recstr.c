#include <stddef.h>

#include "RecStr.h"

int RecStrncmp(const char *str1, const char *str2, size_t n);

size_t RecStrlen(const char *str)
{
    if ('\0' == *str)
    {
        return (0);
    }

    return (1 + RecStrlen(str+1));
}

int RecStrcmp(const char *str1, const char *str2)
{
    if ((*str1 != *str2) || (*str1 == '\0'))
    {
        return (*str1 - *str2);
    }

    return RecStrcmp(str1 + 1, str2 + 1);
}

int RecStrncmp(const char *str1, const char *str2, size_t n)
{
    if ((*str1 != *str2) || (n == 1))
    {
        return (*str1 - *str2);
    }
    n--;
    return RecStrncmp(str1 + 1, str2 + 1, n - 1);
}

char *RecStrcpy(char *dest, const char *src)
{
    *dest = *src;

    if ('\0' == *src)
    {
        return (dest);
    }

    return (RecStrcpy(dest + 1, src + 1) - 1);
}

char *RecStrcat(char *dest, const char *src)
{
    RecStrcpy((dest + RecStrlen(dest)), src);

    return (dest);
}

char *RecStrstr(const char *haystack, const char *needle)
{
    size_t len_needle = 0, len_haystack = 0;
    if (*haystack == *needle)
    {
        len_needle = RecStrlen(needle);
        len_haystack = RecStrlen(haystack);

        if (len_needle <= len_haystack && RecStrncmp(needle, haystack, len_haystack) == 0)
        {
            return (char*)haystack;
        }

        if (haystack == '\0')
        {
            return NULL;
        }
    }
    return RecStrstr(++haystack, needle);    
}