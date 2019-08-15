/****************************
파일이름 : 테트리스 ver1.8.cpp
작 성 자 : 정재호
수정일자 : 19.8.14 09:05
수정목록 : 
	1. 키입력 딜레이 현상 수정
	2. 사용하지 않는 함수 삭제
	3. 코드 설명추가
	4. 코드 간략화 작업
	5. 함수이름 수정
	6. 변수이름 수정
발견오류 : 
	1. 블록을 오른쪽 벽에 붙여서 가로로 길게 회전할 때, 블록이 가로로 일정부분 잘려나감
	2. 잘려나간 블록은 다음 가로줄의 첫번째 위치에 출력됨
*****************************/

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
#define FIELDW 10//필드넓이
#define FIELDH 20//필드높이
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
int Wall[FIELDH + 2][FIELDW + 2];
//플레이 보드
int Board[FIELDH][FIELDW];


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
int CrushBottom(PLAYER* USER);//바닥 충돌 검사//커서 위치 블록 충돌 검사
int CrushBottomBlock(PLAYER* USER);//커서 위치 블록 충돌 검사
void NEWBLOCKS(PLAYER* USER);//새로운 블록을 가져옴
int CHECKAND(PLAYER* USER, int _x, int _y);//임시 이동후 결과 반환
int CheckCrush(PLAYER* USER);//해당 좌표 값의 위치에서 충돌이 있는지 확인
int Bottom(PLAYER* USER);//바닥위치 검사
int RightMost(PLAYER * USER);//제일 오른쪽 블록위치
int BottomBLOCK_Y(PLAYER * USER);//블록의 가장 아랫부분 좌료값 반환
int BottomBLOCK_X(PLAYER * USER);//블록의 가장 아랫부분 좌료값 반환
void GOTOBLOCKBOTTOM(PLAYER* USER);//블록을 바닥에 내리는 함수



