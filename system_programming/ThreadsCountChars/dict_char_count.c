#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stddef.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>

#define NTHREADS 8
#define ASCII_RANGE 256
#define WORD_MAX_LENGTH 30
#define COPIES 1000

typedef struct
{
    char *str;
    size_t min;
    size_t max;
} char_count_args_t;

static size_t LUT[ASCII_RANGE];
pthread_mutex_t lock;
sem_t sem;

/******************************************************************************/
static char *LoadDictionaryToHash(char *dict_path);
void PrintLUT(size_t* arr);
void *CharCount(void *str_void);

int main()
{
    char *str = LoadDictionaryToHash(NULL);
    pthread_t th[NTHREADS];
    size_t counter = 0;
    size_t seg_size = 0, seg_remainder;
    size_t i = 0;
    char_count_args_t char_count_args[NTHREADS];
    
    sem_init(&sem, 0, 0);
    counter = strlen(str);
    seg_size = counter / NTHREADS;
    seg_remainder = counter % NTHREADS;

    for (i = 0; i < NTHREADS; i++)
    {
        (char_count_args[i]).str = str;
        (char_count_args[i]).min = i * seg_size;
        (char_count_args[i]).max = (i + 1) * seg_size;
        /* printf("min: %lu, max: %lu \n", (char_count_args[i]).min, (char_count_args[i]).max); */
    }

    (char_count_args[NTHREADS - 1]).max += seg_remainder;

    printf("nthreads = %lu\n", (size_t)NTHREADS);
    printf("Total chars = %lu\n\n", counter);
/*
    while(*str)
    {
        counter++;
        LUT[(unsigned char)(*str)]++;
        str++;
    }
*/

    for (i = 0; i < NTHREADS; i++)
    {
        pthread_create(&th[i], NULL, &CharCount, &(char_count_args[i]));
    }

    for (i = 0; i < NTHREADS; i++)
    {
        pthread_join(th[i], NULL);
    }
/*
    for (i = 0; i < NTHREADS; i++)
    {
        sem_wait(&sem);
    }
*/
    PrintLUT(LUT);

    free(str);

    return 0;
}


static char *LoadDictionaryToHash(char *dict_path)
{
    FILE *fp = NULL;
    char word[WORD_MAX_LENGTH];
    char *dict_to_string = NULL;
    char *start_dict = NULL;
    size_t total_len = 0;
    size_t i = 0;

    (void)(dict_path);

    fp = fopen("/usr/share/dict/american-english", "r");

    if (!fp)
    {
        return NULL;
    }

    fseek(fp, 0, SEEK_END);
    total_len = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    dict_to_string = (char*)malloc(total_len * COPIES);   /* 1000 times size of dict */
    start_dict = dict_to_string;


    for(i = 0; i < COPIES; ++i)
    {
        while (fgets(word, WORD_MAX_LENGTH, fp))
        {
            /* *(word + strlen(word) - 1) = '\0'; */               /* remove '\n' */
            strcpy(dict_to_string, word);
            dict_to_string += strlen(word); 
        }
        fseek(fp, 0, SEEK_SET);
    }

    dict_to_string++;
    *dict_to_string = '\0';

    fclose(fp);

    return start_dict;
}

void PrintLUT(size_t* arr)
{
    size_t i = 0;
    size_t count = 0;

    printf("\n");
    for (i = 0; i < ASCII_RANGE; i++)
    {
        if (arr[i] != 0)
        {
            printf("%3lu = %-5lu\t", i, arr[i]);

            count++;
            if ((count % 10) == 0)
            {
                printf("\n");
            }
        }
    }
    printf("\n");
}

void *CharCount(void *char_count_args_void)
{
    char_count_args_t char_count_args;
    char *str = NULL;
    size_t i = 0, min = 0, max = 0;
    size_t LUT_local[ASCII_RANGE] = {0};
    /* clock_t start, end;
    double cpu_time_used; */

    char_count_args = *(char_count_args_t*)char_count_args_void;

    str = char_count_args.str;
    min = char_count_args.min;
    max = char_count_args.max;
    
    /* start = clock(); */

    for (i = min; i < max; i++)
    {
        LUT_local[(unsigned char)(str[i])]++;
    }

    for (i = 0; i < ASCII_RANGE; i++)
    {
        if (LUT_local[i] > 0)
        {
            __sync_fetch_and_add(&LUT[i], LUT_local[i]);
            /*LUT[i] += LUT_local[i];*/
        }
    }
/*
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("cpu_time_used = %f\n", cpu_time_used);
*/
    /* sem_post(&sem); */

/*
    pthread_mutex_lock(&lock);

    for (i = 0; i < ASCII_RANGE; i++)
    {
        if (LUT_local[i] > 0)
        {
            LUT[i] += LUT_local[i];
        }
    }

    pthread_mutex_unlock(&lock);
*/

    return (NULL);
}