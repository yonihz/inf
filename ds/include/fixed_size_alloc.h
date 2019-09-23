#ifndef _FIXED_SIZE_ALLOC_H_
#define _FIXED_SIZE_ALLOC_H_

#include <stddef.h>

typedef struct fs_alloc fs_alloc_t;

size_t FSAllocSuggestSize(size_t total, size_t size);
void* FSAllocAlloc(fs_alloc_t* fs_alloc, size_t num, size_t size);
int FSAllocFree(fs_alloc_t* fs_alloc, void* ptr);
fs_alloc_t* FSAllocInit(size_t suggest_size);
size_t FSAllocCountFree(fs_alloc_t* fs_alloc);

#endif

