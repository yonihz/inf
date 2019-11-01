#include <stdio.h> /* fopen */
#include <string.h> /* strlen, strcmp */
#include <stdlib.h> /* malloc */
#include <ctype.h> /* tolower */
#include <assert.h>

#include "hash.h"
#include "spellchecker.h"

#define EOT 3

FILE *file_ptr;

hash_t *DictCreate(char *filename, hash_func_t hash_func, size_t nbuckets)
{
    size_t dict_size = 0;
    char *dict = NULL;
    hash_t *hash = NULL;
    int status = 0;

    hash = HTCreate(hash_func, nbuckets, StrcmpVoid, NULL);

    file_ptr = fopen(filename, "r");

    dict_size = FileCharCount(file_ptr);
    dict = (char*)malloc(dict_size * sizeof(char));
    DictCopy(dict, file_ptr);

    while (*dict != EOT)
    {
        status = HTInsert(hash, dict);

        assert(status == 0);

        dict = dict + strlen(dict) + 1;
    }

    return (hash);
}

size_t DictHash(const void *dict_word)
{
    size_t key = 0;

    key = (tolower(*(char*)dict_word) - 'a');

    if (!isalpha(*(char*)dict_word))
    {
        key = ('z' - 'a');
    } 

    return (key);
}

int DictSpellCheck(hash_t *hash, char *str)
{
    int status = 0;
    
    if (NULL != HTFind(hash, str))
    {
        status = 1;
    }

    return (status);
}

void DictSpellCheckScan(hash_t *hash)
{
    int is_valid = 0;
    char str[50];

    printf("Enter string:\n");

    while (1)
    {
        scanf("%s", str);

        if (*str == '0')
        {
            return;
        }

        is_valid = DictSpellCheck(hash, str);

        if (is_valid == 1)
        {
            printf("%s is in the dictionary\n", str);
        }
        else
        {
            printf("%s is not in the dictionary\n", str);
        }
    }
}

size_t FileCharCount(FILE *file_ptr)
{
    size_t dict_size = 0;

    rewind(file_ptr);

    while (EOF != getc(file_ptr))
    {
        ++dict_size;
    }

    return (dict_size + 1);
}

void DictCopy(char* dict, FILE *file_ptr)
{
    size_t word_len = 0;
    char dict_word[50];

    rewind(file_ptr);

    while (NULL != fgets(dict_word, 50, file_ptr))
    {
        word_len = strcspn(dict_word, "\n");
        dict_word[word_len] = '\0';
        strcpy(dict, dict_word);
        dict = dict + word_len + 1;
    }

    *dict = EOT;
}

int StrcmpVoid(const void *s1, const void *s2)
{
    return (strcmp((const char*)(s1), (const char*)(s2)));
}

size_t DictSize(hash_t *hash)
{
    return HTSize(hash);
}

int DictIsEmpty(hash_t *hash)
{
    return HTIsEmpty(hash);
}

void DictRemove(hash_t *hash, const void *data)
{
    HTRemove(hash, data);
}

void DictDestroy(hash_t *hash)
{
    HTDestroy(hash);
}