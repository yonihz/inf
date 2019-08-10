#include <stdio.h> /* for printf() */
#include <string.h> /* for strlen() */
#include <stdlib.h> /* for calloc(), free() */
#include <ctype.h> /* for tolower() */

char** StrDupLow(char** buffer_i, char** envp_i);

int main(int argc, char* argv[], char* envp[])
{
	int i = 0;
	char** buffer = 0;

	(void)argc; /* avoid errors of unused args */
	(void)argv;

	while (*(envp + i)) /* find length of array pointers (envp) */
	{	
		i++;
	}
	
	buffer = calloc(i + 1, sizeof(char *)); /* calloc to local array of pointers (buffer) */

	i = 0;

	while (*(envp + i))
	{
		StrDupLow(buffer + i, envp + i); /* pass each pointer of the array to function for duplicate and lower-case */
		printf("%s\n", *(buffer + i)); /* print string of each lower-case env var */
		free(*(buffer + i)); /* free each local pointer to string of env var */
		i++;
	}
	
	free(buffer); /* free local array of pointers */

	return (0);
}

char** StrDupLow(char** buffer_i, char** envp_i)
{
	char* ptr_buffer_i = 0;
	char* ptr_envp_i = 0;	
	
	/* calloc using length of each env var string, using the dereference of the pointer in the array of pointers, which stores the pointer to the env var string */
	/* assign calloc to the dereference of the pointer in the local array of pointers, so it would store the pointer to the local string */
	*buffer_i = calloc(strlen(*envp_i) + 1, sizeof(char));

	ptr_buffer_i = *buffer_i; /* use temp pointers to point to the addresses of the local string and env var string */
	ptr_envp_i = *envp_i;
	
	while (*ptr_envp_i)
	{
		*ptr_buffer_i = tolower(*ptr_envp_i); /* assign the lower-case chars of the env var string to the local string */
		ptr_envp_i++;
		ptr_buffer_i++;
	}	
	
	return buffer_i;
}

