#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <time.h>


#define MAXIMUS 11 //定义棋盘大小
#define SLARY 10000
#define PLAYERS 4

int p[MAXIMUS][MAXIMUS];//存储房屋信息
//char buff[MAXIMUS * 2 + 1][MAXIMUS * 4 + 1];//输出缓冲器
int Cx, Cy;//当前光标位置
int Now;//当前的玩家
//int wi, wj;//当前写入缓冲器的列数和行数位置
char* showText;//在棋盘中央显示的文字信息
char* showAnwser;//在棋盘中央显示的文字信息

int count;//回合数
int money[PLAYERS] = { 0 };
int wherePlayer[4][2] = { {1,1}, {1,9}, {9,9}, {9,1} };

void Initialize(void);
void doStep(int player);
int buyHouse(int i, int j, int player);
int check(int i, int j, int player);
int getWiner(void);
int runGame(void);

int main(void)
{
	system("title 简易五子棋 ——Etsnarl制作");//设置标题
	system("mode con cols=63 lines=32");//设置窗口大小
	system("color E0");//设置颜色
	runGame();
	return 0;
}
void Initialize(void)//初始化一个对局函数
{
	int i, j, e;
	for (e =0; e < PLAYERS; e++)
	{
		money[e] = SLARY;
	}

	for (i = 0; i < MAXIMUS; i++)//重置对局数据
	{
		for (j = 0; j < MAXIMUS; j++)
		{
			if (i == 1 || i == 9 || j == 1 || j == 9)
				p[i][j] = 9;
			else
				p[i][j] = 0;
		}
	}

}

void doStep(int player) //输入选手编号，然后找到选手进行移动
{
	int step,count=0,i,j,i1,j1;//可以修改的更好
	i = wherePlayer[player-1][0];
	j = wherePlayer[player-1][1];
	srand(time(NULL));
	step = (rand() % 6 + 1);
	while (count < step)
	{
		if (i >= 1 && i < 9 && j == 1)//走路
		{
			i1 = i + 1;
			j1 = j;
		}
		else if (i == 9 && j >= 1 && j < 9)
		{
			i1 = i;
			j1 = j + 1;
		}
		else if (i <= 9 && j == 9 && i > 1)
		{
			i1 = i - 1;
			j1 = j;
		}
		else if (i == 1 && j <= 9 && j > 1)
		{
			i1 = i;
			j1 = j - 1;
		}
		i = i1;
		j = j1;
		count++;
	}
	wherePlayer[player - 1][0]=i;
	wherePlayer[player - 1][1]=j;
	
}

int buyHouse(int i, int j,int player) //玩家编号+20说明房子被玩家买了
{
	if (p[i][j] == 9 && money[player - 1] > 1000)
	{
		money[player - 1] -= 1000;
		p[i][j] = player + 20;
		return 1;
	}
	else
		return 0;
}

int check(int i, int j,int player)
{

	int input;
	input = getch();
	if (input == ' ')
	{
		if (p[i][j] == 9)
		{
			showText = "这块地没有主人，请问是否要购买";
			showAnwser = "按下y购买花费一千元，按下n不购买";
			input = getch();
			while (1)
			{
				if (input == 'y')
				{
					buyHouse(i, j, player);
					break;
				}
				else if (input == 'n')
					break;
				else
					input = getch();
			}
			return 1;
		}

		else if (p[i][j] >= 20)
		{
			money[player] -= 500;
			money[p[i][j] - 21] += 300;
			showText = "你被打劫掉500块钱";
			showAnwser = "房子的主人得到300块钱（剩下的交税了）";
			return 1;
		}

		else
			printf("check() WRONG!");
		return 0;
	}
}

int getWiner(void)
{
	int i;
	for (i = 0; i < PLAYERS; i++)
	{
		if (money[i] <= 0)
		{
			showText = "你输掉了游戏";
			return i + 1;
		}
	}
	return 0;
}

int runGame(void)
{
	int player=1,result;
	Initialize();
	while (1)
	{
		doStep(player);
		check(wherePlayer[player - 1][0], wherePlayer[player - 1][1], player);
		result = getWiner();
		player += 1;
		if (player == 5)
			player = 1;

		if (result == 0)
			showText = "请下一位玩家走路";
		else
		{
			showAnwser = "游戏结束";
			return 0;
		}
	}
}

