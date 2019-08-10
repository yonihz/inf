#include <stdio.h>

int main()
{
	printf("1)  sizeof signed char = %lu\n",sizeof(signed char));
	printf("2)  sizeof unsigned char = %lu\n",sizeof(unsigned char));
	printf("3)  sizeof short int = %lu\n",sizeof(short int));
	printf("4)  sizeof unsigned short int = %lu\n",sizeof(unsigned short int));
	printf("5)  sizeof int = %lu\n",sizeof(int));
	printf("6)  sizeof unsigned int = %lu\n",sizeof(unsigned int));
	printf("7)  sizeof long int = %lu\n",sizeof(long int));
	printf("8)  sizeof unsigned long int = %lu\n",sizeof(unsigned long int));
	/*
	printf("9)  sizeof long long int = %lu\n",sizeof(long long int));
	printf("10) sizeof unsigned long long int = %lu\n",sizeof(unsigned long long int));
	*/
	printf("11) sizeof float = %lu\n",sizeof(float));
	printf("12) sizeof double = %lu\n",sizeof(double));
	printf("13) sizeof long double = %lu\n",sizeof(long double));


	return (0);
}
