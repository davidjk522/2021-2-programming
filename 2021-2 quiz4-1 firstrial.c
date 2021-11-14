#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void addcount(double x, double y); //더하기 개수 세기
void subcount(double x, double y); //뺴기 개수 세기

int main()
{
	char input[100] = " "; //여유롭게 100칸에 식을 받음

	

	printf("Enter \"end\" to end the program \n\n");

	while (1) // end 입력하기 전까지 계속 반복
	{
		char number1[50] = { ' ' }, number2[50] = { ' ', }; //문자열로 입력 받은 식의 숫자들 추출하기
		for (int i = 0; i < 50; i++)
		{
			number1[i] = ' ';
			number2[i] = ' ';
		}// 초기화 warning 피하기
		int operator = 0; // 계산에 사용될 연산자의 위치(부호 아님)
		double x = 0, y = 0; //atof 함수 이용해서 실수로 바꾼 값을 저장하기 위한 변시
		printf("Enter arithematic expressions, including numbers and operators: ");
		scanf_s("%s", input, 100);

		if (strcmp(input, "end") == 0) // 문자열을 넣어서 strcmp==0 즉 end와 같으면 프로그램 종료 while(1) 문 break하기
		{
			break;
		}
		else { //end가 아닌 경우
			for (int i = 0; i < 100; i++)
			{

				if (input[i] == '+')
				{
					operator = i;
					break;
				}

				else if (input[i] == '-')
				{
					if (input[i] == input[i + 1])
					{
						operator = i;
						break;
					}
					else
					{
						operator = i;
					}
				}

			}//+-검사하는 for문 끝.. 처음에 -나+부호가 있더라도 중간에 있는 위치의 값으로 저장이 되어서 문제x

			for (int i = 0; i < operator; i++)
			{
				int temp;
				temp = input[i];
				number1[i] = temp;
			}

			for (int i = 0; i < 50; i++)
			{
				int temp;
				temp = input[i + operator + 1];
				number2[i] = temp;

			}
			x = atof(number1); //double로 변환
			y = atof(number2); // double로 변환



			//더하기 뺴기, 지원하지 않은 연산 표시
			if (input[operator] == '+')
			{
				addcount(x, y);

			}

			else if (input[operator] == '-')
			{
				subcount(x, y);
			}

			else
			{
				printf("Not supported operation!\n");
			}
			
		}// else, break에 해당하는 for 문

	}// while() 종료
	printf("프로그램 종료");
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