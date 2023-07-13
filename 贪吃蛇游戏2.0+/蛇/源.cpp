#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<malloc.h>
#include<time.h>
#include<stdbool.h>

//#define X 20
//#define Y 20

int X, Y;   //��Ϸ�߽�
unsigned char smp_type;//�Ѷ�ϵ�� main������ ͨ�������ߵĳ��� �������Ѷ�
void Change(unsigned char type); //������Ϸ�߽�ȷ���Ѷ�  ��0��1��2   type �Ѷ�����
int iCount = 3;
int iCount1 = 3;
enum Dir { enum_east, enum_south, enum_west, enum_north };  //ö������ ���� 

struct Snake                                            //�߽ṹ�� 
{
	int iX, iY;
	enum Dir emDir;
};

struct Node												//����Ľڵ� 
{
	struct Snake stSnake;
	int iCount;
	struct Node* pPre;
	struct Node* pNext;
};

struct Node* g_pHead = NULL;
struct Node* g_pEnd = NULL;
struct Node* g_pHead1 = NULL;
struct Node* g_pEnd1 = NULL;

char g_Back[1000][1000];
void Head(void);//ͷ Ӣ�� 
void Frame(void);//��� Ӣ�� 
void GotoXY(unsigned short hang, unsigned short lie);//ȥĳ��ĳ�� 
void CreatSnake(int iCount);//������ 
void CreatSnake1(int iCount);
void Free();
void Free1();
void DrawSnake(void);
void DrawSnake1(void);
void Move(void);
void Move1(void);
void Drop(void);
void Drop1(void);
void KeyState(void);//��ͷ����ת�� 
void Food(void);
void Appand(void);//���� Ӣ�� 
void Appand1(void);
bool Eat(void);
bool Eat1(void);
bool IsDie(void);
bool IsDie1(void);
void HideCursor(); // �������ع��

void Change(unsigned char type) //��Ϸ�߽�)   //Ŀǰ����
{

	switch (type)
	{
	case 3:  //  ���� 
		X = 20;Y = 20;
		GotoXY(0, 0);

		printf("�߽磺��");
		break;
	case 2:  // �е�
		X = 15;Y = 15;
		GotoXY(0, 0);
		//	g_speed = 200;
		printf("�߽磺��");
		break;
	case 1:  //��
		X = 10;Y = 10;
		GotoXY(0, 0);
		//	g_speed = 500;
		printf("�߽磺С");
	}
	//	g++;
}

int main(void)
{
	srand((unsigned int)time(NULL));
//	while (1)
//	{
		smp_type = 0;
		int tmp = 0;
		printf("please press 1,2,3 select easy to diffrent!\n");
		while (1)
		{
			KeyState();//��ȡ ����
			if (smp_type >= 1 && smp_type <= 3)break;
		}
		system("cls");
		if (smp_type == 1)tmp = 3;     //�ߵĴ�С
		if (smp_type == 2)tmp = 6;
		if (smp_type == 3)tmp = 9;
		Change(smp_type);
		Sleep(1000);
		system("cls");
		while (1)
		{
			Head();    //��ʾ����
			Frame();   //�����߿� 	 
			//GotoXY(5,59);
			//GotoXY(6,59);
			//g_pHead;
			CreatSnake(3);
			CreatSnake1(3);
			DrawSnake();
			DrawSnake1();
			Food();
			HideCursor();   //���ع�� 
			while (1)
			{
				KeyState();
				if (true == Eat())
				{
					Food();
				}
				else if (true == Eat1())
				{
					Food();
				}

				/*if((true==IsDie1())||(true==IsDie()))
				{
					system("pause>0");
				}*/
				if ((true == IsDie1()) || (true == IsDie()))
				{
					system("pause>0");
					if (GetAsyncKeyState(VK_ESCAPE))
						return 0;
					else
					{
						system("cls");break;
					}
				}
				Drop();
				Drop1();
				Move();
				Move1();
				DrawSnake();
				DrawSnake1();

				Sleep(300);


			}

			Free();
			Free1();
		}
//	}
	return 0;
}

void HideCursor() // �������ع��
{

	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };  // �ڶ���ֵΪ0��ʾ���ع��

	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);

}

