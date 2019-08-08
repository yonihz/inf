#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

char* StrDupLow(char** buffer, char** envp);

int main(int argc, char* argv[], char* envp[])
{
	int len = 0;
	int i = 0;
	char** buffer = 0;
	char** envp_org = envp;
	char** buffer_org;

	(void)argc;
	(void)argv;

	while (envp[i])
	{
		len++;		
		envp[i];
		i++;
	}
	
	buffer = calloc(len + 1, sizeof(char));

	buffer_org = buffer;

	while (*envp)
	{
		StrDupLow(buffer,envp);	
		printf("%s\n", *buffer);
		envp++;
		buffer++;
	}

	return (0);
}

char* StrDupLow(char** buffer, char** envp)
{
	char* buffer_org;

	*buffer = calloc(strlen(*envp) + 1, sizeof(char));

	buffer_org = *buffer;
	
	while (**envp)
	{
		**buffer = tolower(**envp);
		(*envp)++;
		(*buffer)++;
	}
	
	printf("%s\n", *buffer);	
	
	return buffer_org;
}

