#include <stdio.h> /* fopen */
#include <string.h> /* strlen, strcmp */
#include <stdlib.h> /* malloc */

#include "hash.h"
#include "spellchecker.h"

#define NLETTERS 26

FILE *file_ptr;

hash_t *DictCreate(void)
{
    char *filename = "/usr/share/dict/american-english";
    size_t dict_size = 0;
    char *dict = NULL;
    hash_t *hash = NULL;

    hash = HTCreate(DictHash, NLETTERS, StrcmpVoid, NULL);

    file_ptr = fopen(filename, "r");

    dict_size = FileCharCount(file_ptr);
    dict = (char*)malloc(dict_size * sizeof(char));
    DictCopy(dict, file_ptr);

    while (*dict != EOF)
    {
        HTInsert(hash, dict);
        dict = dict + strlen(dict);
    }

    return (hash);
}

size_t DictHash(const void *dict_word)
{
    size_t key = 0;

    key = (size_t)*(char*)dict_word;

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
    char c = 0;
    size_t dict_size = 0;

    rewind(file_ptr);
    c = getc(file_ptr);

    while (c != EOF)
    {
        ++dict_size;
        c = getc(file_ptr);
    }

    return (dict_size);
}

void DictCopy(char* dict, FILE *file_ptr)
{
    size_t word_len = 0;
    char *dict_word = NULL;

    do
    {
        fgets(dict_word, 50, file_ptr);
        word_len = strcspn(dict_word, (char*)'\n');
        dict_word[word_len] = '\0';
        strcpy(dict, dict_word);
        dict = dict + word_len;
    }
    while (*dict_word == EOF);
}

int StrcmpVoid(const void *s1, const void *s2)
{
    return (strcmp((const char*)(s1), (const char*)(s2)));
}