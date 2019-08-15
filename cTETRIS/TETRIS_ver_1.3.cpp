#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <conio.h>
#define SETRAND() srand((unsigned int)time(NULL))
#define RAND(n) rand()%(n)
#define DELAY(n) Sleep(n)
#define CLEANING() system("cls")

//좌표 이동 함수
void gotoxy(int x, int y) {
	COORD Cur;
	Cur.X = x;
	Cur.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}


//게임 데이터 정보 #################################################################################
//게임 시작 설명 위치 상수화
#define PRINTLINEX  30
#define PRINTLINEY  10

//게임 정보 출력위치 상수화(시간, 다음 블록, 점수)
#define INFODATAPRINTX 85
#define INFODATAPRINTY 0

#define FEELDW 10//필드넓이
#define FEELDH 20//필드높이

//게임 출력 기본 위치
#define FX 5
#define FY 1

//키보드 입력 값 상수화
#define LEFT 75

#define RIGHT 77

#define UP 72

#define DOWN 80


typedef struct player {
	unsigned int score = 0;
	unsigned int X=FX-1;
	unsigned int Y=FY-1;
}PLAYER;

//마우스 커서 타입
typedef enum { NOCURSOR, SOLIDCURSOR, NORMALCURSOR } CURSOR_TYPE;

//게임에 사용될 구조물 타일
enum { EMPTY, BRICK, WALL };
const char * arTile[] = { ", ", "■", "□" };

//화면에 띄울 벽
int Wall[FEELDH + 2][FEELDW + 2];

//플레이 보드
int Board[FEELDH][FEELDW];

//블록
int Brick[3][3] = { BRICK };

//#####################################################################################################

//저장 함수##############################################################################################
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

////블록 정보 저장
//void SETBRICK(PLAYER * USER) {
//	BOARDBRICK(USER);
//}


//########################################################################################################

//출력 함수###############################################################################################
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
			gotoxy(FX + (x+1) * 2, FY + (y+1));
			puts(arTile[Board[y][x]]);
		}
	}

}

//플레이어 정보 출력
void PlayerInfo(PLAYER * user) {
	gotoxy(INFODATAPRINTX, INFODATAPRINTY);
	printf("점수 : %d", user->score);
}

//게임 시작 화면 출력(게임 방법도 설명)
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

//########################################################################################################

//처리 함수###############################################################################################
//블록 정보 보드에 저장
//void BOARDBRICK(PLAYER * USER) {
//	Board[USER->Y][USER->X] = Brick[0][0];
//
//}

//커서의 x좌표 값을 받아온다
int whereX(void) {
	CONSOLE_SCREEN_BUFFER_INFO BUFINFO;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &BUFINFO);
	return BUFINFO.dwCursorPosition.X;
}
//커서의 y좌표 값을 받아온다
int whereY(void) {
	CONSOLE_SCREEN_BUFFER_INFO BUFINFO;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &BUFINFO);
	return BUFINFO.dwCursorPosition.Y;
}

//커서의 타입을 변경하는 함수 (커서가 안보이고 보이고 하는 것을 설정 할 수 있음)
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

//키 입력
int KBHIT(PLAYER * USER) {
	int getkye;
	if (_kbhit()) {
		getkye = _getch();

		if (getkye == 0xE0 || getkye == 0) {

			Board[USER->Y][USER->X] = EMPTY;

			getkye = _getch();
			switch (getkye) {
				//방향키 왼쪽
			case 75:
				
				if (USER->X > 0 && Board[USER->Y][USER->X-1] != BRICK) {
					USER->X -= 1;
				}

				break;
				//방향키 오른쪽
			case 77:

				if (USER->X < FEELDW-1 && Board[USER->Y][USER->X + 1] != BRICK) {
					USER->X += 1;
				}

				break;
				//방향키 아래쪽
			case 80:

				if (USER->Y > 0 && USER->Y < FEELDH-1 && Board[USER->Y+1][USER->X] != BRICK) {
					USER->Y += 1;
				}

				break;
				//방향키 윗쪽
			case 72:

				//블록 방향 바꾸는 함수

				break;
			}
			if (getkye == ' ') {

				//블록을 아래로 떨어 뜨리는 함수
				
			}
		}
		Board[USER->Y][USER->X] = BRICK;
		return 1;
	}
	return 0;
}

//줄 확인
int CHECKLINE(void) {
	int result=0;
	int nFraim, nStay;
	int checkX;
	int count = 0;
	nFraim = FEELDH-1;
	for (; nFraim > 0; nFraim--) {
		for (checkX = 0; checkX < FEELDW; checkX++) {
			if (Board[nFraim][checkX] == 0) {
				count = 0;
				break;
			}
			count++;
		}
		if (count == FEELDW) {
			result = 1;

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
			break;
		}
	}
	return result;
}
//게임 종료
int GAMEOVER() {
	int x=3, y=0;
	for (; x < 7; x++) {
		if (Board[y][x] == BRICK && Board[y+1][x] == BRICK)
			return 1;
	}
	return 0;
}

//게임 동작 제어
void GAMEMANIGER() {
	PLAYER USER;
	//int x, y;
	while (1) {
		//블록 배열에 블록 값을 저장

		Board[USER.Y - 1][USER.X] = EMPTY;
		Board[USER.Y][USER.X] = BRICK;
		
		PRINTBOARD();
		PlayerInfo(&USER);

		while (KBHIT(&USER)) PRINTBOARD();
		
		while (1) {
			if (CHECKLINE()) {
				USER.score++;
				PlayerInfo(&USER);
				PRINTBOARD();
			}

			if (USER.Y == FEELDH - 1 || Board[USER.Y + 1][USER.X] == BRICK) {
				USER.X = FX - 1;
				USER.Y = FY - 1;
				break;
			}
			
			if (USER.Y < FEELDH - 1 && Board[USER.Y + 1][USER.X] != BRICK) {
				USER.Y++;
				break;
			}
			
		}

		if (GAMEOVER()) break;

		DELAY(100 / 2);
	}
	CLEANING();
	gotoxy(10, 5);
	puts("G.A.M.E_O.V.E.R_");
	gotoxy(10, 6);
	printf("YOUR SCORE : %d", USER.score);
	DELAY(5000);
}


//########################################################################################################

int main(void) {
	if (GAMESTART() == 1) {
		CLEANING();
		SetCurSorType(NOCURSOR);

		SETWALL();
		PRINTWALL();
		SETBOARD();

		GAMEMANIGER();
	}
	else {
		printf("게임을 종료합니다.");
		DELAY(2000);
	}
	return 0;
}
