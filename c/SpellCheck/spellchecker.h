#include <stddef.h>

#include "hash.h"

hash_t *DictCreate(char *filename, hash_func_t hash_func, size_t nbuckets);

size_t DictHash(const void *dict_word);
 
/* returns 1 or 0 if word is found or not found, respectively */
int DictSpellCheck(hash_t *hash, char *str);

size_t FileCharCount(FILE *file_ptr);

void DictCopy(char* dict, FILE *file_ptr);

int StrcmpVoid(const void *s1, const void *s2);

void DictSpellCheckScan(hash_t *hash);

size_t DictSize(hash_t *hash);

int DictIsEmpty(hash_t *hash);

void DictRemove(hash_t *hash, const void *data);

void DictDestroy(hash_t *hash);