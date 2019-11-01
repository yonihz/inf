#include <stdlib.h>
#include <stdio.h>

#include "spellchecker.h"
#include "dlist.h"
#include "hash.h"

/* gd ../../ds/hash.c ../../ds/dlist.c spellchecker.c spellchecker_test.c -I../../ds/include */

struct hash
{
    hash_func_t hash_func;
    comp_func_t comp_func;
    dlist_t **htable;
    size_t nbuckets;
    void *param;
};

void Test(void);

int main()
{  
    Test();
    return (0);
}

void Test(void)
{
    size_t i = 0;
    char strings[6][10] = {"apple", "orange", "banana", "cake", "beer", "lemon"};
    hash_t *dict = NULL;
    dlist_t *dict_letter = NULL;
    dlist_iter_t itr = NULL;
    dlist_iter_t itr_end = NULL;
    int is_spell_correct = 0;
    size_t letter = 'c' - 'a';
    
    dict = DictCreate();

    dict_letter = dict->htable[letter];

    itr_end = DListEnd(dict_letter);

    printf("Dictionary DList of a letter %c:\n", (char)letter);
    for (itr = DListBegin(dict_letter); itr != itr_end; itr = DListNext(itr))
    {
        printf("%s ", (char*)DListGetData(itr));
    }
    printf("\n");
    /*
    for (i = 0; i < 6; i++)
    {
        is_spell_correct = DictSpellCheck(dict, strings[i]);
        printf("Word: %s, Spellcheck: %d", strings[i], is_spell_correct);
    }
    */

}