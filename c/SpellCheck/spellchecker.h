#include <stddef.h>

#include "hash.h"

hash_t *DictCreate(void);

size_t DictHash(const void *dict_word);
 
/* returns 1 or 0 if word is found or not found, respectively */
int DictSpellCheck(hash_t *hash, char *str);

size_t FileCharCount(FILE *file_ptr);

void DictCopy(char* dict, FILE *file_ptr);

int StrcmpVoid(const void *s1, const void *s2);