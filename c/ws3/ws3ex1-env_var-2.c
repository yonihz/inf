#include <stdio.h> /* for printf() */
#include <string.h> /* for strlen() */
#include <stdlib.h> /* for calloc(), free() */
#include <ctype.h> /* for tolower() */

char** StrCpyLow(char** buffer_i, char** envp_i, char* next_str_pos);

int main(int argc, char* argv[], char* envp[])
{
	size_t i = 0;
	size_t len_envp_str = 0;
	size_t len_envp_arr = 0;
	size_t len = 0;

	char** buffer = 0;
	char* next_str_pos = 0;

	(void)argc; /* avoid errors of unused args */
	(void)argv;

	while (*(envp + i)) /* find length of array (envp) */
	{	
		len_envp_str += strlen(*(envp + i)) + 1;
		i++;
	}

	len_envp_arr = i;

	len = len_envp_str + len_envp_arr * sizeof(char *);
	
	buffer = calloc(len, sizeof(char)); /* calloc to buffer including array and all strings */

	next_str_pos = (char *)buffer + len_envp_arr * sizeof(char *); /* next string will be put after the array of pointers */

	i = 0;

	while (*(envp + i))
	{
		StrCpyLow(buffer + i, envp + i, next_str_pos); /* pass each pointer of the array to function for copy and lower-case */
		printf("%s\n", *(buffer + i)); /* print string of each lower-case env var */
		next_str_pos += strlen(*(envp + i)) + 1;		
		i++;
	}
	
	free(buffer);

	return (0);
}

char** StrCpyLow(char** buffer_i, char** envp_i, char* next_str_pos)
{
	char* ptr_buffer_i = 0;
	char* ptr_envp_i = 0;

	*buffer_i = next_str_pos;

	ptr_buffer_i = *buffer_i; /* use temp pointers to point to the addresses of the buffer string and env var string */
	ptr_envp_i = *envp_i;
	
	while (*ptr_envp_i)
	{
		*ptr_buffer_i = tolower(*ptr_envp_i); /* assign the lower-case chars of the env var string to the local string */
		ptr_envp_i++;
		ptr_buffer_i++;
	}	
	
	return buffer_i;
}

