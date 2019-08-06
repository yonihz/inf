#include <stdio.h> /* for printf() */
#include <ctype.h> /* for isspace() */

void RmSpaces(char *str);

int main()
{
	char str1[] = "   This is	\t	a  string !   ";	
	RmSpaces(str1);
	printf("%s\n",str1);
	
	return (0);
}

void RmSpaces(char *str)
{
	int fwd = 0; /* forward index - to check all characters of the string */
	int bck = 0; /* back index - to point where to insert the next character, from forward to back */
	
	while (isspace(*(str+fwd)) && *(str+fwd) != '\0') /* start of string - check if character is white space, if true continue to the next until false */
	{
		fwd++;
	}	
	
	*(str+bck) = *(str+fwd); /* insert forward character instead of back character */
	bck++; /* increase back and forward indexes */
	fwd++;

	while (*(str+fwd) != '\0')
	{
		if isspace(*(str+fwd)) /* if found white space, insert it to back index (one space is wanted) */
		{
			*(str+bck) = *(str+fwd);
			bck++;
			fwd++;
		}	
				
		while (isspace(*(str+fwd))) /* continue until not white space, insert char to back  */
		{		
			fwd++;
		}

		*(str+bck) = *(str+fwd);
		bck++;
		fwd++;	
	}

	*(str+bck) = '\0';
	
	return;
}
	
