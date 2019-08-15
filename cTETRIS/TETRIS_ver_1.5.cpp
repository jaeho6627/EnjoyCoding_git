#include <stdio.h>
#include <time.h>
#include <conio.h>
#include <stdlib.h>
#include <Windows.h>

//메크로 함수
#define SETRAND() srand((unsigned int)time(NULL))
#define RAND(n) rand()%(n)
#define DELAY(n) Sleep(n)
#define CLEANING() system("cls")

//데이터 리스트

//상수값

	//게임 초기 UI 위치
#define PRINTLINEX  30
#define PRINTLINEY  10
//게임정보 UI 위치
#define INFODATAPRINTX 35
#define INFODATAPRINTY 5

//게임 필드 크기
#define FEELDW 10//필드넓이
#define FEELDH 20//필드높이

//게임UI위치
#define FX 5
#define FY 1
//키보드 입력 값
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80

//자료형

	//사용자의 게임정보
typedef struct player {
	unsigned int score = 0;
	unsigned int X = FX + 1;
	unsigned int Y = FY-1;
	int NextBlock = rand() % 7;
	int NowBlock = NextBlock;
	int BlockLot = 0;
}PLAYER;

//마우스 커서
typedef enum { NOCURSOR, SOLIDCURSOR, NORMALCURSOR } CURSOR_TYPE;

//게임 구조물
enum { EMPTY, BRICK, WALL };
const char* arTile[] = { ", ", "■", "□" };

//전역 변수

	//블록 데이터
int blocks[7][4][4][4] = {
	//네모
	{{1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0},{1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0},
	 {1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0},{1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0}},
	 //막대기
	{{1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0},{1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0},
	 {1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0},{1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0}},
	 //ㄹ막대기
	{{1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0},{0,1,0,0,1,1,0,0,1,0,0,0,0,0,0,0},
	 {1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0},{0,1,0,0,1,1,0,0,1,0,0,0,0,0,0,0}},
	 //ㄹ뒤집은 막대기
	{{0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0},{1,0,0,0,1,1,0,0,0,1,0,0,0,0,0,0},
	 {0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0},{1,0,0,0,1,1,0,0,0,1,0,0,0,0,0,0}},
	 //ㄴ막대기
	{{1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0},{0,1,0,0,0,1,0,0,1,1,0,0,0,0,0,0},
	 {1,1,1,0,0,0,1,0,0,0,0,0,0,0,0,0},{1,1,0,0,1,0,0,0,1,0,0,0,0,0,0,0}},
	 //ㄴ뒤집은 막대기
	{{0,0,1,0,1,1,1,0,0,0,0,0,0,0,0,0},{1,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0},
	 {1,1,1,0,1,0,0,0,0,0,0,0,0,0,0,0},{1,0,0,0,1,0,0,0,1,1,0,0,0,0,0,0}},
	 //T 자 막대
	{{0,1,0,0,1,1,1,0,0,0,0,0,0,0,0,0},{0,1,0,0,1,1,0,0,0,1,0,0,0,0,0,0},
	 {1,1,1,0,0,1,0,0,0,0,0,0,0,0,0,0},{1,0,0,0,1,1,0,0,1,0,0,0,0,0,0,0}}
};

//화면에 띄울 벽
int Wall[FEELDH + 2][FEELDW + 2];

//플레이 보드
int Board[FEELDH][FEELDW];
//함수 리스트

	//처리 함수

		//좌표이동
void gotoxy(int x, int y);
//커서타입 변경
void SetCurSorType(CURSOR_TYPE c);
//커서 위치 충돌 검사
int CrushButtomBlock(PLAYER* USER);
//바닥 충돌 검사
int CrushButtom(PLAYER* USER);
//키보드 입력을 처리하는 함수
void KeYProcess(PLAYER* USER);
//줄확인하는 함수
int CHECKLINE(PLAYER * USER);
//게임 종료 조건 검사하는 함수
int GAMEOVER(PLAYER* USER);
//게임 동작 제어
void GAMEMANIGER();
//xor연산으로 블록을 보드에 저장하는 함수
void ORBlockB(PLAYER* USER);
//보드에 저장된 블록을 지우는 함수
void DELBLOCKXOR(PLAYER* USER);
//새로운 블록을 가져옴
void NEWBLOCKS(PLAYER* USER);
//전달되는 인자값의 위치로 임시로 이동해 충돌 검사를 실시
int CHECKAND(PLAYER* USER, int _x, int _y);
//새로운 블록과 현재 블록을 교환하는 함수
void ChangeBlocks(PLAYER* USER);
//해당 좌표 값의 위치에서 충돌이 있는지 확인
int CheckCrush(PLAYER* USER);
//제일 오른쪽 블록위치
int FirstRight(PLAYER* USER);
//바닥위치 검사
int FirstButtom(PLAYER* USER);


