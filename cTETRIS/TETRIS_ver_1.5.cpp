#include <stdio.h>
#include <time.h>
#include <conio.h>
#include <stdlib.h>
#include <Windows.h>

//��ũ�� �Լ�
#define SETRAND() srand((unsigned int)time(NULL))
#define RAND(n) rand()%(n)
#define DELAY(n) Sleep(n)
#define CLEANING() system("cls")

//������ ����Ʈ

//�����

	//���� �ʱ� UI ��ġ
#define PRINTLINEX  30
#define PRINTLINEY  10
//�������� UI ��ġ
#define INFODATAPRINTX 35
#define INFODATAPRINTY 5

//���� �ʵ� ũ��
#define FEELDW 10//�ʵ����
#define FEELDH 20//�ʵ����

//����UI��ġ
#define FX 5
#define FY 1
//Ű���� �Է� ��
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80

//�ڷ���

	//������� ��������
typedef struct player {
	unsigned int score = 0;
	unsigned int X = FX + 1;
	unsigned int Y = FY-1;
	int NextBlock = rand() % 7;
	int NowBlock = NextBlock;
	int BlockLot = 0;
}PLAYER;

//���콺 Ŀ��
typedef enum { NOCURSOR, SOLIDCURSOR, NORMALCURSOR } CURSOR_TYPE;

//���� ������
enum { EMPTY, BRICK, WALL };
const char* arTile[] = { ", ", "��", "��" };

//���� ����

	//��� ������
int blocks[7][4][4][4] = {
	//�׸�
	{{1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0},{1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0},
	 {1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0},{1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0}},
	 //�����
	{{1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0},{1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0},
	 {1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0},{1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0}},
	 //�������
	{{1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0},{0,1,0,0,1,1,0,0,1,0,0,0,0,0,0,0},
	 {1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0},{0,1,0,0,1,1,0,0,1,0,0,0,0,0,0,0}},
	 //�������� �����
	{{0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0},{1,0,0,0,1,1,0,0,0,1,0,0,0,0,0,0},
	 {0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0},{1,0,0,0,1,1,0,0,0,1,0,0,0,0,0,0}},
	 //�������
	{{1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0},{0,1,0,0,0,1,0,0,1,1,0,0,0,0,0,0},
	 {1,1,1,0,0,0,1,0,0,0,0,0,0,0,0,0},{1,1,0,0,1,0,0,0,1,0,0,0,0,0,0,0}},
	 //�������� �����
	{{0,0,1,0,1,1,1,0,0,0,0,0,0,0,0,0},{1,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0},
	 {1,1,1,0,1,0,0,0,0,0,0,0,0,0,0,0},{1,0,0,0,1,0,0,0,1,1,0,0,0,0,0,0}},
	 //T �� ����
	{{0,1,0,0,1,1,1,0,0,0,0,0,0,0,0,0},{0,1,0,0,1,1,0,0,0,1,0,0,0,0,0,0},
	 {1,1,1,0,0,1,0,0,0,0,0,0,0,0,0,0},{1,0,0,0,1,1,0,0,1,0,0,0,0,0,0,0}}
};

//ȭ�鿡 ��� ��
int Wall[FEELDH + 2][FEELDW + 2];

//�÷��� ����
int Board[FEELDH][FEELDW];
//�Լ� ����Ʈ

	//ó�� �Լ�

		//��ǥ�̵�
