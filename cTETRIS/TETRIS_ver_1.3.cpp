#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <conio.h>
#define SETRAND() srand((unsigned int)time(NULL))
#define RAND(n) rand()%(n)
#define DELAY(n) Sleep(n)
#define CLEANING() system("cls")

//��ǥ �̵� �Լ�
void gotoxy(int x, int y) {
	COORD Cur;
	Cur.X = x;
	Cur.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}


//���� ������ ���� #################################################################################
//���� ���� ���� ��ġ ���ȭ
#define PRINTLINEX  30
#define PRINTLINEY  10

//���� ���� �����ġ ���ȭ(�ð�, ���� ���, ����)
#define INFODATAPRINTX 85
#define INFODATAPRINTY 0

#define FEELDW 10//�ʵ����
#define FEELDH 20//�ʵ����

//���� ��� �⺻ ��ġ
#define FX 5
#define FY 1

//Ű���� �Է� �� ���ȭ
#define LEFT 75

#define RIGHT 77

#define UP 72

#define DOWN 80


typedef struct player {
	unsigned int score = 0;
	unsigned int X=FX-1;
	unsigned int Y=FY-1;
}PLAYER;

//���콺 Ŀ�� Ÿ��
typedef enum { NOCURSOR, SOLIDCURSOR, NORMALCURSOR } CURSOR_TYPE;

//���ӿ� ���� ������ Ÿ��
enum { EMPTY, BRICK, WALL };
const char * arTile[] = { ", ", "��", "��" };

//ȭ�鿡 ��� ��
int Wall[FEELDH + 2][FEELDW + 2];

//�÷��� ����
int Board[FEELDH][FEELDW];

//���
int Brick[3][3] = { BRICK };

//#####################################################################################################

//���� �Լ�##############################################################################################
//�� ���� ����
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

//���� ���� ����
void SETBOARD() {
	int x, y;
	for (y = 0; y < FEELDH; y++) {
		for (x = 0; x < FEELDW; x++) {
			Board[y][x] = EMPTY;
		}
	}
}

////��� ���� ����
//void SETBRICK(PLAYER * USER) {
//	BOARDBRICK(USER);
//}


//########################################################################################################

//��� �Լ�###############################################################################################
//�� ���� ���
void PRINTWALL() {
	int x, y;
	for (y = 0; y < FEELDH + 2; y++) {
		for (x = 0; x < FEELDW + 2; x++) {
			gotoxy(FX + x * 2, FY + y);
			puts(arTile[Wall[y][x]]);
		}
	}
}

//���� ���� ���
void PRINTBOARD() {
	int x, y;
	for (y = 0; y < FEELDH; y++) {
		for (x = 0; x < FEELDW; x++) {
			gotoxy(FX + (x+1) * 2, FY + (y+1));
			puts(arTile[Board[y][x]]);
		}
	}

}

//�÷��̾� ���� ���
void PlayerInfo(PLAYER * user) {
	gotoxy(INFODATAPRINTX, INFODATAPRINTY);
	printf("���� : %d", user->score);
}

//���� ���� ȭ�� ���(���� ����� ����)
int GAMESTART(void) {
	int choise;
	gotoxy(PRINTLINEX, PRINTLINEY);
	printf("-------------------------------------------------------------");
	gotoxy(PRINTLINEX, PRINTLINEY + 1);
	printf("| @ ���� ��Ʈ���� ���� @					  |");
	gotoxy(PRINTLINEX, PRINTLINEY + 2);
	printf("| <���ӹ��>					          |");
	gotoxy(PRINTLINEX, PRINTLINEY + 3);
	printf("| ����Ű�� ���� ���� ����� �׾� ���߸� �˴ϴ�.		  |");
	gotoxy(PRINTLINEX, PRINTLINEY + 4);
	printf("| '��', '��'Ű�� ����� ������ �� �ֽ��ϴ�.		  |");
	gotoxy(PRINTLINEX, PRINTLINEY + 5);
	printf("| �����̽�Ű�� ����� ȸ�� ��ų �� �ֽ��ϴ�.		  |");
	gotoxy(PRINTLINEX, PRINTLINEY + 6);
	printf("| '��'Ű�� ������ ���� ��ϰ� ��ȯ�� �� �ֽ��ϴ�.           |");
	gotoxy(PRINTLINEX, PRINTLINEY + 7);
	printf("| '��'Ű�� ����� �ٷ� ���� ���� �� �ֽ��ϴ�.	          |");
	gotoxy(PRINTLINEX, PRINTLINEY + 8);
	printf("-------------------------------------------------------------");
	gotoxy(PRINTLINEX, PRINTLINEY + 9);
	printf("1. ���� ���� 2. ����");
	gotoxy(PRINTLINEX, PRINTLINEY + 10);
	printf("����: ");
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

//ó�� �Լ�###############################################################################################
//��� ���� ���忡 ����
//void BOARDBRICK(PLAYER * USER) {
//	Board[USER->Y][USER->X] = Brick[0][0];
//
//}

//Ŀ���� x��ǥ ���� �޾ƿ´�
int whereX(void) {
	CONSOLE_SCREEN_BUFFER_INFO BUFINFO;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &BUFINFO);
	return BUFINFO.dwCursorPosition.X;
}
//Ŀ���� y��ǥ ���� �޾ƿ´�
int whereY(void) {
	CONSOLE_SCREEN_BUFFER_INFO BUFINFO;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &BUFINFO);
	return BUFINFO.dwCursorPosition.Y;
}

//Ŀ���� Ÿ���� �����ϴ� �Լ� (Ŀ���� �Ⱥ��̰� ���̰� �ϴ� ���� ���� �� �� ����)
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

//Ű �Է�
int KBHIT(PLAYER * USER) {
	int getkye;
	if (_kbhit()) {
		getkye = _getch();

		if (getkye == 0xE0 || getkye == 0) {

			Board[USER->Y][USER->X] = EMPTY;

			getkye = _getch();
			switch (getkye) {
				//����Ű ����
			case 75:
				
				if (USER->X > 0 && Board[USER->Y][USER->X-1] != BRICK) {
					USER->X -= 1;
				}

				break;
				//����Ű ������
			case 77:

				if (USER->X < FEELDW-1 && Board[USER->Y][USER->X + 1] != BRICK) {
					USER->X += 1;
				}

				break;
				//����Ű �Ʒ���
			case 80:

				if (USER->Y > 0 && USER->Y < FEELDH-1 && Board[USER->Y+1][USER->X] != BRICK) {
					USER->Y += 1;
				}

				break;
				//����Ű ����
			case 72:

				//��� ���� �ٲٴ� �Լ�

				break;
			}
			if (getkye == ' ') {

				//����� �Ʒ��� ���� �߸��� �Լ�
				
			}
		}
		Board[USER->Y][USER->X] = BRICK;
		return 1;
	}
	return 0;
}

//�� Ȯ��
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
//���� ����
int GAMEOVER() {
	int x=3, y=0;
	for (; x < 7; x++) {
		if (Board[y][x] == BRICK && Board[y+1][x] == BRICK)
			return 1;
	}
	return 0;
}

//���� ���� ����
void GAMEMANIGER() {
	PLAYER USER;
	//int x, y;
	while (1) {
		//��� �迭�� ��� ���� ����

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
		printf("������ �����մϴ�.");
		DELAY(2000);
	}
	return 0;
}
