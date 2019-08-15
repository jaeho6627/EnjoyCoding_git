/****************************
�����̸� : ��Ʈ���� ver1.8.cpp
�� �� �� : ����ȣ
�������� : 19.8.14 09:05
������� : 
	1. Ű�Է� ������ ���� ����
	2. ������� �ʴ� �Լ� ����
	3. �ڵ� �����߰�
	4. �ڵ� ����ȭ �۾�
	5. �Լ��̸� ����
	6. �����̸� ����
�߰߿��� : 
	1. ����� ������ ���� �ٿ��� ���η� ��� ȸ���� ��, ����� ���η� �����κ� �߷�����
	2. �߷����� ����� ���� �������� ù��° ��ġ�� ��µ�
*****************************/

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
#define FIELDW 10//�ʵ����
#define FIELDH 20//�ʵ����
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
	unsigned int X = FX / 2 + 1;
	unsigned int Y = FY - 1;
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
int Wall[FIELDH + 2][FIELDW + 2];
//�÷��� ����
int Board[FIELDH][FIELDW];


int GAMESTART(void);//���ӽ���ȭ��
void gotoxy(int x, int y);//��ǥ�̵�
void SetCurSorType(CURSOR_TYPE c);//Ŀ�� Ÿ�� ����
void SETWALL();//�� ���� ����
void PRINTWALL();//�� ���� ���
void SETBOARD();//���� ���� ����
int GAMEOVER();//���� ����
void PlayerInfo(PLAYER* user);//�÷��̾� ���� ���
int KBHIT(PLAYER * USER);//Ű �Է�
void DELBLOCKXOR(PLAYER* USER);//���忡 ����� ����� ����� �Լ�
void ORBlockB(PLAYER* USER);//or�������� ����� ���忡 �����ϴ� �Լ�
void PRINTBOARD();//���� ���� ���
int CHECKLINE(PLAYER * USER);//��Ȯ���ϴ� �Լ�
int CrushBottom(PLAYER* USER);//�ٴ� �浹 �˻�//Ŀ�� ��ġ ��� �浹 �˻�
int CrushBottomBlock(PLAYER* USER);//Ŀ�� ��ġ ��� �浹 �˻�
void NEWBLOCKS(PLAYER* USER);//���ο� ����� ������
int CHECKAND(PLAYER* USER, int _x, int _y);//�ӽ� �̵��� ��� ��ȯ
int CheckCrush(PLAYER* USER);//�ش� ��ǥ ���� ��ġ���� �浹�� �ִ��� Ȯ��
int Bottom(PLAYER* USER);//�ٴ���ġ �˻�
int RightMost(PLAYER * USER);//���� ������ �����ġ
int BottomBLOCK_Y(PLAYER * USER);//����� ���� �Ʒ��κ� �·ᰪ ��ȯ
int BottomBLOCK_X(PLAYER * USER);//����� ���� �Ʒ��κ� �·ᰪ ��ȯ
void GOTOBLOCKBOTTOM(PLAYER* USER);//����� �ٴڿ� ������ �Լ�



