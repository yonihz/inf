#ifndef _HASH_H_OL74
#define _HASH_H_OL74

/* rev 0.1*/

#include <stddef.h> /*size_t, NULL*/

typedef struct hash hash_t;

typedef int(*comp_func_t)(const void *data, const void *param);

typedef size_t(*hash_func_t)(const void *data);

typedef int(*op_func_t)(void* data, void* param);



hash_t *HTCreate(hash_func_t hash_func, size_t num_of_buckets, comp_func_t comp, void *param);

void HTDestroy(hash_t *hash);

int HTInsert(hash_t *hash, void *data);

void HTRemove(hash_t *hash, const void *data);

void *HTFind(hash_t *hash, const void *data);

int HTForEach(hash_t *hash, op_func_t op_func,void *param);

size_t HTSize(const hash_t *hash);

int HTIsEmpty(const hash_t *hash);

#endif

