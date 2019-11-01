#include <stdio.h> /* fopen */
#include <string.h> /* strlen, strcmp */
#include <stdlib.h> /* malloc */
#include <ctype.h> /* tolower */
#include <assert.h>

#include "hash.h"
#include "spellchecker.h"

#define NLETTERS 26
#define EOT 3

FILE *file_ptr;

hash_t *DictCreate(void)
{
    /*char *filename = "/usr/share/dict/american-english";*/
    char *filename = "/home/yoni/git/c/SpellCheck/dict_test.c";
    size_t dict_size = 0;
    char *dict = NULL;
    hash_t *hash = NULL;
    int status = 0;

    hash = HTCreate(DictHash, NLETTERS, StrcmpVoid, NULL);

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