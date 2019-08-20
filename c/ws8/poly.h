#ifndef __POLY_H__
#define __POLY_H__

/* enum definition */

typedef enum { TYPE_UNDEFINED, TYPE_INT, TYPE_FLT, TYPE_STR } data_type_t;

/* struct definition */

typedef union
{
	int n;
	float f;
	char* str;
} value_t;

typedef struct
{
	data_type_t dt;
	value_t value;
} data_t;

/* function signatures */

/* PolySetValue - set value to array element according to data type */

extern void PolySetValue(data_t* arr_elem, data_type_t input_data_type, void* input_data);

/* PolyPrintSingle - print value of array element */

extern void PolyPrintSingle(data_t* arr_elem);

/* PolyAdd - add an int to array element. concat if string */

extern void PolyAdd(data_t* arr_elem, int num);

/* PolyCleanSingle - change data type to undefined and if element is string free its malloc */

extern void PolyCleanSingle(data_t* arr_elem);

/* PolyPrintAll - print all array elements values */

extern void PolyPrintAll(data_t* arr, size_t size);

/* PolyCleanAll - change data type of all array element to undefined and if an element is a string free its malloc */

extern void PolyCleanAll(data_t* arr, size_t size);

/* PolyGetType - return data type of element */

extern data_type_t PolyGetType(data_t* arr_elem);

#endif
