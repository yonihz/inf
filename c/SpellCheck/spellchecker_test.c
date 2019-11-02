#include <stdlib.h>
#include <stdio.h>

#include "spellchecker.h"
#include "hash.h"

#define NLETTERS 26

/* gd ../../ds/hash.c ../../ds/dlist.c spellchecker.c spellchecker_test.c -I../../ds/include */


/*
TODO: splice, vlg, hash function
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

    char *user_dict = NULL;
    hash_t *dict_hash = NULL;
    int is_spell_correct = 0;

    /* char *filename = "/usr/share/dict/american-english"; */
    char *filename = "/home/yoni/git/c/SpellCheck/dict_test.c";
    
    dict_hash = DictCreate(filename, DictHash, NLETTERS, &user_dict);

    printf("-----\n");
    printf("Dictionary size: %lu\n", HTSize(dict_hash));

    printf("-----\n");
    printf("Dictionary IsEmpty after DictCreate: %d\n", HTIsEmpty(dict_hash));

    printf("-----\n");
    printf("ForEach PrintAll:\n");
    DictPrintAll(dict_hash);

    printf("-----\n");
    printf("ForEach PrintAll after spellcheck for %s:\n", dict_words[5]);
    DictSpellCheck(dict_hash, dict_words[5]);
    DictPrintAll(dict_hash);

    printf("-----\n");
    printf("Spellcheck for test words:\n");
    for (i = 0; i < 6; i++)
    {
        is_spell_correct = DictSpellCheck(dict_hash, strings[i]);
        printf("%s (%d)\n", strings[i], is_spell_correct);
    }

    DictRemove(dict_hash, strings[0]);

    printf("-----\n");
    printf("Test dictionary after removing %s:\n", strings[0]);
    for (i = 0; i < 6; i++)
    {
        is_spell_correct = DictSpellCheck(dict_hash, strings[i]);
        printf("%s (%d)\n", strings[i], is_spell_correct);
    }

    printf("-----\n");
    printf("Dictionary size after remove: %lu\n", HTSize(dict_hash));

    for (i = 0; i < 9; i++)
    {
        DictRemove(dict_hash, dict_words[i]);
    }

    printf("-----\n");
    printf("Dictionary IsEmpty after removing all entries: %d\n", HTIsEmpty(dict_hash));

    DictDestroy(dict_hash, user_dict);
}

void TestScan(void)
{
    char *user_dict = NULL;
    hash_t *dict_hash = NULL;
    char *filename = "/usr/share/dict/american-english";
    
    dict_hash = DictCreate(filename, DictHash, NLETTERS, &user_dict);
    DictSpellCheckScan(dict_hash);
}