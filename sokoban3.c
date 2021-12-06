#include <stdio.h>
#include <conio.h>
#include "cursor.h"

enum { ESC = 27, LEFT = 75, RIGHT = 77, UP = 72, DOWN = 80, r = 82 };
#define putchxy(x, y, c) {gotoxy(x, y);putch(c);}
#define putsxy(x, y, s) {gotoxy(x, y);puts(s);}

char arStage[][18][21] = {
	{
		"11111111111111111111",
		"11111111111111111111",
		"11111111111111111111",
		"11111000111111111111",
		"11111200111111111111",
		"11111002111111111111",
		"11100202011111111111",
		"11101011011111111111",
		"10001011011111003311",
		"10200200040000003311",
		"11111011101011003311",
		"11111000001111111111",
		"11111111111111111111",
		"11111111111111111111",
		"11111111111111111111",
		"11111111111111111111",
		"11111111111111111111",
		"11111111111111111111",
	},
	{
		"11111111111111111111",
		"11111111111111111111",
		"11111111111111111111",
		"11111111111111111111",
		"11113300100000111111",
		"11113300102002001111",
		"11113300121111001111",
		"11113300004011001111",
		"11113300101002011111",
		"11111111101120201111",
		"11111102002020201111",
		"11111100001000001111",
		"11111111111111111111",
		"11111111111111111111",
		"11111111111111111111",
		"11111111111111111111",
		"11111111111111111111",
		"11111111111111111111",
	},
	{
		"11111111111111111111",
		"11111111111111111111",
		"11111111111111111111",
		"11111111111111111111",
		"11111111110000041111",
		"11111111110212011111",
		"11111111110200211111",
		"11111111111202011111",
		"11111111110201011111",
		"11333300110200200111",
		"11133300002002000111",
		"11333300111111111111",
		"11111111111111111111",
		"11111111111111111111",
		"11111111111111111111",
		"11111111111111111111",
		"11111111111111111111",
		"11111111111111111111",
	},
};
char ns[18][21];
int nx, ny;
char* arTile[] = { "  ", "■", "⊙", "◇", "★" };
enum { EMPTY = 48, WALL, PACK, DEPOT, MAN };
int stage = 0;

int any_movement = 0;  //총 움직인 횟수 계산하기

int recordx = 0;
int recordy = 0;
int retry = 1; //재시도 횟수 한 번

