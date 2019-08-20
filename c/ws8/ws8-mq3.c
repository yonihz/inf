#include <stdio.h>

int main()
{
	union numbers
	{
		int i;
		float f;
		double d;
	} num1;

	struct X
	{
		int i;
		char c;
		double d;
		short s;
	} X1;

	struct card
	{
		unsigned int suit : 2;
		unsigned int face_value : 4;
	} card1;

	printf("sizeof(union numbers): %lu\nsizeof(struct X): %lu\nsizeof(struct card): %lu\n", sizeof(num1), sizeof(X1), sizeof(card1));

	return (0);
}	
