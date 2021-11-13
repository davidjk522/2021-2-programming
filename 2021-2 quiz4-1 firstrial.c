#include <stdio.h>
#include <stdlib.h>

void addcount(double x, double y);
void subcount(double x, double y);

int main()
{
	char input[100] = " "; //여유롭게 100칸
	char operatior[2] = { '+', '-' }; // 연산자들
	char number1[50], number2[50];
	int opposition = 0;
	double x = 0, y = 0;

	printf("Enter \"end\" to end the program \n\n");

	while (1) // 계속 반복
	{
		printf("Enter arithematic expressions, including numbers and operators: ");
		scanf_s("%s", input, 100);

		for (int i = 0; i < 100; i++)
		{

			if (input[i] == '+')
			{
				opposition = i;
			}

			else if (input[i] == '-')
			{
				opposition = i;
			}

		}//+-검사하는 for문 끝

		for (int i = 0; i < opposition; i++)
		{
			number1[i] = input[i];
		}
		for (int i = 0; i < 50; i++)
		{
			number2[i] = input[i + opposition + 1];

		}
		x = atof(number1);
		y = atof(number2);

		if (input[opposition] == '+')
		{
			addcount(x, y);

		}

		else if (input[opposition] == '-')
		{
			subcount(x, y);
		}

		else if (input == "end") // end 넣으면 프로그램 끝내기
		{
			printf("program ended ");
			break;
		}
		else
		{
			printf("Not supported operation!\n");
		}
	}// while(1) 종료
	return 0;
}// int main 끝

void addcount(double x, double y)
{
	double z = x + y;
	static int addcount = 0;

	addcount++;
	printf("The addition was performed a total of %d times\n", addcount);
	printf("The result of the operation is: %.3lf \n", z);
}//더하기 개수 세기

void subcount(double x, double y)
{
	double z = x - y;
	static int subcount = 0;

	subcount++;
	printf("The subtraction was performed a total of %d times\n", subcount);
	printf("The result of the operation is: %.3lf\n", z);
}//뺴기 세기