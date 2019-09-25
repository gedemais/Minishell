#include <stdio.h>

static inline void	print(void)
{
	static int value = 0;

	printf("value = %d\n", value);
	value = 2;
}


int main(void)
{
	print();
	print();

	return (0);
}
