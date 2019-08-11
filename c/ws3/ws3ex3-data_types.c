#include <stdio.h>

int main()
{
	size_t us_char_max = (unsigned char)~0L;

	size_t s_char_max = us_char_max / 2;
	size_t s_char_min = - ( us_char_max / 2 ) - 1;

	size_t us_short_max = (unsigned short)~0L;

	size_t s_short_max = us_short_max / 2;
	size_t s_short_min = - ( us_short_max / 2 ) - 1;

	size_t us_int_max = (unsigned int)~0L;

	size_t s_int_max = us_int_max / 2;
	size_t s_int_min = - ( us_int_max / 2 ) - 1;

	size_t us_long_max = (unsigned long)~0L;

	size_t s_long_max = us_long_max / 2;
	size_t s_long_min = - ( us_long_max / 2 ) - 1;

	printf("signed char\n");
	printf("sizeof %lu\n",sizeof(signed char));
	printf("range %ld - %ld\n",s_char_min,s_char_max);
	printf("range hex %hx - %hx\n\n",s_char_min,s_char_max);

	printf("unsigned char\n");
	printf("sizeof %lu\n",sizeof(unsigned char));
	printf("range %ld - %ld\n",0,us_char_max);
	printf("range hex %hx - %hx\n\n",0,us_char_max);

	printf("short int\n");
	printf("sizeof %lu\n",sizeof(short int));
	printf("range %ld - %ld\n",s_short_min,s_short_max);
	printf("range hex %hx - %hx\n\n",s_short_min,s_short_max);

	printf("us short int\n");
	printf("sizeof %lu\n",sizeof(unsigned short int));
	printf("range %hd - %hd\n",0,us_short_max);
	printf("range hex %hx - %hx\n\n",0,us_short_max);

	printf("int\n");
	printf("sizeof %lu\n",sizeof(int));
	printf("range %ld - %ld\n",s_int_min,s_int_max);
	printf("range hex %x - %x\n\n",s_int_min,s_int_max);

	printf("us int\n");
	printf("sizeof %lu\n",sizeof(unsigned int));
	printf("range %ld - %ld\n",0,us_int_max);
	printf("range hex %x - %x\n\n",0,us_int_max);

	printf("long int\n");
	printf("sizeof %lu\n",sizeof(long int));
	printf("range %ld - %ld\n",s_long_min,s_long_max);
	printf("range hex %lx - %lx\n\n",s_long_min,s_long_max);

	printf("us long int\n");
	printf("sizeof %lu\n",sizeof(unsigned long int));
	printf("range %lu - %lu\n",0,us_long_max);
	printf("range hex %lx - %lx\n\n",0,us_long_max);

	printf("float\n");
	printf("sizeof %lu\n\n",sizeof(float));

	printf("double\n");
	printf("sizeof %lu\n\n",sizeof(double));

	printf("long double\n");
	printf("sizeof %lu\n\n",sizeof(long double));

	return (0);
}