int main()
{
	int ch;
	int x, y;
	int dx, dy;
	BOOL bEnd;
	

	showcursor(FALSE);

	clock_t start = clock(); // 시간 측정 시작

	// 전체 무한 루프
	for (;;)
	{

		// 게임판 초기화
		memcpy(ns, arStage[stage], sizeof(ns));
		for (y = 0; y < 18; y++) {
			for (x = 0; x < 20; x++) {
				// 주인공의 위치 찾아 놓는다.
				if (ns[y][x] == MAN) {
					nx = x;
					ny = y;
					ns[y][x] = EMPTY;
				}
			}
		}
		clrscr();
		putsxy(45, 2, "SOKOBAN");
		putsxy(45, 4, "ESC:종료");
		putsxy(45, 6, "1, 2, 3:스테이지 이동");
		putsxy(45, 8, "취소기능을 사용하려면 R을 누르세요(반드시 shift + r 로 입력!)");

		// 게임 진행 루프
		for (;;) {
			// 화면을 그린다.
			for (y = 0; y < 18; y++) {
				for (x = 0; x < 20; x++) {
					putsxy(x * 2, y, arTile[ns[y][x] - '0']);
				}
			}
			putsxy(nx * 2, ny, arTile[MAN - '0']);

			// 주인공 이동
			ch = getch();
			if (ch == 0xE0 || ch == 0) {
				ch = getch();
				dx = dy = 0;
				switch (ch) {
				case LEFT:
					dx = -1;
					recordx = dx;
					recordy = 0;
					break;
				case RIGHT:
					dx = 1;
					recordx = dx;
					recordy = 0;
					break;
				case UP:
					dy = -1;
					recordx = 0;
					recordy = dy;
					break;
				case DOWN:
					dy = 1;
					recordx = 0;
					recordy = dy;
					break;

				}

				// 벽이 아니어야 한다.
				if (ns[ny + dy][nx + dx] != WALL) {

					// 짐을 미는 경우
					if (ns[ny + dy][nx + dx] == PACK) {
						// 그 다음 칸이 비어 있거나 창고여야 한다. 
						if (ns[ny + dy * 2][nx + dx * 2] == EMPTY ||
							ns[ny + dy * 2][nx + dx * 2] == DEPOT) {
							if (arStage[stage][ny + dy][nx + dx] == DEPOT) {
								ns[ny + dy][nx + dx] = DEPOT;
							}
							else {
								ns[ny + dy][nx + dx] = EMPTY;
							}
							ns[ny + dy * 2][nx + dx * 2] = PACK;
							
						}
						else {
							dx = dy = 0;
						}

					}
					// 새 위치로 이동
					nx += dx;
					ny += dy;

					gotoxy(45, 12); //커서를 움직여 표시할 위치로 이동한다.
					printf("이동 횟수는: %d", ++any_movement); //움직인 횟수 나타낸다.

				}
				
				

				//재사용 기회 남았는지 없는지 알려줌
				
				if (retry == 1)
				{
					gotoxy(45, 16);
					printf("재사용 기회 1번 남음 ");
				}
				else
				{
					gotoxy(45, 16);
					printf("재사용 기회 다 사용함 ");
				}

			}


			else if ((ch == r) && (retry == 1))
			{
				retry = 0;
				if (ns[ny + recordy][nx + recordx] == PACK)
				{
					ns[ny][nx] = PACK;
					ns[ny + recordy][nx + recordx] = EMPTY;
				}

				if (ns[ny - recordy][nx - recordx] != WALL) {
					// 짐을 미는 경우
					if (ns[ny - recordy][nx - recordx] == PACK) {
						// 그 다음 칸이 비어 있거나 창고여야 한다. 
						if (ns[ny - recordy * 2][nx - recordx * 2] == EMPTY ||
							ns[ny - recordy * 2][nx - recordx * 2] == DEPOT) {
							if (arStage[stage][ny - recordy][nx - recordx] == DEPOT) {
								ns[ny - recordy][nx - recordx] = DEPOT;
							}
							else {
								ns[ny - recordy][nx - recordx] = EMPTY;
							}
							ns[ny - recordy * 2][nx - recordx * 2] = PACK;
							
						}
						else {
							recordx = recordy = 0;
						}
						
					}
					// 새 위치로 이동
					nx -= recordx;
					ny -= recordy;
					
					gotoxy(45, 12); //커서를 움직여 표시할 위치로 이동한다.
					printf("이동 횟수는: %d", --any_movement); //움직인 횟수 나타낸다. 여기는 한 번 수행 되고 나면 다시 수행이 안되므로 키보드가 계속 눌리는 걱정할 필요 없음

					gotoxy(45, 16);
					printf("재사용 기회 다 사용함 ");
				}

			}
			

			else
			{
					if (ch == ESC)
					{
						showcursor(TRUE);
						
						return;
					}

					if (ch == '1')
					{
						stage = 0;
						break;
					}

					if (ch == '2')
					{
						stage = 1;
						break;
					}

					if (ch == '3') 
					{
						stage = 2;
						break;
					}
			}
			clock_t end = clock();
			int diff = end - start;
			gotoxy(45, 18);
			printf("총 걸린 시간: %4.2f 초", (double) (diff) / CLOCKS_PER_SEC);
			
				// 게임 끝 처리
				bEnd = TRUE;
				for (y = 0; y < 18; y++) 
				{
					for (x = 0; x < 20; x++) 
					{
						if (ns[y][x] == DEPOT) 
						{
							bEnd = FALSE;
						}
					}
				}

				if (bEnd) 
				{
					clrscr();
					putsxy(10, 10, "참 잘했어요. 다음 스테이지로 이동합니다.");
					delay(2000);
					
					stage++;
					if (stage == 3) stage = 0;
					break;
				}
			}
		}
	}



