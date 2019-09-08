#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc */
#include <string.h> /* strlen */

void Print3Arr(char arr1[], char arr2[], char arr3[], char* arr_lut);

int main()
{
	/* common arr1 arr2: Q L M G F */
	char arr1[] = "A Q L M Y R G F";
	char arr2[] = "B L F M Q G J P";
	char arr3[] = "K Q X Z W L D I";
	char* arr_lut = malloc(256);
	char arr_lut_check[256];
	size_t i = 0;
	size_t len_lut = 256;
	int status = 0;

	for (i = 0; i < len_lut; i++)
	{
		arr_lut_check[i] = 0;
	}

	arr_lut_check['F'] = 2;
	arr_lut_check['G'] = 2;
	arr_lut_check['M'] = 2;
	

	printf("arr1: %s\narr2: %s\narr3: %s\n", arr1, arr2, arr3);

	Print3Arr(arr1, arr2, arr3, arr_lut);

	for (i = 0; i < len_lut; i++)
	{
		if (arr_lut_check[i] == 2)
		{
			if (arr_lut[i] != 2)
			{
				status = 1;
			}
		}
	}
	
	status ? printf("TEST FAIL\n") : printf("TEST PASS\n") ;

	return (0);
}

void Print3Arr(char arr1[], char arr2[], char arr3[], char* arr_lut)
{
	size_t i = 0;
	size_t len1 = 0;
	size_t len2 = 0;
	size_t len3 = 0;
	size_t len_lut = 256;

	for (i = 0; i < len_lut; i++)
	{
		arr_lut[i] = 0;
	}

	len1 = strlen(arr1);
	len2 = strlen(arr2);
	len3 = strlen(arr3);

	for (i = 0; i < len1; i++)
	{
		arr_lut[(size_t)arr1[i]] = 1;
	}

	for (i = 0; i < len2; i++)
	{
		arr_lut[(size_t)arr2[i]] = (arr_lut[(size_t)arr2[i]] + 2) / 3 * 2;
	}

	for (i = 0; i < len3; i++)
	{
		arr_lut[(size_t)arr3[i]] = (arr_lut[(size_t)arr3[i]]) * 0;
	}

	for (i = 0; i < len_lut; i++)
	{
		arr_lut[i] == 2 ? printf("%c ", (int)i) : 1 ;
	}
	printf("\n");
}
