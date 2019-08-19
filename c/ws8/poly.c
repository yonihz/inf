#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "poly.h"

void PolySetValue(data_t* arr_elem, data_type_t input_data_type, void* input_data)
{
	(*arr_elem).dt = input_data_type;

	switch (input_data_type)
	{
		case TYPE_INT:
		{
			(*arr_elem).value.n = *((int*)input_data);
			break;
		}
		case TYPE_FLT:
		{
			(*arr_elem).value.f = *((float*)input_data);
			break;
		}
		case TYPE_STR:
		{
			(*arr_elem).value.str = malloc(strlen((char*)input_data) + 1);
			strcpy((*arr_elem).value.str, (char*)input_data);
			break;
		}
		case TYPE_UNDEFINED:
		{
			printf("Undefined object\n");
			break;
		}
		default:
		{
			printf("Undefined object\n");
			break;
		}
	}
}

void PolyAdd(data_t* arr_elem, int num)
{
	switch ((*arr_elem).dt)
	{
		case TYPE_INT:
		{
			(*arr_elem).value.n += 10;
			break;
		}
		case TYPE_FLT:
		{
			(*arr_elem).value.f += 10;
			break;
		}
		case TYPE_STR:
		{
			int len_curr = strlen((*arr_elem).value.str);
			char* temp_ptr = 0;
			char* str_num = 0;
			int temp_num = num;
			int len_num = 0;

			while(temp_num != 0)
			{
			    temp_num /= 10;
    			len_num++;
  			}				

			str_num = malloc(len_num + 1);

			sprintf(str_num, "%d", num);

			temp_ptr = realloc((*arr_elem).value.str, len_num + len_curr + 1);		
			(*arr_elem).value.str = temp_ptr;
			strcpy((*arr_elem).value.str + len_curr, str_num);
			free(str_num);
			break;
		}
		case TYPE_UNDEFINED:
		{
			printf("Undefined object\n");
			break;
		}
		default:
		{
			printf("Undefined object\n");
			break;
		}
	} 
}

void PolyPrintSingle(data_t* arr_elem)
{
	switch ((*arr_elem).dt)
	{
		case TYPE_INT:
		{
			printf("Object = %d (int)\n", (*arr_elem).value.n);
			break;
		}
		case TYPE_FLT:
		{
			printf("Object = %f (float)\n", (*arr_elem).value.f);
			break;
		}
		case TYPE_STR:
		{
			printf("Object = %s (string)\n", (*arr_elem).value.str);
			break;
		}
		case TYPE_UNDEFINED:
		{
			printf("Undefined object\n");
			break;
		}
		default:
		{
			printf("Undefined object\n");
			break;
		}
	} 
}

void PolyPrintAll(data_t* arr, size_t size)
{
	size_t i = 0;

	for (i = 0; i < size; i++)
	{
		PolyPrintSingle(arr+i);
	}
}

void PolyCleanSingle(data_t* arr_elem)
{
	if (TYPE_STR == (*arr_elem).dt)
	{
		free((*arr_elem).value.str);
	}
}

void PolyCleanAll(data_t* arr, size_t size)
{
	size_t i = 0;

	for (i = 0; i < size; i++)
	{
		PolyCleanSingle(arr+i);
	}
}

data_type_t PolyGetType(data_t* arr_elem)
{
	switch ((*arr_elem).dt)
	{
		case TYPE_INT:
		{
			printf("Object is int\n");
			break;
		}
		case TYPE_FLT:
		{
			printf("Object is float\n");
			break;
		}
		case TYPE_STR:
		{
			printf("Object is string\n");
			break;
		}
		case TYPE_UNDEFINED:
		{
			printf("Undefined object\n");
			break;
		}
		default:
		{
			printf("Undefined object\n");
			break;
		}
	}
	return ((*arr_elem).dt);
}