//출력 함수

	//선택된 블럭을 출력
void PrintBlock(PLAYER* USER);
//벽 정보 출력
void PRINTWALL();
//보드 정보 출력
void PRINTBOARD();
//플레이어 정보 출력
void PlayerInfo(PLAYER* user);
//게임 시작 화면 출력
int GAMESTART(void);

//저장 함수

	//벽 정보 저장
void SETWALL();
//보드 정보 저장
void SETBOARD();

//실행
int main(void) {

	CLEANING();
	SetCurSorType(NOCURSOR);
	SETRAND();

	SETWALL();
	PRINTWALL();
	SETBOARD();

	GAMEMANIGER();
	return 0;
}
/*
보드에 이전 블록을 지우는 방법 : xor 연산
보드에 블록을 출력하는 방법 : or 연산
보드에 출력된 블록과 출력해야하는 블록이 충돌하는지 확인하는 방법 : AND
*/
/*
블록을 출력할 배열의 위치에서 AND 연산으로 1인 부분이 없다면 저장하고
있다면 기본 위치로 이동해서 다른 블록을 받아오고 다시 y좌표를 증가시키면서 지우고 출력하는 것을 반복한다.
*/
/*
오른쪽 벽 충돌 검사 방법
: 출력해야하는 블록의 가장 오른쪽 블록의 위치가 배열의 넓이 값의 -1과 같은 경우 (또는 해당 블록의 오른쪽에 블록이 있는 경우) 오른쪽으로 블록을 이동시킬 수 없다
왼쪽 벽 충돌 검사 방법
: 출력해야하는 블록의 가장 왼쪽 블록의 위치가 0과 같은 경우 (또는 해당 블록의 왼쪽에 블록이 있는 경우) 왼쪽으로 이동시킬 수 없다
바닥 충돌 검사
: 출력해야하는 블록의 가장 아랫 블록의 좌표 위치가 보드 높이 -1인 경우 (또는 아랫 위치에 블록이 있는 경우) 더이상 아래로 내려갈 수 없음으로 이전 위치에 블록을 다시 저장하고
새로운 블록을 받아와서 게임을 계속 진행 한다.
*/

//게임 동작 제어
void GAMEMANIGER() {
	PLAYER USER;
	int gameover = 0;
	USER.NextBlock = RAND(7);
	PlayerInfo(&USER);
	while (1) {
		USER.X = FX / 2 + 1;
		USER.Y = FY-1;
		USER.BlockLot = 0;
		PlayerInfo(&USER);
		while (2) {
			if (CheckCrush(&USER)) {
				gameover++;
				break;
			}
			
			ORBlockB(&USER);
			PRINTBOARD();
			DELBLOCKXOR(&USER);

			/*게임 종료 조건*/
			
			if (CHECKLINE(&USER)) {
				PlayerInfo(&USER);
			}
				

			if (CrushButtom(&USER) || CrushButtomBlock(&USER)) {
				ORBlockB(&USER);

				//새로운 블록을 받아온다 
				NEWBLOCKS(&USER);

				break; //탈출
			}

			if (kbhit()) {
				KeYProcess(&USER);
				ORBlockB(&USER);
				PRINTBOARD();
				DELBLOCKXOR(&USER);
			}

			if (!CHECKAND(&USER, 0, 1)/*임시 이동 후 충돌 검사(AND연산으로)*/) {
				//문제가 없다면
				USER.Y++;
			}

			DELAY(1000 / 2);
		}
		if (gameover == 1)
			break;
	}
	CLEANING();
	gotoxy(10, 5);
	puts("G.A.M.E_O.V.E.R_");
	gotoxy(10, 6);
	printf("YOUR SCORE : %d", USER.score);
	DELAY(5000);
}
//바닥위치 검사
int FirstButtom(PLAYER* USER) {
	int x, y;
	for (y = 3; y > 0; y--) {
		for (x = 0; x < 4; x++) {
			if (blocks[USER->NowBlock][USER->BlockLot][y][x] == BRICK) {
				return y;
			}
		}
	}
	return 0;
}