bool IsDie(void)								//ײ�߽��� 
{
	if (1 == g_Back[g_pHead->stSnake.iX][g_pHead->stSnake.iY - 3])    //1��ʾǽ 0��ʾ���� 2��ʾʳ�� 
	{
		GotoXY(15, 49);
		printf("P1 Game over!\a");
		GotoXY(16, 49);
		printf("����esc�˳���Ϸ");
		return true;
	}
	return false;
}

bool IsDie1(void)								//ײ�߽���    xigai
{
	if (1 == g_Back[g_pHead1->stSnake.iX][g_pHead1->stSnake.iY - 3])    //1��ʾǽ 0��ʾ���� 2��ʾʳ�� 
	{
		GotoXY(15, 49);
		printf("P2 Game over!\a");
		GotoXY(16, 49);
		printf("����esc�˳���Ϸ");
		return true;
	}
	return false;
}

void GotoXY(unsigned short hang, unsigned short lie)			//���ù��λ�� 
{
	COORD cd = { lie,hang };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cd);
}

void Appand(void)								//��ʳ�����ӳ��� 
{
	//�����ڵ� 
	struct Node* pTemp = (struct Node*)malloc(sizeof(struct Node));
	if (NULL == pTemp)
		return;
	//�ڵ��Ա��ֵ 
	pTemp->iCount++;
	pTemp->pPre = NULL;
	pTemp->pNext = NULL;
	pTemp->stSnake.emDir = g_pEnd->stSnake.emDir;
	switch (g_pEnd->stSnake.emDir)
	{
	case enum_east:
		pTemp->stSnake.iX = g_pEnd->stSnake.iX;
		pTemp->stSnake.iY = g_pEnd->stSnake.iY + 1;
		break;
	case enum_south:
		pTemp->stSnake.iX = g_pEnd->stSnake.iX + 1;
		pTemp->stSnake.iY = g_pEnd->stSnake.iY;
		break;
	case enum_west:
		pTemp->stSnake.iX = g_pEnd->stSnake.iX;
		pTemp->stSnake.iY = g_pEnd->stSnake.iY - 1;
		break;
	case enum_north:
		pTemp->stSnake.iX = g_pEnd->stSnake.iX - 1;
		pTemp->stSnake.iY = g_pEnd->stSnake.iY;
		break;
	}
	//���ӵ������β���� 
	pTemp->pPre = g_pEnd;
	g_pEnd->pNext = pTemp;
	g_pEnd = pTemp;

}

void Appand1(void)								//��ʳ�����ӳ���   xiyga
{
	//�����ڵ� 
	struct Node* pTemp1 = (struct Node*)malloc(sizeof(struct Node));
	if (NULL == pTemp1)
		return;
	//�ڵ��Ա��ֵ 
	pTemp1->iCount++;
	pTemp1->pPre = NULL;
	pTemp1->pNext = NULL;
	pTemp1->stSnake.emDir = g_pEnd1->stSnake.emDir;
	switch (g_pEnd1->stSnake.emDir)
	{
	case enum_east:
		pTemp1->stSnake.iX = g_pEnd1->stSnake.iX;
		pTemp1->stSnake.iY = g_pEnd1->stSnake.iY + 1;
		break;
	case enum_south:
		pTemp1->stSnake.iX = g_pEnd1->stSnake.iX + 1;
		pTemp1->stSnake.iY = g_pEnd1->stSnake.iY;
		break;
	case enum_west:
		pTemp1->stSnake.iX = g_pEnd1->stSnake.iX;
		pTemp1->stSnake.iY = g_pEnd1->stSnake.iY - 1;
		break;
	case enum_north:
		pTemp1->stSnake.iX = g_pEnd1->stSnake.iX - 1;
		pTemp1->stSnake.iY = g_pEnd1->stSnake.iY;
		break;
	}
	//���ӵ������β���� 
	pTemp1->pPre = g_pEnd1;
	g_pEnd1->pNext = pTemp1;
	g_pEnd1 = pTemp1;

}

