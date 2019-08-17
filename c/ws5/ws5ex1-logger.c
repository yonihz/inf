#include <stdio.h> /* for file functions */
#include <string.h> /* for strlen, strcmp, strncmp */
#include <stdlib.h> /* for malloc */

#define SIZE_ARR 5 /* struct array size, defined by number of operations types */
#define UNUSED(x) (void)(x)

/* file pointer declaration */
FILE *file_ptr;

/* enum definition */
enum op_status {PASS = 0, FAIL = 1, EXIT = 2};

/* operations functions */
enum op_status AppendStr(char* filename, char* input_str);
enum op_status PrependStr(char* filename, char* input_str);
enum op_status RemoveFile(char* filename, char* input_str);
enum op_status CountLines(char* filename, char* input_str);
enum op_status ExitProgram(char* filename, char* input_str);

/* comparison functions */
int CmpAllChars(const char* dest, const char* src);
int Cmp1Char(const char* dest, const char* src);
int CmpNull(const char* dest, const char* src);

int main(int argc, char** argv)
{
	int i = 0;
	int status = 0;
	char input_str[1000];
	
	/* typedef of pointers to functions */

	typedef int (*f_cmp_ptr_t)(const char*, const char*);	
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
	{"-exit", &CmpAllChars, &ExitProgram}, 
	{"-count", &CmpAllChars, &CountLines}, 
	{"-remove", &CmpAllChars, &RemoveFile}, 
	{"<", &Cmp1Char, &PrependStr},
	{"", &CmpNull, &AppendStr}
	};

	/* check if user entered a filename */

	if (2 != argc)
	{
		printf("Error: filename missing. Exiting program\n");
		return (0);
	}	

	/* main loop for operations */

	while (status != EXIT)
	{
		printf("Enter a string:\n");

		fgets(input_str, 1000, stdin);

		input_str[strcspn(input_str, "\n")] = 0; /* remove newline char from string */

		for (i = 0; i < SIZE_ARR; i++)
		{
			if (arr[i].f_cmp_ptr(input_str,arr[i].cmd_str) == 0)
			{	
				status = arr[i].f_op_ptr(argv[1], input_str);
				printf("\n");
				break;
			}
		}

		if (status == FAIL)
		{
			printf("Operation failed, try again.\n");
		}
	}

	return (0);
}

/* Line count function */

enum op_status CountLines(char* filename, char* input_str)
{	
	int count = 0;
	char c = 0;

	UNUSED(input_str);

	file_ptr = fopen(filename,"r");
	
	if (NULL == file_ptr)
	{
		printf("Error: no file\n");
		return(FAIL);
	}

	rewind(file_ptr); /* rewind file and check for newline chars in file */

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
	return (PASS);
}

/* Prepend function */

enum op_status PrependStr(char* filename, char* input_str)
{
	FILE* file_ptr_temp;
	int file_exists = 1;
	char c = 0;

	printf("OPERATION: Prepend\n");

	file_ptr = fopen(filename,"r"); /* check if file exists */

	if (NULL != file_ptr)
	{
		file_exists = 0;
		fclose(file_ptr);
	}

	if (file_exists != 0) /* if file exists, append text and return */
	{
		file_ptr = fopen(filename,"a");

		if (NULL == file_ptr)
		{
			printf("Error: file open failed\n");
			return(FAIL);
		}
	
		input_str += 1; /* increment string to exclude < char */
		fputs(input_str,file_ptr);
		fputs("\n",file_ptr);
		fclose(file_ptr);

		return (PASS);
	}

	file_ptr = fopen(filename,"r");

	file_ptr_temp = fopen("temp","w"); /* create a temp file for prepend */

	if (NULL == file_ptr || NULL == file_ptr_temp)
	{
		printf("Error: file open failed\n");
		return(FAIL);
	}

	input_str += 1;
	fputs(input_str, file_ptr_temp); /* append the input text to empty temp file */
	fputs("\n", file_ptr_temp);

	rewind(file_ptr); /* rewind original file and copy char by char to temp file */

	c = fgetc(file_ptr);

	while (c != EOF)
	{	
		fputc(c, file_ptr_temp);
		c = fgetc(file_ptr);
	}
	
	fputs("\n",file_ptr);

	fclose(file_ptr_temp);

	fclose(file_ptr);

	remove(filename); /* remove original file, then rename temp to original file */
	
	rename("temp", filename);

	return (PASS);
}

/* Append function */

enum op_status AppendStr(char* filename, char* input_str)
{
	printf("OPERATION: Append\n");

	file_ptr = fopen(filename,"a");
	
	if (NULL == file_ptr)
	{
		printf("Error: file open failed\n");
		return(FAIL);
	}

	fputs(input_str,file_ptr);
	fputs("\n",file_ptr);

	fclose(file_ptr);

	return (PASS);
}

/* Remove file function */

enum op_status RemoveFile(char* filename, char* input_str)
{
	int status;

	UNUSED(input_str);
		
	printf("OPERATION: Remove file\n\n");

	file_ptr = fopen(filename,"r");
	
	if (NULL == file_ptr)
	{
		printf("Error: no file\n");
		return(FAIL);
	}

	status = remove(filename); /* remove() function returns 0 if successful */

	return (status);
}

/* Exit program function */

enum op_status ExitProgram(char* filename, char* input_str)
{
	UNUSED(input_str);
	UNUSED(filename);

	printf("Exiting program\n");

	return (EXIT);
}

/* Compare string to all chars using strcmp function */

int CmpAllChars(const char* dest, const char* src)
{
	return (strcmp(dest, src));
}

/* Compare string to 1 char using strncmp function */

int Cmp1Char(const char* dest, const char* src)
{
	return (strncmp(dest, src, 1));
}

/* Null compare function - always return 0 */

int CmpNull(const char* dest, const char* src)
{
	UNUSED(dest);
	UNUSED(src);

	return (0);
}