//제일 오른쪽 블록위치
int FirstRight(PLAYER * USER) {
	int x, y;
	for (x = 3; x > 0; x--) {
		for (y = 0; y < 4; y++) {
			if (blocks[USER->NowBlock][USER->BlockLot][y][x] == BRICK)
				return x;
		}
	}
	return 0;
}

//해당 좌표 값의 위치에서 충돌이 있는지 확인
int CheckCrush(PLAYER* USER) {
	int x, y;
	for (y = 0; y < 4; y++) {
		for (x = 0; x < 4; x++) {
			if (Board[USER->Y + y][USER->X + x] && blocks[USER->NowBlock][USER->BlockLot][y][x])
				return 1;
		}
	}
	return 0;
}

//새로운 블록과 현재 블록을 교환하는 함수
void ChangeBlocks(PLAYER* USER) {
	int temp;
	temp = USER->NowBlock;
	USER->NowBlock = USER->NextBlock;
	USER->NextBlock = temp;
}

//새로운 블록을 가져옴
void NEWBLOCKS(PLAYER* USER) {
	USER->NowBlock = USER->NextBlock;
	USER->NextBlock = RAND(7);
}

//전달 받은 좌표값을 기준으로 입시로 이동해서 AND로 충돌 검사를 한다 //좌우 벽을 통과하지 못하도록 수정 필요
int CHECKAND(PLAYER* USER, int _x, int _y) {
	int x, y;
	for (y = 0; y < 4; y++) {
		for (x = 0; x < 4; x++) {
			if (Board[USER->Y + y + _y][USER->X + x + _x] && blocks[USER->NowBlock][USER->BlockLot][y][x]) {
					return 1;
			}
		}
	}
	return 0;
}
//키보드 입력을 처리하는 함수
void KeYProcess(PLAYER* USER) {
	int x, y;
	int getkey;
	while (1) {
		getkey = getch();
		if (getkey == 0xE0 || getkey == 0) {
			getkey = getch();
			if (getkey == LEFT) {
				if (USER->X == 0)
					return;
				if (!CHECKAND(USER, -1, 0)/*임시 이동 후 충돌 검사(AND연산으로)*/) {
					//문제가 없다면
					USER->X--;
					break;
				}
			}
			else if (getkey == RIGHT) {
				if (USER->X == FEELDW - 1 || USER->X + FirstRight(USER) == FEELDW - 1)
					return;
				if (!CHECKAND(USER, 1, 0)/*임시 이동 후 충돌 검사(AND연산으로)*/) {
					//문제가 없다면
					USER->X++;
					break;
				}
			}
			else if (getkey == UP) {
				//다음 블록과 현재 블록을 교체
				//ChangeBlocks(USER);
				//블록을 회전
				if (USER->BlockLot == 3) {
					USER->BlockLot = 0;
				}
				else {
					USER->BlockLot++;
				}
				if (CheckCrush(USER)) {
					//문제가 있다면 원상 복구
					//ChangeBlocks(USER);
					if (USER->BlockLot == 0) {
						USER->BlockLot = 3;
					}
					else {
						USER->BlockLot--;
					}
				}
				break;
			}
			else if (getkey == DOWN) {
				if (USER->Y + FirstButtom(USER) > FEELDH - 3) {
					return;
				}
				if (!CHECKAND(USER, 0, 1)/*임시 이동 후 충돌 검사(AND연산으로)*/) {
					//문제가 없다면
					USER->Y++;
					break;
				}
			}
			//else if (/*스페이스바*/) {
			//	//		if (/*AND검사로 바닥부터 올라 가면서 결과 값이 모두 0이 장소 확인*/) {
			//	//			//해당 위치에 블록 값을 보드에 저장
			//	//		}
			//}
		}
	}
}

//이전 블록을 지우는 함수 //
void DELBLOCKXOR(PLAYER* USER) {
	int x, y;
	for (y = 0; y < 4; y++) {
		for (x = 0; x < 4; x++) {
			Board[USER->Y + y][USER->X + x] = Board[USER->Y + y][USER->X + x] ^ blocks[USER->NowBlock][USER->BlockLot][y][x];
		}
	}
}

