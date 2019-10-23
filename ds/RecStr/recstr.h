/* Rev. 1.0*/ 
/* 22.10.19  16:00 */

#include <stddef.h>

/*returns length of string*/
size_t RecStrlen(const char *str);

/*return 0 if 2 chars are same, and -1/+1 according to difference*/
int RecStrcmp(const char *str1, const char *str2);

/*copies contents of str to dest, returns dest*/
char *RecStrcpy(char *dest, const char *str);

/*concatanates str1 to end of dest, returns dest*/
char *RecStrcat(char *dest, const char *src);

/*returns first instance of needle in haystack*/
char *RecStrstr(const char *haystack, const char *needle);