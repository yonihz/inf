#include <stdlib.h>
#include <stdio.h>

#include "spellchecker.h"
#include "hash.h"

#define NLETTERS 26

/* gd ../../ds/hash.c ../../ds/dlist.c spellchecker.c spellchecker_test.c -I../../ds/include */


/*
TODO: ForEach, caching, vlg, hash function
*/

void TestBasic(void);
void TestScan(void);

int main()
{  
    TestBasic();
    /*TestScan();*/
    return (0);
}

void TestBasic(void)
{
    size_t i = 0;
    char strings[6][10] = {"apple", "orangek", "bananan", "cake", "beer", "lemon"};
    char dict_words[9][10] = {"camera", "apple", "at", "orange", "cake", "cat", "beer", "blah", "car"};

    hash_t *dict = NULL;
    int is_spell_correct = 0;

    /*char *filename = "/usr/share/dict/american-english";*/
    char *filename = "/home/yoni/git/c/SpellCheck/dict_test.c";
    
    dict = DictCreate(filename, DictHash, NLETTERS);

    printf("Basic Tests::\n\n");
    printf("Spellcheck for test words:\n");

    for (i = 0; i < 6; i++)
    {
        is_spell_correct = DictSpellCheck(dict, strings[i]);
        printf("%s (%d)\n", strings[i], is_spell_correct);
    }

    printf("\n");

    printf("Dictionary size: %lu\n", HTSize(dict));
    printf("Dictionary IsEmpty after DictCreate: %d\n", HTIsEmpty(dict));

    DictRemove(dict, strings[0]);

    printf("\nTest dictionary after removing %s:\n", strings[0]);
    for (i = 0; i < 6; i++)
    {
        is_spell_correct = DictSpellCheck(dict, strings[i]);
        printf("%s (%d)\n", strings[i], is_spell_correct);
    }

    printf("\n");

    printf("Dictionary size after remove: %lu\n", HTSize(dict));

    for (i = 0; i < 9; i++)
    {
        DictRemove(dict, dict_words[i]);
    }

    printf("Dictionary IsEmpty after removing all entries: %d\n", HTIsEmpty(dict));

    DictDestroy(dict);
}

void TestScan(void)
{
    hash_t *dict = NULL;
    char *filename = "/usr/share/dict/american-english";
    
    dict = DictCreate(filename, DictHash, NLETTERS);
    DictSpellCheckScan(dict);
}