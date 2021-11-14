#include <stdio.h>
void count();
int sum(int n)
{
	int result = 0; //sum(n)의 값
	
	if (n == 1)
	{
		result = 1;
		
	}
	else
	{
		result = (n + sum(n-1) );
		
	}
	count;

	return result;
	

}
void count()
{
	static int used_count = 0;
	used_count++;
}

int main()
{
	int n = 0;
	while (1) //양의 n을 입력하도록 반복
	{
		printf("양의 정수 n을 입력하세요: ");
		scanf_s("%d", &n);

		if ( (n > 0) && (sizeof(n) == 4) )
		{
			break;
		}
		else
		{
			printf("잘못된 입력입니다. 다시 입력하세요. \n");
		}

	}
	printf("sum(n) = %d\n", sum(n));
	



} // int main()의 끝

