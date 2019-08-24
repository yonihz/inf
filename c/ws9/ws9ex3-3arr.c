#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Print3Arr(char* arr1, char* arr2, char* arr3);

int main()
{
	/* common arr1 arr2: Q L M G F */
	char* arr1 = "A Q L M Y R G F";
	char* arr2 = "B L F M Q G J P";
	char* arr3 = "K Q X Z W L D I";

	printf("arr1: %s\narr2: %s\narr3: %s\n", arr1, arr2, arr3);

	Print3Arr(arr1, arr2, arr3);

	return (0);
}

void Print3Arr(char* arr1, char* arr2, char* arr3)
{
	size_t i = 0;
	size_t len1 = 0;
	size_t len2 = 0;
	size_t len3 = 0;
	size_t len4 = 256;
	char* arr4 = calloc(len4+1, sizeof(char));
	*(arr4+len4) = '\0';

	len1 = strlen(arr1);
	len2 = strlen(arr2);
	len3 = strlen(arr3);

	for (i = 0; i < len1; i++)
	{
		arr4[(size_t)arr1[i]] = 1;
	}

	for (i = 0; i < len2; i++)
	{
		arr4[(size_t)arr2[i]] = (arr4[(size_t)arr2[i]] + 2) / 3 * 2;
	}

	for (i = 0; i < len3; i++)
	{
		arr4[(size_t)arr3[i]] = (arr4[(size_t)arr3[i]]) * 0;
	}

	printf("arr4: ");
	for (i = 0; i < len4; i++)
	{
		arr4[i] == 2 ? printf("%c ", (int)i) : 1 ;
	}
	printf("\n");

	free(arr4);
}
