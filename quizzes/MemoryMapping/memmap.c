/* static function */
static void StaticFunc(void);

/* extern function */
extern void ExternFunc(void);

/* non-const static global var */
static int static_global_var = 5;

/* const static global var */
static int const_static_global_var = 20;

/* non-const global var */
int global_var = 8;

/* const global var */
int const_global_var = 10;

/* env var */
/* command line arg */
int main(int argc, char *argv[], char *envp[])
{
    /* string literal */
    char* str_literal = "string";

    /* non-const local var */
    int local_var = 1;

    /* const local var */
    int const_local_var = 1;

    /* non-const static local var */
    static int static_local_var = 2;

    /* const static local var */
    const static int const_static_local_var = 15;

    /* heap var */
    int* heap_var = NULL;
    heap_var = malloc(sizeof(int));

    return (0);
}

static void StaticFunc(void)
{
    int a = 1;
    return;
}