bool Eat(void)									//�ж��Ƿ��ʳ 
{
	if (2 == g_Back[g_pHead->stSnake.iX][g_pHead->stSnake.iY])
	{
		g_Back[g_pHead->stSnake.iX][g_pHead->stSnake.iY] = 0;
		Appand();
		GotoXY(5, 63);
		iCount++;
		printf("\b\b%d", iCount);
		return true;
	}
	else if (3 == g_Back[g_pHead->stSnake.iX][g_pHead->stSnake.iY])
	{
		g_Back[g_pHead->stSnake.iX][g_pHead->stSnake.iY] = 0;
		Appand();
		GotoXY(5, 63);
		iCount++;
		printf("\b\b%d", iCount);
		Appand();
		GotoXY(5, 63);
		iCount++;
		printf("\b\b%d", iCount);
		return true;
	}
	return false;
}

bool Eat1(void)									//�ж��Ƿ��ʳ   xigai
{
	if (2 == g_Back[g_pHead1->stSnake.iX][g_pHead1->stSnake.iY])
	{
		g_Back[g_pHead1->stSnake.iX][g_pHead1->stSnake.iY] = 0;
		Appand1();
		GotoXY(6, 63);
		iCount1++;
		printf("\b\b%d",iCount1);
		return true;
	}
	else if (3 == g_Back[g_pHead1->stSnake.iX][g_pHead1->stSnake.iY])
	{
		g_Back[g_pHead1->stSnake.iX][g_pHead1->stSnake.iY] = 0;
		Appand1();
		GotoXY(6, 63);
		iCount1++;
		printf("\b\b%d", iCount1);
		Appand1();
		GotoXY(6, 63);
		iCount1++;
		printf("\b\b%d", iCount1);
		return true;
	}
	return false;
}

void Food(void)									//ʳ��   xiugai
{
	while (1)
	{
		//����һ������ 
		int x = rand() % (X - 2) + 1;
		int y = rand() % (Y - 2) + 4;
		//�ж��Ƿ���������
		struct Node* pT = g_pHead;
		struct Node* pT1 = g_pHead1;
		while (pT != NULL)
		{
			if (x == pT->stSnake.iX && y == pT->stSnake.iY)
				break;
			pT = pT->pNext;
		}
		while (pT1 != NULL)
		{
			if (x == pT1->stSnake.iX && y == pT1->stSnake.iY)
				break;
			pT1 = pT1->pNext;
		}
		//�ڵĻ�����һ�� 
		if ((NULL != pT1) && (NULL != pT))
			continue;
		//���ڣ��Ǿ��Ǻ����λ��
		else
		{
			int foodshape = rand() % 3;
			if (foodshape == 0)
			{
				foodshape = 3;
			}
			else if (foodshape == 1)
			{
				foodshape = 2;
			}
			g_Back[x][y] = foodshape;
			GotoXY(9 + x, y * 2 + 30);
			if (foodshape == 2)
			{
				printf("��");
			}
			else if (foodshape == 3)
			{
				printf("o");
			}
			break;
		}
	}
}

void KeyState(void)								//��ͷ����ת�� xiugai
{
	if (GetAsyncKeyState(VK_UP))
	{
		g_pHead->stSnake.emDir = enum_north;
	}
	else if (GetAsyncKeyState(VK_DOWN))
	{
		g_pHead->stSnake.emDir = enum_south;
	}
	else if (GetAsyncKeyState(VK_LEFT))
	{
		g_pHead->stSnake.emDir = enum_west;
	}
	else if (GetAsyncKeyState(VK_RIGHT))
	{
		g_pHead->stSnake.emDir = enum_east;
	}

	if (GetAsyncKeyState('W'))
	{
		g_pHead1->stSnake.emDir = enum_north;
	}
	else if (GetAsyncKeyState('S'))
	{
		g_pHead1->stSnake.emDir = enum_south;
	}
	else if (GetAsyncKeyState('A'))
	{
		g_pHead1->stSnake.emDir = enum_west;
	}
	else if (GetAsyncKeyState('D'))
	{
		g_pHead1->stSnake.emDir = enum_east;
	}
	//------------------------------------------  ����Ϊ��ȡ�Ѷȼ���
	else if (GetAsyncKeyState('1'))
	{
		smp_type = 1;
	}
	//------------------------------------------
	else if (GetAsyncKeyState('2'))
	{
		smp_type = 2;
	}
	//------------------------------------------
	else if (GetAsyncKeyState('3'))
	{
		smp_type = 3;
	}
}

