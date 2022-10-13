#include <stdio.h>

const float a = 2;

int func(int a, int b, int c)
{
	return (a) + (b) + (c);
}

int main()
{
	int b[2];
	printf("Please enter 2 inputs:\n");
	scanf("%d", &b[0]);
	if (b[0] < 0)
	{
		return 0;
	}
	while (b[0] > 0)
	{
		b[0] = b[0] - 1;
	}
	b[1] = func(1, 2, 1);
	printf("%d\n", (int)a + b[0] + b[1]);
	return 0;
}