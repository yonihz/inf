#include <stdio.h> /* fopen, fclose */
#include <string.h> /* strlen, strcmp */
#include <stdlib.h> /* malloc */
#include <ctype.h> /* tolower */
#include <assert.h>

#include "hash.h"
#include "spellchecker.h"

#define EOT 3
#define HTABLE_SIZE 26
#define UNUSED(x) (void)(x)

enum status_t {SUCCESS = 0, FAILUE};
enum sp_status_t {SP_FAILUE = 0, SP_SUCCESS};

FILE *file_ptr;

hash_t *DictCreate(char *filename, hash_func_t hash_func, size_t nbuckets, char **dict)
{
    size_t dict_size = 0;
    hash_t *hash = NULL;
    int status = 0;
    char *dict_ptr = NULL;

    hash = HTCreate(hash_func, nbuckets, StrcmpVoid, NULL);
    file_ptr = fopen(filename, "r");

    if (NULL == file_ptr)
	{
		return (NULL);
	}

    dict_size = FileCharCount(file_ptr);
    *dict = (char*)malloc(dict_size * sizeof(char));

    if (NULL == *dict)
    {
        return (NULL);
    }

    dict_ptr = *dict;
    DictCopy(dict_ptr, file_ptr);

    while (*dict_ptr != EOT)
    {
        status = HTInsert(hash, dict_ptr);

        assert(status == 0);

        dict_ptr = dict_ptr + strlen(dict_ptr) + 1;
    }

    fclose(file_ptr);
    file_ptr = NULL;

    return (hash);
}

size_t DictHash(const void *dict_word)
{
    size_t key = 0;

    assert(dict_word);

    key = (tolower(*(char*)dict_word) - 'a');

    if (!isalpha(*(char*)dict_word))
    {
        key = ('z' - 'a');
    } 

    return (key);
}

/*
size_t DictHash(const void *dict_word)
{
    size_t hash = 5381;
    int c = 0;
    char *word = (void*)dict_word;

    while ((c = *word++))
    {
        hash = ((hash << 5) + hash) + tolower(c);
    }

    hash = hash % HTABLE_SIZE;
    printf("hash = %lu\n\n", hash);
    return (hash);
}
*/

int DictSpellCheck(hash_t *hash, char *str)
{
    int status = SP_FAILUE;

    assert(hash && str);
    
    if (NULL != HTFind(hash, str))
    {
        status = SP_SUCCESS;
    }

    return (status);
}

void DictSpellCheckScan(hash_t *hash)
{
    int is_valid = 0;
    char str[50];

    assert(hash);

    printf("Enter a string to spellcheck (0 to quit):\n");

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

    assert(file_ptr);

    rewind(file_ptr);

    while (EOF != getc(file_ptr))
    {
        ++dict_size;
    }

    return (dict_size + 2);
}

void DictCopy(char* dict, FILE *file_ptr)
{
    size_t word_len = 0;
    char dict_word[50];

    assert(dict && file_ptr);

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
    assert(hash);

    return HTSize(hash);
}

int DictIsEmpty(hash_t *hash)
{
    assert(hash);

    return HTIsEmpty(hash);
}

void DictRemove(hash_t *hash, const void *data)
{
    assert(hash);

    HTRemove(hash, data);
}

void DictDestroy(hash_t *hash, char *dict)
{
    assert(hash && dict);

    HTDestroy(hash);
    hash = NULL;
    free(dict);
    dict = NULL;
}

int DictPrintAll(hash_t *hash)
{
    int status = 0;

    assert(hash);

    status = HTForEach(hash, DictPrintWord, NULL);
    printf("\n");

    return (status);
}

int DictPrintWord(void *data, void *param)
{
    UNUSED(param);
    printf("%s ", (char*)data);

    return (0);
}