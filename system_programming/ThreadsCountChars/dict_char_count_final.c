#include <pthread.h> /* pthread_create, pthread_t, mutex */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stddef.h>

#define WORD_MAX_LENGTH 30
#define COPIES 1000
#define NUM_OF_THREADS 4
#define SIZE_OF_SHORT 65536
#define NUM_OF_LETTERS 256

static size_t end_LUT[NUM_OF_LETTERS];
static unsigned char *buff;
static size_t buff_size = 0;
static pthread_t threads[NUM_OF_THREADS];
static pthread_mutex_t mutex;

/******************************************************************************/
static unsigned char *LoadDictionary(size_t *dict_size);
static int InitThreads();
static void JoinThreads();
static void *ThreadFunc(void *thread_num);
static void PrintLUT();

int main()
{
    buff = LoadDictionary(&buff_size);
    buff_size /= 2;

    pthread_mutex_init(&mutex, NULL);
    
    /* create threads */
    if (-1 == InitThreads())
    {
        return -1;
    }
    
    /* join threads */
    JoinThreads();
    pthread_mutex_destroy(&mutex);
    
    PrintLUT();

    free(buff);

    return 0;
}

static void *ThreadFunc(void *thread_num)
{
    size_t i = 0;
    size_t local_short_LUT[SIZE_OF_SHORT] = {0};
    size_t local_char_LUT[NUM_OF_LETTERS] = {0};

    size_t idx_start = (size_t)thread_num;

    for(i = idx_start;
        i < buff_size;
        i+=NUM_OF_THREADS)
    {
        local_short_LUT[((short*)buff)[i]]++;
    }

    for (i = 0; i < SIZE_OF_SHORT - 1; i++)
    {
        local_char_LUT[*(unsigned char*)(&i)] += local_short_LUT[i];
        local_char_LUT[*((unsigned char*)(&i)+1)] += local_short_LUT[i];
    }
    
    pthread_mutex_lock(&mutex);
    for (i = 0; i < NUM_OF_LETTERS; i++)
    {
        end_LUT[i] += local_char_LUT[i];
    }
    pthread_mutex_unlock(&mutex);
    
    return NULL;
}

static void PrintLUT()
{
    int i = 0;

    for (i = 0; i < NUM_OF_LETTERS; i++)
    {
        printf("The num of '%c' appears is: %lu\n", (unsigned char)i, end_LUT[i]);
    }
}

static int InitThreads()
{
    size_t i = 0;

    for (i = 0; i < NUM_OF_THREADS; i++)
    {
        if (0 != pthread_create(&threads[i], NULL, &ThreadFunc, (void*)i))
        {
            return -1;
        }
    }

    return 0;
}

static void JoinThreads()
{
    size_t i = 0;

    for (i = 0; i < NUM_OF_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }
}


/*****************************************************************************/
static unsigned char *LoadDictionary(size_t *dict_size)
{
    char *dict_to_string = NULL;
    char *start_dict = NULL;
    size_t i = 0;
    size_t size = 0;

    FILE *fp = fopen("/usr/share/dict/american-english", "r");
    if (!fp) exit(1);

    fseek(fp, 0, SEEK_END);
    size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    if (NULL == (dict_to_string = (char *)malloc(size * COPIES + 1))) exit (1);
    start_dict = dict_to_string;

    for (i = 0; COPIES > i; ++i)
    {
        if (size != fread(dict_to_string, 1, size, fp)) exit(1);
        dict_to_string += size;
        fseek(fp, 0, SEEK_SET);
    }
    
    fclose(fp);
    
    *dict_to_string = '\0';
    
    *dict_size = size * COPIES;

    return ((unsigned char *)start_dict);
}