//xor연산으로 블록을 보드에 저장하는 함수 ( 오른쪽 벽에 닿을 때 값의 저장을 한줄씩 줄려서 저장한다)
void ORBlockB(PLAYER* USER) {
	int x, y;
	
	for (y = 0; y < 4; y++) {
		for (x = 0; x < 4; x++) {
			Board[USER->Y + y][USER->X + x] = Board[USER->Y + y][USER->X + x] | blocks[USER->NowBlock][USER->BlockLot][y][x];
		}
	}
}


void gotoxy(int x, int y) {
	COORD Cur;
	Cur.X = x;
	Cur.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}

void SetCurSorType(CURSOR_TYPE c) {
	CONSOLE_CURSOR_INFO CURINFO;

	switch (c) {
	case NOCURSOR:
		CURINFO.bVisible = FALSE;
		CURINFO.dwSize = 1;
		break;
	case SOLIDCURSOR:
		CURINFO.bVisible = TRUE;
		CURINFO.dwSize = 100;
		break;
	case NORMALCURSOR:
		CURINFO.bVisible = TRUE;
		CURINFO.dwSize = 20;
		break;
	}
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CURINFO);
}

//커서 위치 블록 충돌 검사
int CrushButtomBlock(PLAYER* USER) {
	int x, y;

	for (y = 0; y < 4; y++) {
		for (x = 0; x < 4; x++) {
			if (Board[USER->Y + 1 + y][USER->X + x] && blocks[USER->NowBlock][USER->BlockLot][y][x]) {
				return 1;
			}
		}
	}
	return 0;
}

//바닥 충돌 검사
int CrushButtom(PLAYER* USER) {
	int x, y;
	if (USER->Y + 3 == FEELDH - 1) {
		y = 3;
		for (x = 0; x < 4; x++) {
			if (blocks[USER->NowBlock][USER->BlockLot][y][x] == BRICK)
				return 1;
		}
	}
	else if (USER->Y + 2 == FEELDH - 1) {
		y = 2;
		for (x = 0; x < 4; x++) {
			if (blocks[USER->NowBlock][USER->BlockLot][y][x] == BRICK)
				return 1;
		}
	}
	else if (USER->Y + 1 == FEELDH - 1) {
		y = 1;
		for (x = 0; x < 4; x++) {
			if (blocks[USER->NowBlock][USER->BlockLot][y][x] == BRICK)
				return 1;
		}
	}
	else if (USER->Y == FEELDH - 1) {
		y = 0;
		for (x = 0; x < 4; x++) {
			if (blocks[USER->NowBlock][USER->BlockLot][y][x] == BRICK)
				return 1;
		}
	}
	return 0;
}



//줄확인하는 함수
 int CHECKLINE(PLAYER * USER) {
	
	int nFraim, nStay;
	int checkX;
	int count = 0;
	nFraim = FEELDH - 1;
	for (; nFraim > 0; nFraim--) {
		for (checkX = 0; checkX < FEELDW; checkX++) {
			if (Board[nFraim][checkX] == 0) {
				count = 0;
				break;
			}
			count++;
		}
		if (count == FEELDW) {

			for (checkX = 0; checkX < FEELDW; checkX++) {
				Board[nFraim][checkX] = EMPTY;
			}

			for (checkX = 0; checkX < FEELDW; checkX++) {
				for (nStay = nFraim; nStay > 0; nStay--) {
					if (nStay == 0) {
						Board[nStay][checkX] = EMPTY;
						break;
					}
					Board[nStay][checkX] = Board[nStay - 1][checkX];
				}
			}
			USER->score++;
			return 1;
		}
	}
	return 0;
}

//게임 종료 조건 검사하는 함수
int GAMEOVER(PLAYER* USER) {
	
	return 0;
}

//저장 함수

	//벽 정보 저장
void SETWALL() {
	int x, y;
	for (y = 0; y < FEELDH + 2; y++) {
		for (x = 0; x < FEELDW + 2; x++) {
			if (y == 0 || y == FEELDH + 1 || x == 0 || x == FEELDW + 1) {
				Wall[y][x] = WALL;
			}
		}
	}
}

//보드 정보 저장
void SETBOARD() {
	int x, y;
	for (y = 0; y < FEELDH; y++) {
		for (x = 0; x < FEELDW; x++) {
			Board[y][x] = EMPTY;
		}
	}
}

//출력함수

	//선택된 블럭을 출력
