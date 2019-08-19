#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#ifndef __POLY_H__
#define __POLY_H__

/* enum definition */

enum data_type { TYPE_UNDEFINED, TYPE_INT, TYPE_FLT, TYPE_STR };

typedef enum data_type data_type_t;

/* struct definition */

typedef union value_union
{
	int n;
	float f;
	char* str;
} value_t;

typedef struct data_struct
{
	data_type_t dt;
	value_t value;
} data_t;

/* function signatures */

extern void PolySetValue(data_t* arr_elem, data_type_t input_data_type, void* input_data);

extern void PolyPrintSingle(data_t* arr_elem);

extern void PolyAdd(data_t* arr_elem, int num);

extern void PolyCleanSingle(data_t* arr_elem);

extern void PolyPrintAll(data_t* arr, size_t size);

extern void PolyCleanAll(data_t* arr, size_t size);

extern data_type_t PolyGetType(data_t* arr_elem);

#endif
