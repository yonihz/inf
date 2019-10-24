/* Rev. 1.0*/ 
/* 22.10.19  16:00 */

#include <stddef.h>
#include "slist.h"
#include "stack.h"

size_t RecStrlen(const char *str);

int RecStrcmp(const char *str1, const char *str2);

int RecStrncmp(const char *str1, const char *str2, size_t n);

char *RecStrcpy(char *dest, const char *src);

char *RecStrcat(char *dest, const char *src);

char *RecStrstr(const char *haystack, const char *needle);

slist_node_t* RecSListFlip(slist_node_t* head);

unsigned int ItrFib(unsigned int n);

unsigned int RecFib(unsigned int n);

void SortUnsortedStack(stack_t *stack);