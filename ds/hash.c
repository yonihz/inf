#include <stdlib.h>
#include <string.h>

#include "hash.h"
#include "dlist.h"

struct hash
{
    hash_func_t hash_func;
    comp_func_t comp_func;
    dlist_t **htable;
    size_t nbuckets;
    void *param;
};

hash_t *HTCreate(hash_func_t hash_func, size_t num_of_buckets, comp_func_t comp, void *param)
{
    hash_t *new_hash = NULL;
    size_t i = 0;

    new_hash = (hash_t*)malloc(sizeof(hash_t));
    new_hash->hash_func = hash_func;
    new_hash->comp_func = comp;
    new_hash->param = param;    
    new_hash->nbuckets = num_of_buckets;
    new_hash->htable = (dlist_t**)malloc(num_of_buckets * sizeof(dlist_t*));

    for (i = 0; i < num_of_buckets; ++i)
    {
        new_hash->htable[i] = DListCreate();

        if (NULL == new_hash->htable[i])
        {
            new_hash->nbuckets = i;
            HTDestroy(new_hash);
            return (NULL);
        }
    }

    return (new_hash);
}

void HTDestroy(hash_t *hash)
{
    size_t i = 0;

    for (i = 0; i < hash->nbuckets; ++i)
    {
        DListDestroy(hash->htable[i]);
    }

    free(hash);
}

int HTInsert(hash_t *hash, void *data)
{
    size_t key = 0;
    dlist_iter_t itr = NULL;

    key = hash->hash_func(data);
    itr = DListPushFront(hash->htable[key], data);

    return (DListIsSame(itr, DListEnd(hash->htable[key])));
}

void HTRemove(hash_t *hash, const void *data)
{
    size_t key = 0;
    dlist_iter_t itr_remove = NULL, itr_begin = NULL, itr_end = NULL;

    key = hash->hash_func(data);
    itr_begin = DListBegin(hash->htable[key]);
    itr_end = DListEnd(hash->htable[key]);
    itr_remove = DListFind(itr_begin, itr_end, hash->comp_func, (void*)data);
    DListRemove(itr_remove);
}

void *HTFind(hash_t *hash, const void *data)
{
    size_t key = 0;
    dlist_iter_t itr_found = NULL, itr_begin = NULL, itr_end = NULL;
    void *data_found = NULL;

    key = hash->hash_func(data);
    itr_begin = DListBegin(hash->htable[key]);
    itr_end = DListEnd(hash->htable[key]);
    itr_found = DListFind(itr_begin, itr_end, hash->comp_func, (void*)data);
    data_found = DListGetData(itr_found);

    /* caching - move found data to the beginning of the list */
    /*
    if (!DListIsSame(itr_found, itr_end))
    {
        DListSplice(itr_begin, itr_found, DListNext(itr_found));
    }
    */
    
    if (NULL != data_found)
    {
        DListRemove(itr_found);
        DListPushFront(hash->htable[key], data_found);
    }
    
    return (data_found);
}

int HTForEach(hash_t *hash, op_func_t op_func,void *param)
{
    size_t i = 0;
    int status = 0;
    dlist_iter_t itr = NULL, itr_begin = NULL, itr_end = NULL;

    for (i = 0; (i < hash->nbuckets) && (0 == status); ++i)
    {
        itr_begin = DListBegin(hash->htable[i]);
        itr_end = DListEnd(hash->htable[i]);

        for (itr = itr_begin; (itr != itr_end) && (0 == status); itr = DListNext(itr))
        {
            status = op_func(DListGetData(itr), param);
        }
    }

    return (status);
}

size_t HTSize(const hash_t *hash)
{
    size_t size = 0, i = 0;

    for (i = 0; i < hash->nbuckets; ++i)
    {
        size += DListSize(hash->htable[i]);
    } 

    return (size);
}

int HTIsEmpty(const hash_t *hash)
{
    size_t is_empty = 1, i = 0;

    for (i = 0; (i < hash->nbuckets) && (1 == is_empty); ++i)
    {
        is_empty = DListIsEmpty(hash->htable[i]);
    } 

    return (is_empty);
}