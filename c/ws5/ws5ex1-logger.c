#include <stdio.h> /* for file functions */
#include <string.h> /* for strlen, strcmp */
#include <stdlib.h> /* for malloc */

#define SIZE_ARR 4
#define UNUSED(x) (void)(x)

int AppendStr(FILE* file_ptr, char* input_str);
int SeekStart(FILE* file_ptr);
int RemoveFile(FILE* file_ptr);
int CountLines(FILE* file_ptr);
int Exit(FILE* file_ptr);

enum return_op {PASS = 0, FAIL = 1};
 
int main(int argc, char** argv)
{
	FILE *file_ptr;

	size_t len = 0;
	int i = 0;
	char* filename1 = 0;
	char input_str[1000];
	
	/* typedef of pointers to functions */

	typedef int (*f_cmp_ptr_t)(const char*, const char*);	
	typedef int (*f_op_ptr_t)(FILE*);

	/* struct includes command, pointers to comparison and operation functions */

	struct logger
	{
		char* cmd_str;
		f_cmp_ptr_t f_cmp_ptr;
		f_op_ptr_t f_op_ptr;
	};

	/* init struct array for each operation function */

	struct logger arr [SIZE_ARR] = { 
	{"-remove", &strcmp, &RemoveFile}, 
	{"-count", &strcmp, &CountLines}, 
	{"-exit", &strcmp, &Exit}, 
	{"<", &strcmp, &SeekStart}
	};
		
	UNUSED(argc);

	len = strlen(argv[1]) + 1; /* find length of filename string, malloc and strcpy from argv */
	filename1 = malloc(len);
	strcpy(filename1, argv[1]);

	while (1)
	{
		printf("Enter a string:\n");

		fgets(input_str, 1000, stdin);

		input_str[strcspn(input_str, "\n")] = 0; /* remove newline char from string */

		for (i = 0; i < SIZE_ARR; i++)
		{
			file_ptr = fopen(filename1,"w");

			if (arr[i].f_cmp_ptr(input_str,arr[i].cmd_str) == 0)
			{	
				if (file_ptr == NULL)
				{
					printf("Error in file\n");
					exit(FAIL);
				}				

				arr[i].f_op_ptr(file_ptr);

				break;
			}
		}
		
		if (i == SIZE_ARR || i == 3)
		{
			AppendStr(file_ptr, input_str);
		}

		fclose(file_ptr);
	}

	return (0);
}

int CountLines(FILE* file_ptr)
{
	char c = 0;
	int count = 0;

	c = getc(file_ptr);

	while (c != EOF)
	{
		if (c == 10)
		{
			count++;
		}
		
		c = getc(file_ptr);
	}

	printf("Number of lines is %d\n\n", count);
}

int SeekStart(FILE* file_ptr)
{
	fseek(file_ptr, 0, SEEK_SET);
	printf("OPERATION: Prepend\n\n");
}

int AppendStr(FILE* file_ptr, char* input_str)
{
	int status = FAIL;
	printf("status = %d\n", status);
	fputs(input_str, file_ptr);	
	fseek(file_ptr, 0, SEEK_END);
	fputc(10, file_ptr);
	printf("OPERATION: Append\n\n");
}

int RemoveFile(FILE* file_ptr)
{
	int status;
	printf("OPERATION: Remove file\n\n");
}

int Exit(FILE* file_ptr)
{
	printf("Exit\n");
	exit(PASS);
}

