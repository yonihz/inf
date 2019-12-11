/****************************************************************
* 																*
* FILE NAME: shuffle_sort_dict.c		            		 	*
* 																*
* PURPOSE: Shuffle and sort dictionary             		        *
*                                                               *
* DATE: 09.12.19												*
* 																*
* Author: Yoni Horovitz											*
* 																*
****************************************************************/

#include <stdio.h> /* fopen, fclose */
#include <string.h> /* strlen, strcmp */
#include <stdlib.h> /* malloc */
#include <time.h> /* time */
#include <pthread.h>
#include <assert.h>

#define UNUSED(x) (void)(x)
#define DICT_NCOPIES 1000
#define WORD_MAX_LENGTH 30
#define NTHREADS 4

enum status_t {SUCCESS = 0, FAILUE};

typedef struct {
    char **src;
    char **dest;
    size_t start;
    size_t end;
} merge_sort_args_t;

FILE *file_ptr;

char **DictCreate(char **dict_str_start, size_t *size);
void DictArrShuffle(char **dict_arr, size_t size);
void SwapCharPtr(char **a, char **b);
void PrintArr(char **arr, size_t size);
void MergeMultiThreads(char **dest, char **src, size_t size);
void *MergeSingleThread(void *merge_sort_args_void);
static void RecMergeSort(char **dest, char **src, size_t start, size_t end);
static void MergeSubArrays(char **dest, char **src, size_t start, size_t end);
static void MergeSubArraysGeneral(char **dest, char **src, size_t start, size_t end, size_t part_idx);

int main()
{
    char *dict_str_start = NULL;
    char **dict_arr = NULL, **buffer = NULL;
    size_t size = 0;

    srand(time(NULL));

    printf("NTHREADS: %d, DICT_NCOPIES: %d\n", NTHREADS, DICT_NCOPIES);
    dict_arr = DictCreate(&dict_str_start, &size);

    DictArrShuffle(dict_arr, size);
/*
    printf("After Shuffle:\n");
    PrintArr(dict_arr, size);
*/
    buffer = (char **)malloc(size * sizeof(char*));

    MergeMultiThreads(buffer, dict_arr, size);

/*
    printf("\nAfter Sort:\n");
    PrintArr(dict_arr, size);
*/
    free(dict_str_start);
    free(dict_arr);
    free(buffer);

    return (0);
}

char **DictCreate(char **dict_str_start, size_t *size)
{
    size_t dict_total_chars = 0, dict_total_words = 0, i = 0, word_len = 0;
    char *dict_str = NULL;
    char **dict_arr = NULL;
    char c = 0;
    char *filename = "/usr/share/dict/american-english";

    file_ptr = fopen(filename, "r");

    fseek(file_ptr, 0, SEEK_END);
    dict_total_chars = ftell(file_ptr);
    fseek(file_ptr, 0, SEEK_SET);

    dict_str = (char*)malloc(dict_total_chars * DICT_NCOPIES + 1);
    *dict_str_start = dict_str;

    for (i = 0; i < DICT_NCOPIES; ++i)
    {
        fread(dict_str, 1, dict_total_chars, file_ptr);
        dict_str += dict_total_chars;
        fseek(file_ptr, 0, SEEK_SET);
    }

    c = getc(file_ptr);

	while (c != EOF)
	{
		if (c == 10)
		{
			dict_total_words++;
		}
		
		c = getc(file_ptr);
	}
    fseek(file_ptr, 0, SEEK_SET);

    fclose(file_ptr);

    *dict_str = '\0';
    dict_str = *dict_str_start;

    *size = dict_total_words * DICT_NCOPIES;

    dict_arr = (char**)malloc(*size * sizeof(char*));
    
    for (i = 0; i < *size; i++)
    {
        dict_arr[i] = dict_str;
        word_len = strcspn(dict_str, "\n");
        dict_str[word_len] = '\0';
        dict_str = dict_str + word_len + 1;
    }

    return (dict_arr);
}

void DictArrShuffle(char **dict_arr, size_t size)
{
	size_t i = 0;
    size_t rand_idx;

	for (i = 0; i < size; i++)
	{
        rand_idx = rand() % size;
		SwapCharPtr(&dict_arr[i], &dict_arr[rand_idx]);
	}
}

void SwapCharPtr(char **a, char **b)
{
    char *temp = NULL;
    temp = *a;
    *a = *b;
    *b = temp;
}

void PrintArr(char **arr, size_t size)
{
    size_t i = 0;

    for (i = 0; i < size; i++)
    {
        printf("%s ", arr[i]);

        if (i == 100)
        {
            break;
        }
    }

    printf("\n");
}

void MergeMultiThreads(char **dest, char **src, size_t size)
{
    pthread_t th[NTHREADS];
    merge_sort_args_t merge_sort_args[NTHREADS];
    size_t i = 0, seg_size = 0;

    seg_size = size / NTHREADS;

    for (i = 0; i < NTHREADS; i++)
    {
        merge_sort_args[i].dest = dest;
        merge_sort_args[i].src = src;
        merge_sort_args[i].start = i * seg_size;
        merge_sort_args[i].end = (i + 1) * seg_size - 1;
    }

    (merge_sort_args[NTHREADS - 1]).end = size - 1;

    for (i = 0; i < NTHREADS; i++)
    {
        pthread_create(&th[i], NULL, &MergeSingleThread, &(merge_sort_args[i]));
    }

    for (i = 0; i < NTHREADS; i++)
    {
        pthread_join(th[i], NULL);
    }

    for (i = 1; i < NTHREADS; i++)
    {
        MergeSubArraysGeneral(
            dest,
            src,
            merge_sort_args[0].start,
            merge_sort_args[i].end,
            merge_sort_args[i].start - 1);
    }
}

void *MergeSingleThread(void *merge_sort_args_void)
{
    merge_sort_args_t *merge_sort_args = (merge_sort_args_t*)merge_sort_args_void;

    RecMergeSort(
        merge_sort_args->dest,
        merge_sort_args->src,
        merge_sort_args->start,
        merge_sort_args->end);

    return (NULL);
}

static void RecMergeSort(char **dest, char **src, size_t start, size_t end)
{
    if (start < end)
    {
        RecMergeSort(dest, src, start, ((start + end) / 2));
        RecMergeSort(dest, src, ((start + end) / 2) + 1, end);
        MergeSubArrays(dest, src, start, end);
    }
}

static void MergeSubArrays(char **dest, char **src, size_t start, size_t end)
{
    size_t i = 0, j = 0, k = 0;
    
    i = start;
    j = ((start + end) / 2) + 1;
    k = start;
    
    while ((i <= ((start + end) / 2)) && (j <= end))
    {
        if (strcmp(src[i], src[j]) < 0)
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

static void MergeSubArraysGeneral(char **dest, char **src, size_t start, size_t end, size_t part_idx)
{
    size_t i = 0, j = 0, k = 0;
    
    i = start;
    j = part_idx + 1;
    k = start;
    
    while ((i <= part_idx && (j <= end)))
    {
        if (strcmp(src[i], src[j]) < 0)
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

    while (i <= part_idx)
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