void Move(void)									//�ƶ��� 
{
	if (NULL == g_pHead)
		return;
	struct Node* pT = g_pEnd;
	while (pT != g_pHead)
	{
		pT->stSnake = pT->pPre->stSnake;
		pT = pT->pPre;
	}
	switch (g_pHead->stSnake.emDir)
	{
	case enum_east:
		g_pHead->stSnake.iY++;
		break;
	case enum_south:
		g_pHead->stSnake.iX++;
		break;
	case enum_west:
		g_pHead->stSnake.iY--;
		break;
	case enum_north:
		g_pHead->stSnake.iX--;
		break;
	}
}

void Move1(void)									//�ƶ���   xiugai 
{
	if (NULL == g_pHead1)
		return;
	struct Node* pT1 = g_pEnd1;
	while (pT1 != g_pHead1)
	{
		pT1->stSnake = pT1->pPre->stSnake;
		pT1 = pT1->pPre;
	}
	switch (g_pHead1->stSnake.emDir)
	{
	case enum_east:
		g_pHead1->stSnake.iY++;
		break;
	case enum_south:
		g_pHead1->stSnake.iX++;
		break;
	case enum_west:
		g_pHead1->stSnake.iY--;
		break;
	case enum_north:
		g_pHead1->stSnake.iX--;
		break;
	}
}

void Drop(void)									//����β�� 
{
	GotoXY(9 + g_pEnd->stSnake.iX, g_pEnd->stSnake.iY * 2 + 30);
	printf(" ");
}

void Drop1(void)									//����β��   xigai
{
	GotoXY(9 + g_pEnd1->stSnake.iX, g_pEnd1->stSnake.iY * 2 + 30);
	printf(" ");
}

void DrawSnake(void)							//���� 
{
	if (NULL == g_pHead)
		return;
	struct Node* pT = g_pHead;
	while (pT != NULL)
	{
		GotoXY(9 + pT->stSnake.iX, pT->stSnake.iY * 2 + 30);
		printf("O");
		pT = pT->pNext;
	}
}

void DrawSnake1(void)							//����   xigai
{
	if (NULL == g_pHead1)
		return;
	struct Node* pT1 = g_pHead1;
	while (pT1 != NULL)
	{
		GotoXY(9 + pT1->stSnake.iX, pT1->stSnake.iY * 2 + 30);
		printf("@");
		pT1 = pT1->pNext;

	}
}

void CreatSnake(int iCount)					//�����ڵ�  �����ߵĴ�С 
{
	if (iCount <= 0)
		return;
	int i;
	for (i = 0;i < iCount;i++)
	{
		//�����ڵ� 
		struct Node* pT = (struct Node*)malloc(sizeof(struct Node));
		if (NULL == pT)
			return;
		//�ڵ��Ա��ֵ 
		pT->iCount = 0;
		pT->pNext = NULL;
		pT->pPre = NULL;
		pT->stSnake.emDir = enum_west;
		pT->stSnake.iX = 0;
		pT->stSnake.iY = 0;
		// ���ڵ�����������
		if (NULL == g_pHead)
		{
			g_pHead = pT;
			g_pEnd = pT;

			g_pHead->iCount = 1;

			//g_pHead->stSnake.iX=rand()%(X-2)+1;         //�����ȡ������ȷ��iXС�ڣ�X-2��+1 
			//g_pHead->stSnake.iY=rand()%(Y-iCount-1)+3;  //�����ȡ������ȷ��iYС�ڣ�Y-iCount��+1
			g_pHead->stSnake.iX = 7;
			g_pHead->stSnake.iY = 13;
		}
		else
		{
			g_pEnd->pNext = pT;
			pT->pPre = g_pEnd;
			g_pEnd = pT;

			g_pHead->iCount += 1;

			g_pEnd->stSnake.iX = g_pEnd->pPre->stSnake.iX;

			g_pEnd->stSnake.iY = g_pEnd->pPre->stSnake.iY + 1;
		}
	}
}