void gotoxy(int x, int y);
//Ŀ��Ÿ�� ����
void SetCurSorType(CURSOR_TYPE c);
//Ŀ�� ��ġ �浹 �˻�
int CrushButtomBlock(PLAYER* USER);
//�ٴ� �浹 �˻�
int CrushButtom(PLAYER* USER);
//Ű���� �Է��� ó���ϴ� �Լ�
void KeYProcess(PLAYER* USER);
//��Ȯ���ϴ� �Լ�
int CHECKLINE(PLAYER * USER);
//���� ���� ���� �˻��ϴ� �Լ�
int GAMEOVER(PLAYER* USER);
//���� ���� ����
void GAMEMANIGER();
//xor�������� ����� ���忡 �����ϴ� �Լ�
void ORBlockB(PLAYER* USER);
//���忡 ����� ����� ����� �Լ�
void DELBLOCKXOR(PLAYER* USER);
//���ο� ����� ������
void NEWBLOCKS(PLAYER* USER);
//���޵Ǵ� ���ڰ��� ��ġ�� �ӽ÷� �̵��� �浹 �˻縦 �ǽ�
int CHECKAND(PLAYER* USER, int _x, int _y);
//���ο� ��ϰ� ���� ����� ��ȯ�ϴ� �Լ�
void ChangeBlocks(PLAYER* USER);
//�ش� ��ǥ ���� ��ġ���� �浹�� �ִ��� Ȯ��
int CheckCrush(PLAYER* USER);
//���� ������ �����ġ
int FirstRight(PLAYER* USER);
//�ٴ���ġ �˻�
int FirstButtom(PLAYER* USER);


//��� �Լ�

	//���õ� ���� ���
void PrintBlock(PLAYER* USER);
//�� ���� ���
void PRINTWALL();
//���� ���� ���
void PRINTBOARD();
//�÷��̾� ���� ���
void PlayerInfo(PLAYER* user);
//���� ���� ȭ�� ���
int GAMESTART(void);

//���� �Լ�

	//�� ���� ����
void SETWALL();
//���� ���� ����
void SETBOARD();

//����
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
���忡 ���� ����� ����� ��� : xor ����
���忡 ����� ����ϴ� ��� : or ����
���忡 ��µ� ��ϰ� ����ؾ��ϴ� ����� �浹�ϴ��� Ȯ���ϴ� ��� : AND
*/
/*
����� ����� �迭�� ��ġ���� AND �������� 1�� �κ��� ���ٸ� �����ϰ�
�ִٸ� �⺻ ��ġ�� �̵��ؼ� �ٸ� ����� �޾ƿ��� �ٽ� y��ǥ�� ������Ű�鼭 ����� ����ϴ� ���� �ݺ��Ѵ�.
*/
/*
������ �� �浹 �˻� ���
: ����ؾ��ϴ� ����� ���� ������ ����� ��ġ�� �迭�� ���� ���� -1�� ���� ��� (�Ǵ� �ش� ����� �����ʿ� ����� �ִ� ���) ���������� ����� �̵���ų �� ����
���� �� �浹 �˻� ���
: ����ؾ��ϴ� ����� ���� ���� ����� ��ġ�� 0�� ���� ��� (�Ǵ� �ش� ����� ���ʿ� ����� �ִ� ���) �������� �̵���ų �� ����
�ٴ� �浹 �˻�
: ����ؾ��ϴ� ����� ���� �Ʒ� ����� ��ǥ ��ġ�� ���� ���� -1�� ��� (�Ǵ� �Ʒ� ��ġ�� ����� �ִ� ���) ���̻� �Ʒ��� ������ �� �������� ���� ��ġ�� ����� �ٽ� �����ϰ�
���ο� ����� �޾ƿͼ� ������ ��� ���� �Ѵ�.
*/