//���� ���� ����
void GAMEMANIGER() {
	PLAYER USER;		//���� ������ ������ ������ ����
	USER.NextBlock = RAND(7);	//��������� ���� ����
	
	while (1) {
		ORBlockB(&USER);	//���� ������ ������� ��������� ���忡 ����
		PRINTBOARD();		//��������� ������ ���带 ���
		DELBLOCKXOR(&USER);	//�ٽ� ��������� ����

		PlayerInfo(&USER);	//���� ������ ���

		if (CHECKLINE(&USER)) {	//������ �˻�� ���� ��Ȳ�� Ȯ�� & ������ ��� �ش� ������ ����
			PlayerInfo(&USER);	//�����Ѱ�� ���� ���� ���
			//PRINTBOARD();	//���� ���� ���¸� �ٽ� ���
		}

		while (KBHIT(&USER)) {	//������ Ű�Է¿� ���� ��ǥ���� ó��
			ORBlockB(&USER);	//ó���� ��ǥ�� ����� �̵����� ���忡 ����
			PRINTBOARD();		//��ϰ��� ����� ���带 ���
			DELBLOCKXOR(&USER);	//�ٽ� ����� ����
			DELAY(100 / 2);		//���� �ð��� �����̸� �༭ �������� �ε巯�������� ��
		}

		if (CrushBottom(&USER) || CrushBottomBlock(&USER)) {
			//����� �ٴڿ� ���� ��� �Ǵ� ����� �Ʒ��� �̹� ����� �ִ� ���
			ORBlockB(&USER);	//�ش� ��ġ�� ����� ���� (�̶� ����Ǵ� ����� �ٽ� ������ ����)
			PRINTBOARD();	//����� ����� ������ ��Ȳ�� �ٽ� ���
			//���ο� ����� �޾ƿ´� 
			NEWBLOCKS(&USER);
			USER.X = FX / 2 + 1;	//������ ��ǥ ���� �⺻ ��ġ�� �̵�
			USER.Y = FY - 1;
			USER.BlockLot = 0;		//���ȸ�� ���� �⺻���� �ǵ���
			if (CheckCrush(&USER)) 	break;	//���� �⺻ ������ġ�� ����� ������� ���ϴ� ��� ���� ������ Ż�� (���ӿ��� ����)
		}
		else if (!CHECKAND(&USER, 0, 1)/*�ӽ� �̵� �� �浹 �˻�(AND��������)*/) {	//�� ������ �ƴ� ���
			//y��ǥ ���� 1�÷� ����� �̵����� �� �浹�ϴ��� �˻�, �浿���� �ʴ´ٸ� ������ y��ǥ�� 1 ����
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
//����
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
		printf("������ �����մϴ�.");
		DELAY(2000);
	}
	return 0;
}


//���� ���� ȭ�� ���
int GAMESTART(void) {
	int choise;
	gotoxy(PRINTLINEX, PRINTLINEY);
	printf("-------------------------------------------------------------");
	gotoxy(PRINTLINEX, PRINTLINEY + 1);
	printf("| @ ��Ʈ���� ���� @	   				  |");
	gotoxy(PRINTLINEX, PRINTLINEY + 2);
	printf("| <���ӹ��>					          |");
	gotoxy(PRINTLINEX, PRINTLINEY + 3);
	printf("| ����Ű�� ���� ���� ����� �׾� ���߸� �˴ϴ�.		  |");
	gotoxy(PRINTLINEX, PRINTLINEY + 4);
	printf("| '��', '��'Ű�� ����� ������ �� �ֽ��ϴ�.		  |");
	gotoxy(PRINTLINEX, PRINTLINEY + 5);
	printf("| �����̽�Ű�� ����� �ٴڿ� ���� �� �ֽ��ϴ�.		  |");
	gotoxy(PRINTLINEX, PRINTLINEY + 6);
	printf("| '��'Ű�� ����� ȸ�� ��ų �� �ֽ��ϴ�.			  |");
	gotoxy(PRINTLINEX, PRINTLINEY + 7);
	printf("| '��'Ű�� ����� �Ʒ��� ���������ϴ�.			  |");
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
//��ǥ�̵�
void gotoxy(int x, int y) {
	COORD Cur;
	Cur.X = x;
	Cur.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}
//Ŀ�� Ÿ�� ����
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
//�� ���� ����
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
//�� ���� ���
void PRINTWALL() {
	int x, y;
	for (y = 0; y < FIELDH + 2; y++) {
		for (x = 0; x < FIELDW + 2; x++) {
			gotoxy(FX + x * 2, FY + y);
			puts(arTile[Wall[y][x]]);
		}
	}
}
//���� ���� ����
void SETBOARD() {
	int x, y;
	for (y = 0; y < FIELDH; y++) {
		for (x = 0; x < FIELDW; x++) {
			Board[y][x] = EMPTY;
		}
	}
}
//���� ����
int GAMEOVER() {
	int x = 3, y = 0;
	for (; x < 7; x++) {
		if (Board[y][x] == BRICK && Board[y + 1][x] == BRICK)
			return 1;
	}
	return 0;
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
			gotoxy(INFODATAPRINTX + x * 2, INFODATAPRINTY + 2 + (y + 1));
			puts(arTile[blocks[user->NextBlock][0][y][x]]);
		}
	}
}
//Ű �Է�
int KBHIT(PLAYER * USER) {
	//static int count = 0;		//�Լ��� �����ϴ��� �Լ��� �ҷ� Ű�� �Է¹޴� Ƚ���� ����ϱ� ���� static���� ����
	int getkye = 0;			//������ �Է��� Ű ���� ����

	if (_kbhit()) {		//Ű���尡 ���ȴٸ�
		getkye = _getch();		//Ű���� �ް�

		if (getkye == 0xE0 ) {		//Ű���� 224�� ���
			getkye = _getch();		//�ٽ� Ű�� �Է¹���

			switch (getkye) {
				//����Ű ����
			case LEFT:

				if (USER->X == 0) break;
				if (!CHECKAND(USER, -1, 0)/*�ӽ� �̵� �� �浹 �˻�(AND��������)*/) {
					//������ ���ٸ�
					USER->X--;
				}
				rewind(stdin);
				break;
				//����Ű ������
			case RIGHT:

				if (USER->X == FIELDW - 1 || USER->X + RightMost(USER) == FIELDW - 1) break;
				if (!CHECKAND(USER, 1, 0)/*�ӽ� �̵� �� �浹 �˻�(AND��������)*/) {
					//������ ���ٸ�
					USER->X++;
				}
				rewind(stdin);
				break;
				//����Ű �Ʒ���
			case DOWN:

				if (USER->Y + Bottom(USER) > FIELDH - 3) break;
				if (!CHECKAND(USER, 0, 1)/*�ӽ� �̵� �� �浹 �˻�(AND��������)*/) {
					//������ ���ٸ�
					USER->Y++;
				}
				rewind(stdin);
				break;
				//����Ű ����
			case UP:

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
				/*����� ������ ���� �ٿ��� ȸ���� ���η� ��� �����ϴ� ���
				�迭�� ���� ���α��̸� ��� ���� ���� �迭��ҿ� �߷����� ����� �����*/
				rewind(stdin);
				break;
			}
		}
		
		if(getkye == 32){ //�����̽��� �Է½�

			GOTOBLOCKBOTTOM(USER); //����� ������ x�࿡ �ش��ϴ� ���尡���� y�࿡ ����� ����
			PRINTBOARD();
			//���ο� ����� �޾ƿ´� 
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
//���� ����� ����� �Լ� //
void DELBLOCKXOR(PLAYER* USER) {
	int x, y;
	for (y = 0; y < 4; y++) {
		for (x = 0; x < 4; x++) {
			Board[USER->Y + y][USER->X + x] = Board[USER->Y + y][USER->X + x] ^ blocks[USER->NowBlock][USER->BlockLot][y][x];
		}
	}
}
//or�������� ����� ���忡 �����ϴ� �Լ�
void ORBlockB(PLAYER* USER) {
	int x, y;

	for (y = 0; y < 4; y++) {
		for (x = 0; x < 4; x++) {
			Board[USER->Y + y][USER->X + x] = Board[USER->Y + y][USER->X + x] | blocks[USER->NowBlock][USER->BlockLot][y][x];
		}
	}
}
//���� ���� ���
void PRINTBOARD() {
	int x, y;
	for (y = 0; y < FIELDH; y++) {
		for (x = 0; x < FIELDW; x++) {
			gotoxy(FX + (x + 1) * 2, FY + (y + 1));
			puts(arTile[Board[y][x]]);
		}
	}

}
//��Ȯ���ϴ� �Լ�
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
//�ٴ� �浹 �˻�
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
//Ŀ�� ��ġ ��� �浹 �˻�
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
//���ο� ����� ������
void NEWBLOCKS(PLAYER* USER) {
	USER->NowBlock = USER->NextBlock;
	USER->NextBlock = RAND(7);
}
//�ӽ� �̵��� ��� ��ȯ
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
//�ٴ���ġ �˻�
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

//���� ������ �����ġ
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
//����� ���� �Ʒ��κ� �·ᰪ ��ȯ
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

//����� �ٴڿ� ������ �Լ�
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