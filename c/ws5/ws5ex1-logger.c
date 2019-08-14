#include <stdio.h> /* for file functions */
#include <string.h> /* for strlen, strcmp, strncmp */
#include <stdlib.h> /* for malloc */

#define SIZE_ARR 4
#define UNUSED(x) (void)(x)

FILE *file_ptr;

/* enum definition */
enum op_status {PASS = 0, FAIL = 1};

/* operations functions */
enum op_status AppendStr(char* filename, char* input_str);
enum op_status PrependStr(char* filename, char* input_str);
enum op_status RemoveFile(char* filename, char* input_str);
enum op_status CountLines(char* filename, char* input_str);
enum op_status ExitProgram(char* filename, char* input_str);

/* comparison functions */
int CmpAllChars(const char* dest, const char* src, size_t len);
int CmpNChars(const char* dest, const char* src, size_t len);

int main(int argc, char** argv)
{
	size_t len = 0;
	int i = 0;
	char* filename1 = 0;
	char input_str[1000];
	
	/* typedef of pointers to functions */

	typedef int (*f_cmp_ptr_t)(const char*, const char*, size_t);	
	typedef enum op_status (*f_op_ptr_t)(char*, char*);

	/* struct includes command, pointers to comparison and operation functions */

	struct logger
	{
		char* cmd_str;
		f_cmp_ptr_t f_cmp_ptr;
		f_op_ptr_t f_op_ptr;
	};

	/* init struct array for each operation function */

	struct logger arr [SIZE_ARR] = { 
	{"-remove", &CmpAllChars, &RemoveFile}, 
	{"-count", &CmpAllChars, &CountLines}, 
	{"-exit", &CmpAllChars, &ExitProgram}, 
	{"<", &CmpNChars, &PrependStr}
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

		len = strlen(input_str);

		for (i = 0; i < SIZE_ARR; i++)
		{
			if (arr[i].f_cmp_ptr(input_str,arr[i].cmd_str,len) == 0)
			{	
				arr[i].f_op_ptr(filename1, input_str);
				break;
			}
		}
		
		if (i == SIZE_ARR)
		{
			AppendStr(filename1, input_str);
		}
	}

	return (0);
}

enum op_status CountLines(char* filename, char* input_str)
{
	int status = PASS;	
	int count = 0;
	char c = 0;

	UNUSED(input_str);

	file_ptr = fopen(filename,"r");
	
	if (file_ptr == NULL)
	{
		printf("Error in file open\n");
		status = FAIL;
		return(status);
	}

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
	return (status);
}

enum op_status PrependStr(char* filename, char* input_str)
{
	int status = PASS;

	UNUSED(input_str);

	printf("OPERATION: Prepend\n\n");
	return (status);
}

enum op_status AppendStr(char* filename, char* input_str)
{
	int status = PASS;

	UNUSED(input_str);

	printf("OPERATION: Append\n\n");
	return (status);
}

enum op_status RemoveFile(char* filename, char* input_str)
{
	int status = PASS;

	UNUSED(input_str);

	printf("OPERATION: Remove file\n\n");
	return (status);
}

enum op_status ExitProgram(char* filename, char* input_str)
{
	int status = PASS;

	UNUSED(input_str);

	printf("Exit\n");
	exit(status);
}

int CmpAllChars(const char* dest, const char* src, size_t len)
{
	UNUSED(len);
	return (strcmp(dest, src));
}

int CmpNChars(const char* dest, const char* src, size_t len)
{
	if (*src == '<')
	{
		len = 1;
	}

	return (strncmp(dest, src, len));
}

