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
	int fwd = 0;
	int bck = 0;
	
	while (isspace(*(str+fwd)) && *(str+fwd) != '\0')
	{
		fwd++;
	}	
	
	*(str+bck) = *(str+fwd);
	bck++;
	fwd++;

	while (*(str+fwd) != '\0')
	{
		if isspace(*(str+fwd))
		{
			*(str+bck) = *(str+fwd);
			bck++;
			fwd++;
		}	
				
		while (isspace(*(str+fwd))) 
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
	