void CreatSnake1(int iCount)					//�����ڵ�  �����ߵĴ�С   xiuagui
{
	if (iCount <= 0)
		return;
	int i;
	for (i = 0;i < iCount;i++)
	{
		//�����ڵ� 
		struct Node* pT1 = (struct Node*)malloc(sizeof(struct Node));
		if (NULL == pT1)
			return;
		//�ڵ��Ա��ֵ 
		pT1->iCount = 0;
		pT1->pNext = NULL;
		pT1->pPre = NULL;
		pT1->stSnake.emDir = enum_east;
		pT1->stSnake.iX = 0;
		pT1->stSnake.iY = 0;
		// ���ڵ�����������
		if (NULL == g_pHead1)
		{
			g_pHead1 = pT1;
			g_pEnd1 = pT1;

			g_pHead1->iCount = 1;

			//g_pHead1->stSnake.iX=rand()%(X-2)+1;         //�����ȡ������ȷ��iXС�ڣ�X-2��+1 
			//g_pHead1->stSnake.iY=rand()%(Y-iCount-1)+3;  //�����ȡ������ȷ��iYС�ڣ�Y-iCount��+1
			g_pHead1->stSnake.iX = 11;
			g_pHead1->stSnake.iY = 12;
		}
		else
		{
			g_pEnd1->pNext = pT1;
			pT1->pPre = g_pEnd1;
			g_pEnd1 = pT1;

			g_pHead1->iCount += 1;

			g_pEnd1->stSnake.iX = g_pEnd1->pPre->stSnake.iX;

			g_pEnd1->stSnake.iY = g_pEnd1->pPre->stSnake.iY + 1;
		}
	}
}

void Free(void)
{
	if (NULL == g_pHead)
		return;
	struct Node* pT = g_pHead;
	while (NULL != pT)
	{
		//��¼��ɾ���Ľڵ�
		struct Node* pp = pT;
		//�ڵ������� 
		pT = pT->pNext;
		//�ͷż�¼ 
		free(pp);
	}
	g_pHead = NULL;
	g_pEnd = NULL;
}

void Free1(void)                                 //xiufvai
{
	if (NULL == g_pHead1)
		return;
	struct Node* pT1 = g_pHead1;
	while (NULL != pT1)
	{
		//��¼��ɾ���Ľڵ�
		struct Node* pp1 = pT1;
		//�ڵ������� 
		pT1 = pT1->pNext;
		//�ͷż�¼ 
		free(pp1);
	}
	g_pHead1 = NULL;
	g_pEnd1 = NULL;
}

void Frame(void)											//�߿�ֵ 
{
	int i;
	for (i = 0;i < X;i++)
	{
		int j;
		for (j = 0;j < Y;j++)
		{
			if (i == 0 || j == 0 || i == X - 1 || j == Y - 1)
				g_Back[i][j] = 1;
			else g_Back[i][j] = 0;
		}
	}
	for (i = 0;i < X;i++)
	{
		GotoXY(i + 9, 0);
		printf("\t\t\t\t    ");
		int j;
		for (j = 0;j < Y;j++)
		{

			if (g_Back[i][j] == 1)
				printf("�� ");

			else
				printf("  ");
		}
		putchar('\n');
	}
}


void Head(void)												//��ʾ���� 
{
	printf("\n\n\t\t\t\t\t>>>>>>>>>>  ̰����  <<<<<<<<<<\n");
	//printf("\t\t\t\t\t>>>>>  Enter ����/��ͣ   <<<<<\n");
	printf("\t\t\t\t\t>>>>> �������� ����p1����    <<<<<\n");
	printf("\t\t\t\t\t>>>>>  wsad����p2����    <<<<<\n");
	//printf("\t\t\t\t\t>>>>>   Q ���¿�ʼ       <<<<<\n");
	//printf("\t\t\t\t\t>>>>> tab �л��Ѷ�: �� <<<<<\n");
	printf("\t\t\t\t\t>>>>>    p1��ǰ����: %d   <<<<<\n",iCount);
	printf("\t\t\t\t\t>>>>>    p2��ǰ����: %d   <<<<<\n",iCount1);
	printf("\t\t\t\t\t>>>>>   ESC  �˳���Ϸ    <<<<<\n");
	printf("\t\t\t\t\t>>>>>>>>>>>>>>><<<<<<<<<<<<<<<\n");
}

/*void Change(void)   //Ŀǰ����
{
	static int g = 1;

	switch (g % 3)
	{
	case 1:  //�е�
		GotoXY(5, 60);
		g_speed = 350;
		printf("�е�");
		break;
	case 2:  //����
		GotoXY(5, 60);
		g_speed = 200;
		printf("����");
		break;
	case 0:  //��
		GotoXY(5, 60);
		g_speed = 500;
		printf("��");
	}
	g++;
}*/