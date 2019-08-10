#include <stdio.h>

int main()
{
	// String as char array in hex format
	char str[]={0x22,0x48,0x65,0x6C,0x6C,0x6F,0x20,0x57,0x6F,0x72,0x6C,0x64,0x21,0x22,0x0};

	printf("%s\n",str);
}


/* verify char to hex conversion from ascii table */
/*
int main()
{
	char str[] = "\"Hello World!\"";
	int i;

	for (i=0;i<sizeof(str);i++)
	{
		printf("%02X ",str[i]);
	}
	printf("\n");
}
*/