void PrintBlock(PLAYER* USER) {
	int x, y;
	if (USER->Y == (FEELDH - 1) - 2) {
		for (y = 0; y < 3; y++) {
			for (x = 0; x < 4; x++) {
				gotoxy(USER->X * 2 + 1 + (x + 1) * 2, USER->Y + (y + 1));
				puts(arTile[blocks[USER->NowBlock][USER->BlockLot][y][x]]);
			}
		}
	}
	else if (USER->Y == (FEELDH - 1) - 1) {
		for (y = 0; y < 2; y++) {
			for (x = 0; x < 4; x++) {
				gotoxy(USER->X * 2 + 1 + (x + 1) * 2, USER->Y + (y + 1));
				puts(arTile[blocks[USER->NowBlock][USER->BlockLot][y][x]]);
			}
		}
	}
	else if (USER->Y == FEELDH - 1) {
		for (y = 0; y < 1; y++) {
			for (x = 0; x < 4; x++) {
				gotoxy(USER->X * 2 + 1 + (x + 1) * 2, USER->Y + (y + 1));
				puts(arTile[blocks[USER->NowBlock][USER->BlockLot][y][x]]);
			}
		}
	}
	else {
		for (y = 0; y < 4; y++) {
			for (x = 0; x < 4; x++) {
				gotoxy(USER->X * 2 + 1 + (x + 1) * 2, USER->Y + (y + 1));
				puts(arTile[blocks[USER->NowBlock][USER->BlockLot][y][x]]);
			}
		}
	}


}

//벽 정보 출력
void PRINTWALL() {
	int x, y;
	for (y = 0; y < FEELDH + 2; y++) {
		for (x = 0; x < FEELDW + 2; x++) {
			gotoxy(FX + x * 2, FY + y);
			puts(arTile[Wall[y][x]]);
		}
	}
}

//보드 정보 출력
void PRINTBOARD() {
	int x, y;
	for (y = 0; y < FEELDH; y++) {
		for (x = 0; x < FEELDW; x++) {
			gotoxy(FX + (x + 1) * 2, FY + (y + 1));
			puts(arTile[Board[y][x]]);
		}
	}

}

//플레이어 정보 출력
void PlayerInfo(PLAYER* user) {
	int x, y;
	gotoxy(INFODATAPRINTX, INFODATAPRINTY);
	printf("점수 : %d", user->score);
	gotoxy(INFODATAPRINTX, INFODATAPRINTY + 2);
	puts("- 다음블록 -");
	for (y = 0; y < 4; y++) {
		for (x = 0; x < 4; x++) {
			gotoxy(INFODATAPRINTX+x*2, INFODATAPRINTY + 2 + (y+1));
			puts(arTile[blocks[user->NextBlock][0][y][x]]);
		}
	}
}

//게임 시작 화면 출력
int GAMESTART(void) {
	int choise;
	gotoxy(PRINTLINEX, PRINTLINEY);
	printf("-------------------------------------------------------------");
	gotoxy(PRINTLINEX, PRINTLINEY + 1);
	printf("| @ 전통 테트리스 게임 @					  |");
	gotoxy(PRINTLINEX, PRINTLINEY + 2);
	printf("| <게임방법>					          |");
	gotoxy(PRINTLINEX, PRINTLINEY + 3);
	printf("| 방향키로 내려 오는 블록을 쌓아 맞추면 됩니다.		  |");
	gotoxy(PRINTLINEX, PRINTLINEY + 4);
	printf("| '←', '→'키로 블록을 움직일 수 있습니다.		  |");
	gotoxy(PRINTLINEX, PRINTLINEY + 5);
	printf("| 스페이스키로 블록을 회전 시킬 수 있습니다.		  |");
	gotoxy(PRINTLINEX, PRINTLINEY + 6);
	printf("| '↑'키로 다음에 나올 블록과 교환할 수 있습니다.           |");
	gotoxy(PRINTLINEX, PRINTLINEY + 7);
	printf("| '↓'키로 블록을 바로 내려 놓을 수 있습니다.	          |");
	gotoxy(PRINTLINEX, PRINTLINEY + 8);
	printf("-------------------------------------------------------------");
	gotoxy(PRINTLINEX, PRINTLINEY + 9);
	printf("1. 게임 시작 2. 종료");
	gotoxy(PRINTLINEX, PRINTLINEY + 10);
	printf("선택: ");
	scanf("%d", &choise);
	if (choise == 2) {
		CLEANING();
		return -1;
	}
	else {
		CLEANING();
		return 1;
	}
}