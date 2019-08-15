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
	unsigned int X = FX / 2 + 1;
	unsigned int Y = FY - 1;
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


int GAMESTART(void);//게임시작화면
void gotoxy(int x, int y);//좌표이동
void SetCurSorType(CURSOR_TYPE c);//커서 타입 변경
void SETWALL();//벽 정보 저장
void PRINTWALL();//벽 정보 출력
void SETBOARD();//보드 정보 저장
int GAMEOVER();//게임 종료
void PlayerInfo(PLAYER* user);//플레이어 정보 출력
int KBHIT(PLAYER * USER);//키 입력
void DELBLOCKXOR(PLAYER* USER);//보드에 저장된 블록을 지우는 함수
void ORBlockB(PLAYER* USER);//or연산으로 블록을 보드에 저장하는 함수
void PRINTBOARD();//보드 정보 출력
int CHECKLINE(PLAYER * USER);//줄확인하는 함수
int CrushButtom(PLAYER* USER);//바닥 충돌 검사//커서 위치 블록 충돌 검사
int CrushButtomBlock(PLAYER* USER);//커서 위치 블록 충돌 검사
void NEWBLOCKS(PLAYER* USER);//새로운 블록을 가져옴
int CHECKAND(PLAYER* USER, int _x, int _y);//임시 이동후 결과 반환
int CheckCrush(PLAYER* USER);//해당 좌표 값의 위치에서 충돌이 있는지 확인
int FirstButtom(PLAYER* USER);//바닥위치 검사
int FirstRight(PLAYER * USER);//제일 오른쪽 블록위치
int ButtomBLOCK_Y(PLAYER * USER);//블록의 가장 아랫부분 좌료값 반환
int ButtomBLOCK_X(PLAYER * USER);//블록의 가장 아랫부분 좌료값 반환
void GOTOBLOCKBUTTOM(PLAYER* USER);//블록을 바닥에 내리는 함수



