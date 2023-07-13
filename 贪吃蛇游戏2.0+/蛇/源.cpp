#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<malloc.h>
#include<time.h>
#include<stdbool.h>

//#define X 20
//#define Y 20

int X, Y;   //游戏边界
unsigned char smp_type;//难度系数 main函数中 通过增加蛇的长度 来增减难度
void Change(unsigned char type); //根据游戏边界确定难度  ，0，1，2   type 难度类型
int iCount = 3;
int iCount1 = 3;
enum Dir { enum_east, enum_south, enum_west, enum_north };  //枚举类型 方向 

struct Snake                                            //蛇结构体 
{
	int iX, iY;
	enum Dir emDir;
};

struct Node												//链表的节点 
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
void Head(void);//头 英文 
void Frame(void);//框架 英文 
void GotoXY(unsigned short hang, unsigned short lie);//去某行某列 
void CreatSnake(int iCount);//创造蛇 
void CreatSnake1(int iCount);
void Free();
void Free1();
void DrawSnake(void);
void DrawSnake1(void);
void Move(void);
void Move1(void);
void Drop(void);
void Drop1(void);
void KeyState(void);//箭头控制转向 
void Food(void);
void Appand(void);//附加 英文 
void Appand1(void);
bool Eat(void);
bool Eat1(void);
bool IsDie(void);
bool IsDie1(void);
void HideCursor(); // 用于隐藏光标

void Change(unsigned char type) //游戏边界)   //目前无用
{

	switch (type)
	{
	case 3:  //  困难 
		X = 20;Y = 20;
		GotoXY(0, 0);

		printf("边界：大");
		break;
	case 2:  // 中等
		X = 15;Y = 15;
		GotoXY(0, 0);
		//	g_speed = 200;
		printf("边界：中");
		break;
	case 1:  //简单
		X = 10;Y = 10;
		GotoXY(0, 0);
		//	g_speed = 500;
		printf("边界：小");
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
			KeyState();//获取 按键
			if (smp_type >= 1 && smp_type <= 3)break;
		}
		system("cls");
		if (smp_type == 1)tmp = 3;     //蛇的大小
		if (smp_type == 2)tmp = 6;
		if (smp_type == 3)tmp = 9;
		Change(smp_type);
		Sleep(1000);
		system("cls");
		while (1)
		{
			Head();    //提示文字
			Frame();   //产生边框 	 
			//GotoXY(5,59);
			//GotoXY(6,59);
			//g_pHead;
			CreatSnake(3);
			CreatSnake1(3);
			DrawSnake();
			DrawSnake1();
			Food();
			HideCursor();   //隐藏光标 
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

void HideCursor() // 用于隐藏光标
{

	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };  // 第二个值为0表示隐藏光标

	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);

}

bool IsDie(void)								//撞边结束 
{
	if (1 == g_Back[g_pHead->stSnake.iX][g_pHead->stSnake.iY - 3])    //1表示墙 0表示空气 2表示食物 
	{
		GotoXY(15, 49);
		printf("P1 Game over!\a");
		GotoXY(16, 49);
		printf("输入esc退出游戏");
		return true;
	}
	return false;
}

bool IsDie1(void)								//撞边结束    xigai
{
	if (1 == g_Back[g_pHead1->stSnake.iX][g_pHead1->stSnake.iY - 3])    //1表示墙 0表示空气 2表示食物 
	{
		GotoXY(15, 49);
		printf("P2 Game over!\a");
		GotoXY(16, 49);
		printf("输入esc退出游戏");
		return true;
	}
	return false;
}

void GotoXY(unsigned short hang, unsigned short lie)			//设置光标位置 
{
	COORD cd = { lie,hang };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cd);
}

void Appand(void)								//吃食后增加长度 
{
	//创建节点 
	struct Node* pTemp = (struct Node*)malloc(sizeof(struct Node));
	if (NULL == pTemp)
		return;
	//节点成员赋值 
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
	//链接到链表的尾巴上 
	pTemp->pPre = g_pEnd;
	g_pEnd->pNext = pTemp;
	g_pEnd = pTemp;

}

void Appand1(void)								//吃食后增加长度   xiyga
{
	//创建节点 
	struct Node* pTemp1 = (struct Node*)malloc(sizeof(struct Node));
	if (NULL == pTemp1)
		return;
	//节点成员赋值 
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
	//链接到链表的尾巴上 
	pTemp1->pPre = g_pEnd1;
	g_pEnd1->pNext = pTemp1;
	g_pEnd1 = pTemp1;

}

bool Eat(void)									//判断是否吃食 
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

bool Eat1(void)									//判断是否吃食   xigai
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

void Food(void)									//食物   xiugai
{
	while (1)
	{
		//产生一组坐标 
		int x = rand() % (X - 2) + 1;
		int y = rand() % (Y - 2) + 4;
		//判断是否在蛇身上
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
		//在的话就下一次 
		if ((NULL != pT1) && (NULL != pT))
			continue;
		//不在，那就是合理的位置
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
				printf("□");
			}
			else if (foodshape == 3)
			{
				printf("o");
			}
			break;
		}
	}
}

