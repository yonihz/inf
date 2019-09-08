#ifndef _VERIFY_FUNCS_H_
#define _VERIFY_FUNCS_H_

void VerifyInt(int test, int expected, char test_name[]);

void VerifySizet(size_t test,size_t expected, char test_name[]);

void VerifyVoidptr(void* test, void* expected, char test_name[]);

void VerifyChar(char test[], char expected[], char test_name[]);

#endif