//게임 동작 제어
void GAMEMANIGER() {
	PLAYER USER;
	USER.NextBlock = RAND(7);
	
	while (1) {
		ORBlockB(&USER);
		PRINTBOARD();
		DELBLOCKXOR(&USER);

		PlayerInfo(&USER);
		if (CHECKLINE(&USER)) {
			PlayerInfo(&USER);
			PRINTBOARD();
		}

		while (KBHIT(&USER)) {
			ORBlockB(&USER);
			PRINTBOARD();
			DELBLOCKXOR(&USER);
			DELAY(100 / 2);
		}

		while (1) {
			

			if (CrushButtom(&USER) || CrushButtomBlock(&USER)) {
				ORBlockB(&USER);
				PRINTBOARD();
				//새로운 블록을 받아온다 
				NEWBLOCKS(&USER);
				USER.X = FX / 2 + 1;
				USER.Y = FY - 1;
				USER.BlockLot = 0;
				break;
			}

			if (!CHECKAND(&USER, 0, 1)/*임시 이동 후 충돌 검사(AND연산으로)*/) {
				
				USER.Y++;
				break;
			}

		}

		if (CheckCrush(&USER)) 	break;

		DELAY(1000 / 2);
	}
	CLEANING();
	gotoxy(10, 5);
	puts("G.A.M.E_O.V.E.R_");
	gotoxy(10, 6);
	printf("YOUR SCORE : %d", USER.score);
	DELAY(5000);
}
//실행
int main(void) {
	CLEANING();
	SetCurSorType(NOCURSOR);
	SETRAND();

	if (GAMESTART() == 1) {
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


//게임 시작 화면 출력
int GAMESTART(void) {
	int choise;
	gotoxy(PRINTLINEX, PRINTLINEY);
	printf("-------------------------------------------------------------");
	gotoxy(PRINTLINEX, PRINTLINEY + 1);
	printf("| @ 테트리스 게임 @	   				  |");
	gotoxy(PRINTLINEX, PRINTLINEY + 2);
	printf("| <게임방법>					          |");
	gotoxy(PRINTLINEX, PRINTLINEY + 3);
	printf("| 방향키로 내려 오는 블록을 쌓아 맞추면 됩니다.		  |");
	gotoxy(PRINTLINEX, PRINTLINEY + 4);
	printf("| '←', '→'키로 블록을 움직일 수 있습니다.		  |");
	gotoxy(PRINTLINEX, PRINTLINEY + 5);
	printf("| 스페이스키로 블록을 바닥에 놓을 수 있습니다.		  |");
	gotoxy(PRINTLINEX, PRINTLINEY + 6);
	printf("| '↑'키로 블록을 회전 시킬 수 있습니다.			  |");
	gotoxy(PRINTLINEX, PRINTLINEY + 7);
	printf("| '↓'키로 블록을 아래로 내려보냅니다.			  |");
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
//좌표이동
void gotoxy(int x, int y) {
	COORD Cur;
	Cur.X = x;
	Cur.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}
//커서 타입 변경
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
//보드 정보 저장
void SETBOARD() {
	int x, y;
	for (y = 0; y < FEELDH; y++) {
		for (x = 0; x < FEELDW; x++) {
			Board[y][x] = EMPTY;
		}
	}
}
//게임 종료
int GAMEOVER() {
	int x = 3, y = 0;
	for (; x < 7; x++) {
		if (Board[y][x] == BRICK && Board[y + 1][x] == BRICK)
			return 1;
	}
	return 0;
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
			gotoxy(INFODATAPRINTX + x * 2, INFODATAPRINTY + 2 + (y + 1));
			puts(arTile[blocks[user->NextBlock][0][y][x]]);
		}
	}
}
//키 입력
int KBHIT(PLAYER * USER) {
	static int count = 0;
	int getkye;
	if (_kbhit()) {
		getkye = _getch();

		if (getkye == 0xE0 ) {
			getkye = _getch();
			
			
			if (count == 3) {
				count = 0;
				rewind(stdin);
				return 0;
			}
			switch (getkye) {
				//방향키 왼쪽
			case LEFT:

				if (USER->X == 0) break;
				if (!CHECKAND(USER, -1, 0)/*임시 이동 후 충돌 검사(AND연산으로)*/) {
					//문제가 없다면
					USER->X--;
					count++;
					rewind(stdin);
				}

				break;
				//방향키 오른쪽
			case RIGHT:

				if (USER->X == FEELDW - 1 || USER->X + FirstRight(USER) == FEELDW - 1) break;
				if (!CHECKAND(USER, 1, 0)/*임시 이동 후 충돌 검사(AND연산으로)*/) {
					//문제가 없다면
					USER->X++;
					count++;
					rewind(stdin);
				}

				break;
				//방향키 아래쪽
			case DOWN:

				if (USER->Y + FirstButtom(USER) > FEELDH - 3) break;
				if (!CHECKAND(USER, 0, 1)/*임시 이동 후 충돌 검사(AND연산으로)*/) {
					//문제가 없다면
					USER->Y++;
					count++;
					rewind(stdin);
				}

				break;
				//방향키 윗쪽
			case UP:

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
				count++;
				rewind(stdin);
				break;
			}
		}
		else {
			getkye = getch();
			switch (getkye)
			{
			case 32:

				GOTOBLOCKBUTTOM(USER);
				PRINTBOARD();
				//새로운 블록을 받아온다 
				NEWBLOCKS(USER);
				USER->X = FX / 2 + 1;
				USER->Y = FY - 1;
				USER->BlockLot = 0;
				count = 0;
				rewind(stdin);
				break;
			
			}
		}
		return 1;
	}
	return 0;
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
//먼저 지움 //
void FristDELBLOCK(PLAYER* USER) {
	int x, y;
	for (y = 0; y < 4; y++) {
		for (x = 0; x < 4; x++) {
			Board[USER->Y + y-1][USER->X + x] = Board[USER->Y + y-1][USER->X + x] ^ blocks[USER->NowBlock][USER->BlockLot][y][x];
		}
	}
}
//or연산으로 블록을 보드에 저장하는 함수
void ORBlockB(PLAYER* USER) {
	int x, y;

	for (y = 0; y < 4; y++) {
		for (x = 0; x < 4; x++) {
			Board[USER->Y + y][USER->X + x] = Board[USER->Y + y][USER->X + x] | blocks[USER->NowBlock][USER->BlockLot][y][x];
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
//줄확인하는 함수
int CHECKLINE(PLAYER * USER) {

	int nFraim, nStay;
	int checkX;
	int count = 0;
	nFraim = FEELDH - 1;
	for (; nFraim > 0; nFraim--) {
		for (checkX = 0; checkX < FEELDW; checkX++) {
			if (Board[nFraim][checkX] == EMPTY) {
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
//새로운 블록을 가져옴
void NEWBLOCKS(PLAYER* USER) {
	USER->NowBlock = USER->NextBlock;
	USER->NextBlock = RAND(7);
}
//임시 이동후 결과 반환
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
//블록의 가장 아랫부분 좌료값 반환
int ButtomBLOCK_Y(PLAYER * USER) {
	int x, y;
	for (y = 3; y > 0; y--) {
		for (x = 0; x < 4; x++) {
			if (blocks[USER->NowBlock][USER->BlockLot][y][x] == BRICK)
			{
				return y;
			}
		}
	}
	return 0;
}
int ButtomBLOCK_X(PLAYER * USER) {
	int x, y;
	for (y = 3; y > 0; y--) {
		for (x = 0; x < 4; x++) {
			if (blocks[USER->NowBlock][USER->BlockLot][y][x] == BRICK)
			{
				return x;
			}
		}
	}
	return 0;
}

//블록을 바닥에 내리는 함수
void GOTOBLOCKBUTTOM(PLAYER* USER) {
	int checkY, checkX;

	checkY = ButtomBLOCK_Y(USER);
	checkX = ButtomBLOCK_X(USER);
	while (USER->Y + checkY <= FEELDH - 1) {
		if (USER->Y + checkY == FEELDH - 1) {
			if (CheckCrush(USER)) {
				USER->Y--;
			}
			ORBlockB(USER);
			return;
		}
		if (!CheckCrush(USER)) {
			USER->Y++;
		}
		else {
			USER->Y--;
			ORBlockB(USER);
			return;
		}
	}
}