void KeyState(void)								//箭头控制转向 xiugai
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
	//------------------------------------------  以下为获取难度级别
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

void Move(void)									//移动蛇 
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

void Move1(void)									//移动蛇   xiugai 
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

void Drop(void)									//消除尾巴 
{
	GotoXY(9 + g_pEnd->stSnake.iX, g_pEnd->stSnake.iY * 2 + 30);
	printf(" ");
}

void Drop1(void)									//消除尾巴   xigai
{
	GotoXY(9 + g_pEnd1->stSnake.iX, g_pEnd1->stSnake.iY * 2 + 30);
	printf(" ");
}

void DrawSnake(void)							//画蛇 
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

void DrawSnake1(void)							//画蛇   xigai
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

void CreatSnake(int iCount)					//链表、节点  创造蛇的大小 
{
	if (iCount <= 0)
		return;
	int i;
	for (i = 0;i < iCount;i++)
	{
		//创建节点 
		struct Node* pT = (struct Node*)malloc(sizeof(struct Node));
		if (NULL == pT)
			return;
		//节点成员赋值 
		pT->iCount = 0;
		pT->pNext = NULL;
		pT->pPre = NULL;
		pT->stSnake.emDir = enum_west;
		pT->stSnake.iX = 0;
		pT->stSnake.iY = 0;
		// 将节点连在链表上
		if (NULL == g_pHead)
		{
			g_pHead = pT;
			g_pEnd = pT;

			g_pHead->iCount = 1;

			//g_pHead->stSnake.iX=rand()%(X-2)+1;         //随机数取余数，确保iX小于（X-2）+1 
			//g_pHead->stSnake.iY=rand()%(Y-iCount-1)+3;  //随机数取余数，确保iY小于（Y-iCount）+1
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

void CreatSnake1(int iCount)					//链表、节点  创造蛇的大小   xiuagui
{
	if (iCount <= 0)
		return;
	int i;
	for (i = 0;i < iCount;i++)
	{
		//创建节点 
		struct Node* pT1 = (struct Node*)malloc(sizeof(struct Node));
		if (NULL == pT1)
			return;
		//节点成员赋值 
		pT1->iCount = 0;
		pT1->pNext = NULL;
		pT1->pPre = NULL;
		pT1->stSnake.emDir = enum_east;
		pT1->stSnake.iX = 0;
		pT1->stSnake.iY = 0;
		// 将节点连在链表上
		if (NULL == g_pHead1)
		{
			g_pHead1 = pT1;
			g_pEnd1 = pT1;

			g_pHead1->iCount = 1;

			//g_pHead1->stSnake.iX=rand()%(X-2)+1;         //随机数取余数，确保iX小于（X-2）+1 
			//g_pHead1->stSnake.iY=rand()%(Y-iCount-1)+3;  //随机数取余数，确保iY小于（Y-iCount）+1
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
		//记录被删除的节点
		struct Node* pp = pT;
		//节点往下走 
		pT = pT->pNext;
		//释放记录 
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
		//记录被删除的节点
		struct Node* pp1 = pT1;
		//节点往下走 
		pT1 = pT1->pNext;
		//释放记录 
		free(pp1);
	}
	g_pHead1 = NULL;
	g_pEnd1 = NULL;
}

void Frame(void)											//边框赋值 
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
				printf("■ ");

			else
				printf("  ");
		}
		putchar('\n');
	}
}


void Head(void)												//提示文字 
{
	printf("\n\n\t\t\t\t\t>>>>>>>>>>  贪吃蛇  <<<<<<<<<<\n");
	//printf("\t\t\t\t\t>>>>>  Enter 启动/暂停   <<<<<\n");
	printf("\t\t\t\t\t>>>>> ↑←↓→ 控制p1方向    <<<<<\n");
	printf("\t\t\t\t\t>>>>>  wsad控制p2方向    <<<<<\n");
	//printf("\t\t\t\t\t>>>>>   Q 重新开始       <<<<<\n");
	//printf("\t\t\t\t\t>>>>> tab 切换难度: 简单 <<<<<\n");
	printf("\t\t\t\t\t>>>>>    p1当前长度: %d   <<<<<\n",iCount);
	printf("\t\t\t\t\t>>>>>    p2当前长度: %d   <<<<<\n",iCount1);
	printf("\t\t\t\t\t>>>>>   ESC  退出游戏    <<<<<\n");
	printf("\t\t\t\t\t>>>>>>>>>>>>>>><<<<<<<<<<<<<<<\n");
}

/*void Change(void)   //目前无用
{
	static int g = 1;

	switch (g % 3)
	{
	case 1:  //中等
		GotoXY(5, 60);
		g_speed = 350;
		printf("中等");
		break;
	case 2:  //困难
		GotoXY(5, 60);
		g_speed = 200;
		printf("困难");
		break;
	case 0:  //简单
		GotoXY(5, 60);
		g_speed = 500;
		printf("简单");
	}
	g++;
}*/