//게임 동작 제어
void GAMEMANIGER() {
	PLAYER USER;		//유저 정보를 저장할 변수를 생성
	USER.NextBlock = RAND(7);	//다음블록의 값을 생성
	
	while (1) {
		ORBlockB(&USER);	//유저 정보의 지출력할 블록정보를 보드에 저장
		PRINTBOARD();		//블록정보를 저장한 보드를 출력
		DELBLOCKXOR(&USER);	//다시 블록정보를 지움

		PlayerInfo(&USER);	//유저 정보를 출력

		if (CHECKLINE(&USER)) {	//가로줄 검사로 득점 상황을 확인 & 득점인 경우 해당 가로줄 제거
			PlayerInfo(&USER);	//득접한경우 유저 정보 출력
			//PRINTBOARD();	//현재 보드 상태를 다시 출력
		}

		while (KBHIT(&USER)) {	//유저의 키입력에 대한 좌표값을 처리
			ORBlockB(&USER);	//처리된 좌표로 블록을 이동시켜 보드에 저장
			PRINTBOARD();		//블록값이 저장된 보드를 출력
			DELBLOCKXOR(&USER);	//다시 블록을 제거
			DELAY(100 / 2);		//일정 시간의 딜레이를 줘서 움직임이 부드러워지도록 함
		}

		if (CrushBottom(&USER) || CrushBottomBlock(&USER)) {
			//블록이 바닥에 닿은 경우 또는 블록의 아래에 이미 블록이 있는 경우
			ORBlockB(&USER);	//해당 위치에 블록을 저장 (이때 저장되는 블록은 다시 지우지 않음)
			PRINTBOARD();	//블록이 저장된 보드의 상황을 다시 출력
			//새로운 블록을 받아온다 
			NEWBLOCKS(&USER);
			USER.X = FX / 2 + 1;	//유저의 좌표 값을 기본 위치로 이동
			USER.Y = FY - 1;
			USER.BlockLot = 0;		//블록회전 값을 기본으로 되돌림
			if (CheckCrush(&USER)) 	break;	//만약 기본 시작위치에 블록을 출력하지 못하는 경우 무한 루프를 탈출 (게임오버 조건)
		}
		else if (!CHECKAND(&USER, 0, 1)/*임시 이동 후 충돌 검사(AND연산으로)*/) {	//위 조건이 아닌 경우
			//y좌표 값을 1늘려 블록을 이동했을 때 충돌하는지 검사, 충동하지 않는다면 유저의 y좌표값 1 증가
			USER.Y++;
		}

		DELAY(1000 / 2);
	}
	CLEANING();
	gotoxy(10, 5);
	puts("G.A.M.E_O.V.E.R_");
	gotoxy(10, 6);
	printf("YOUR SCORE : %d\n", USER.score);
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
	for (y = 0; y < FIELDH + 2; y++) {
		for (x = 0; x < FIELDW + 2; x++) {
			if (y == 0 || y == FIELDH + 1 || x == 0 || x == FIELDW + 1) {
				Wall[y][x] = WALL;
			}
		}
	}
}
//벽 정보 출력
void PRINTWALL() {
	int x, y;
	for (y = 0; y < FIELDH + 2; y++) {
		for (x = 0; x < FIELDW + 2; x++) {
			gotoxy(FX + x * 2, FY + y);
			puts(arTile[Wall[y][x]]);
		}
	}
}
//보드 정보 저장
void SETBOARD() {
	int x, y;
	for (y = 0; y < FIELDH; y++) {
		for (x = 0; x < FIELDW; x++) {
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
	//static int count = 0;		//함수를 종료하더라도 함수가 불려 키를 입력받는 횟수를 계산하기 위해 static으로 선언
	int getkye = 0;			//유저의 입력한 키 값을 저장

	if (_kbhit()) {		//키보드가 눌렸다면
		getkye = _getch();		//키값을 받고

		if (getkye == 0xE0 ) {		//키값이 224인 경우
			getkye = _getch();		//다시 키를 입력받음

			switch (getkye) {
				//방향키 왼쪽
			case LEFT:

				if (USER->X == 0) break;
				if (!CHECKAND(USER, -1, 0)/*임시 이동 후 충돌 검사(AND연산으로)*/) {
					//문제가 없다면
					USER->X--;
				}
				rewind(stdin);
				break;
				//방향키 오른쪽
			case RIGHT:

				if (USER->X == FIELDW - 1 || USER->X + RightMost(USER) == FIELDW - 1) break;
				if (!CHECKAND(USER, 1, 0)/*임시 이동 후 충돌 검사(AND연산으로)*/) {
					//문제가 없다면
					USER->X++;
				}
				rewind(stdin);
				break;
				//방향키 아래쪽
			case DOWN:

				if (USER->Y + Bottom(USER) > FIELDH - 3) break;
				if (!CHECKAND(USER, 0, 1)/*임시 이동 후 충돌 검사(AND연산으로)*/) {
					//문제가 없다면
					USER->Y++;
				}
				rewind(stdin);
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
				/*블록을 오른쪽 벽에 붙여서 회전시 가로로 길게 변경하는 경우
				배열의 길이 가로길이를 벗어나 다음 줄의 배열요소에 잘려가난 블록이 저장됨*/
				rewind(stdin);
				break;
			}
		}
		
		if(getkye == 32){ //스페이스바 입력시

			GOTOBLOCKBOTTOM(USER); //블록을 유저의 x축에 해당하는 저장가능한 y축에 블록을 저장
			PRINTBOARD();
			//새로운 블록을 받아온다 
			NEWBLOCKS(USER);
			USER->X = FX / 2 + 1;
			USER->Y = FY - 1;
			USER->BlockLot = 0;
			rewind(stdin);
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
	for (y = 0; y < FIELDH; y++) {
		for (x = 0; x < FIELDW; x++) {
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
	nFraim = FIELDH - 1;
	for (; nFraim > 0; nFraim--) {
		for (checkX = 0; checkX < FIELDW; checkX++) {
			if (Board[nFraim][checkX] == EMPTY) {
				count = 0;
				break;
			}
			count++;
		}
		if (count == FIELDW) {

			for (checkX = 0; checkX < FIELDW; checkX++) {
				Board[nFraim][checkX] = EMPTY;
			}

			for (checkX = 0; checkX < FIELDW; checkX++) {
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
int CrushBottom(PLAYER* USER) {
	int x, y;
	if (USER->Y + 3 == FIELDH - 1) {
		y = 3;
		for (x = 0; x < 4; x++) {
			if (blocks[USER->NowBlock][USER->BlockLot][y][x] == BRICK)
				return 1;
		}
	}
	else if (USER->Y + 2 == FIELDH - 1) {
		y = 2;
		for (x = 0; x < 4; x++) {
			if (blocks[USER->NowBlock][USER->BlockLot][y][x] == BRICK)
				return 1;
		}
	}
	else if (USER->Y + 1 == FIELDH - 1) {
		y = 1;
		for (x = 0; x < 4; x++) {
			if (blocks[USER->NowBlock][USER->BlockLot][y][x] == BRICK)
				return 1;
		}
	}
	else if (USER->Y == FIELDH - 1) {
		y = 0;
		for (x = 0; x < 4; x++) {
			if (blocks[USER->NowBlock][USER->BlockLot][y][x] == BRICK)
				return 1;
		}
	}
	return 0;
}
//커서 위치 블록 충돌 검사
int CrushBottomBlock(PLAYER* USER) {
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
int Bottom(PLAYER* USER) {
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
int RightMost(PLAYER * USER) {
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
int BottomBLOCK_Y(PLAYER * USER) {
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
int BottomBLOCK_X(PLAYER * USER) {
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
void GOTOBLOCKBOTTOM(PLAYER* USER) {
	int checkY, checkX;

	checkY = BottomBLOCK_Y(USER);
	checkX = BottomBLOCK_X(USER);
	while (USER->Y + checkY <= FIELDH - 1) {
		if (USER->Y + checkY == FIELDH - 1) {
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