/****************************************************************
* 																*
* FILE NAME: sort_dict.c		            				   	*
* 																*
* PURPOSE: Sort dictionary with merge sort         		        *
*                                                               *
* DATE: 09.12.19												*
* 																*
* Author: Yoni Horovitz											*
* 																*
****************************************************************/

#include <stdio.h> /* fopen, fclose */
#include <string.h> /* strlen, strcmp */
#include <stdlib.h> /* malloc */
#include <ctype.h> /* tolower */
#include <assert.h>

#define UNUSED(x) (void)(x)
#define DICT_NCOPIES 1
#define WORD_MAX_LENGTH 30

enum status_t {SUCCESS = 0, FAILUE};

FILE *file_ptr;

int main()
{
    int output_mergesort[ARR_SIZE] = {0};
    MergeSort(output_mergesort, input, ARR_SIZE);
}

char *DictCreate(void)
{
    size_t dict_total_chars = 0, dict_total_words = 0, i = 0;
    char *dict = NULL, *dict_start = NULL;
    char **dict_arr = NULL;
    char word[WORD_MAX_LENGTH];
    char *filename = "/usr/share/dict/american-english";

    file_ptr = fopen(filename, "r");

    if (NULL == file_ptr)
	{
		return (NULL);
	}

    fseek(file_ptr, 0, SEEK_END);
    dict_total_chars = ftell(file_ptr);
    fseek(file_ptr, 0, SEEK_SET);

    dict = (char*)malloc(dict_total_chars * DICT_NCOPIES);
    dict_start = dict;

    if (NULL == *dict)
    {
        return (NULL);
    }

    while (fgets(word, WORD_MAX_LENGTH, file_ptr))
    {
        strcpy(dict, word);
        dict += strlen(word); 
        dict_total_words++;
    }
    fseek(file_ptr, 0, SEEK_SET);

    dict_arr = (char**)malloc(dict_total_words * DICT_NCOPIES);

    dict++;
    *dict = '\0';

    fclose(file_ptr);

    return (dict_start);
}

void MergeSort(int *dest, int *src, size_t size)
{
    RecMergeSort(dest, src, 0, size - 1);
}

static void RecMergeSort(int *dest, int *src, size_t start, size_t end)
{
    if (start < end)
    {
        RecMergeSort(dest, src, start, ((start + end) / 2));
        RecMergeSort(dest, src, ((start + end) / 2) + 1, end);
        MergeSubArrays(dest, src, start, end);
    }
}

static void MergeSubArrays(int *dest, int *src, size_t start, size_t end)
{
    size_t i = 0, j = 0, k = 0;
    
    i = start;
    j = ((start + end) / 2) + 1;
    k = start;
    
    while ((i <= ((start + end) / 2)) && (j <= end))
    {
        if (src[i] < src[j])
        {
            dest[k] = src[i];
            ++i;
        }
        else
        {
            dest[k] = src[j];
            ++j;
        }
        
        ++k;
    }

    while (i <= ((start + end) / 2))
    {
        dest[k] = src[i];
        ++i;
        ++k;  
    }

    while (j <= end)
    {
        dest[k] = src[j];
        ++j;
        ++k;  
    }

    k = start;

    for (k = start; k <= end; ++k)
    {
        src[k] = dest[k];
    }
}