//���� ���� ����
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

			/*���� ���� ����*/
			
			if (CHECKLINE(&USER)) {
				PlayerInfo(&USER);
			}
				

			if (CrushButtom(&USER) || CrushButtomBlock(&USER)) {
				ORBlockB(&USER);

				//���ο� ����� �޾ƿ´� 
				NEWBLOCKS(&USER);

				break; //Ż��
			}

			if (kbhit()) {
				KeYProcess(&USER);
				ORBlockB(&USER);
				PRINTBOARD();
				DELBLOCKXOR(&USER);
			}

			if (!CHECKAND(&USER, 0, 1)/*�ӽ� �̵� �� �浹 �˻�(AND��������)*/) {
				//������ ���ٸ�
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
//�ٴ���ġ �˻�
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

//���� ������ �����ġ
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

//�ش� ��ǥ ���� ��ġ���� �浹�� �ִ��� Ȯ��
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

//���ο� ��ϰ� ���� ����� ��ȯ�ϴ� �Լ�
void ChangeBlocks(PLAYER* USER) {
	int temp;
	temp = USER->NowBlock;
	USER->NowBlock = USER->NextBlock;
	USER->NextBlock = temp;
}

//���ο� ����� ������
void NEWBLOCKS(PLAYER* USER) {
	USER->NowBlock = USER->NextBlock;
	USER->NextBlock = RAND(7);
}

//���� ���� ��ǥ���� �������� �Խ÷� �̵��ؼ� AND�� �浹 �˻縦 �Ѵ� //�¿� ���� ������� ���ϵ��� ���� �ʿ�
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
//Ű���� �Է��� ó���ϴ� �Լ�
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
				if (!CHECKAND(USER, -1, 0)/*�ӽ� �̵� �� �浹 �˻�(AND��������)*/) {
					//������ ���ٸ�
					USER->X--;
					break;
				}
			}
			else if (getkey == RIGHT) {
				if (USER->X == FEELDW - 1 || USER->X + FirstRight(USER) == FEELDW - 1)
					return;
				if (!CHECKAND(USER, 1, 0)/*�ӽ� �̵� �� �浹 �˻�(AND��������)*/) {
					//������ ���ٸ�
					USER->X++;
					break;
				}
			}
			else if (getkey == UP) {
				//���� ��ϰ� ���� ����� ��ü
				//ChangeBlocks(USER);
				//����� ȸ��
				if (USER->BlockLot == 3) {
					USER->BlockLot = 0;
				}
				else {
					USER->BlockLot++;
				}
				if (CheckCrush(USER)) {
					//������ �ִٸ� ���� ����
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
				if (!CHECKAND(USER, 0, 1)/*�ӽ� �̵� �� �浹 �˻�(AND��������)*/) {
					//������ ���ٸ�
					USER->Y++;
					break;
				}
			}
			//else if (/*�����̽���*/) {
			//	//		if (/*AND�˻�� �ٴں��� �ö� ���鼭 ��� ���� ��� 0�� ��� Ȯ��*/) {
			//	//			//�ش� ��ġ�� ��� ���� ���忡 ����
			//	//		}
			//}
		}
	}
}

//���� ����� ����� �Լ� //
void DELBLOCKXOR(PLAYER* USER) {
	int x, y;
	for (y = 0; y < 4; y++) {
		for (x = 0; x < 4; x++) {
			Board[USER->Y + y][USER->X + x] = Board[USER->Y + y][USER->X + x] ^ blocks[USER->NowBlock][USER->BlockLot][y][x];
		}
	}
}

//xor�������� ����� ���忡 �����ϴ� �Լ� ( ������ ���� ���� �� ���� ������ ���پ� �ٷ��� �����Ѵ�)
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

//Ŀ�� ��ġ ��� �浹 �˻�
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

//�ٴ� �浹 �˻�
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



//��Ȯ���ϴ� �Լ�
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

//���� ���� ���� �˻��ϴ� �Լ�
int GAMEOVER(PLAYER* USER) {
	
	return 0;
}

//���� �Լ�

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

//����Լ�

	//���õ� ���� ���
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
			gotoxy(FX + (x + 1) * 2, FY + (y + 1));
			puts(arTile[Board[y][x]]);
		}
	}

}

//�÷��̾� ���� ���
void PlayerInfo(PLAYER* user) {
	int x, y;
	gotoxy(INFODATAPRINTX, INFODATAPRINTY);
	printf("���� : %d", user->score);
	gotoxy(INFODATAPRINTX, INFODATAPRINTY + 2);
	puts("- ������� -");
	for (y = 0; y < 4; y++) {
		for (x = 0; x < 4; x++) {
			gotoxy(INFODATAPRINTX+x*2, INFODATAPRINTY + 2 + (y+1));
			puts(arTile[blocks[user->NextBlock][0][y][x]]);
		}
	}
}

//���� ���� ȭ�� ���
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