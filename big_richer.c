#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <time.h>


#define MAXIMUS 10 //定义棋盘大小
#define SLARY 10000
#define PLAYERS 4

int p[MAXIMUS][MAXIMUS];//存储房屋信息
char buff[MAXIMUS * 3 + 1][MAXIMUS * 6 + 1] = { 0 };//输出缓冲器
int wi=0, wj=0;//当前写入缓冲器的列数和行数位置
char* showText="大富翁！！";
char* showAnwser="游戏开始！按空格走路";
char* tip1 = "大写字母为可以移动的人";
char* tip2 = "小写字母为买了的房子";
char* tip3 = "买房子1000，被打劫500，打劫300";
int count=0;//回合数
int money[PLAYERS] = { 0 };
int wherePlayer[4][2] = { {1,1}, {1,9}, {9,9}, {9,1} };

void Initialize(void);
void doStep(int player);
int buyHouse(int i, int j, int player);
int check(int i, int j, int player);
int getWiner(void);
int runGame(void);
void setPan(void);
void setSqr(void);
void showGame(void); 
char* copyStr(char* strDel , const char* string);
void setSpace(void);
void setWord(void);
void setPlayer(void);
void setWhose(void);

int main(void)
{
	system("title 简易大富翁");//设置标题
	system("mode con cols=70 lines=34");//设置窗口大小
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

int buyHouse(int i, int j,int player) //玩家编号+10说明房子被玩家买了
{
	if (p[i][j] == 9 && money[player - 1] > 1000)
	{
		money[player - 1] -= 1000;
		p[i][j] = player + 10;
		return 1;
	}
	else
		return 0;
}

int check(int i, int j,int player)
{

	int input;
	while (1)//嵌套太多了，可以改进
	{
		showGame();
		input = getch();
		if (input == ' ')
		{
			setPan();
			setWord();
			setWhose();
			setPlayer();
			showGame();
			if (p[i][j] == 9)
			{
				showText = "这块地没有主人，请问是否要购买";
				showAnwser = "按下y购买，花费一千元，按下n不购买";
				setWord();
				showGame();
				input = getch();
				while (1)
				{
					if (input == 'y')
					{
						showText = "您购买了这块土地！         ";
						showAnwser = "请下一个玩家操作        ";
						setWord();
						showGame();
						buyHouse(i, j, player);
						break;
					}
					else if (input == 'n')
					{
						showText = "您没有购买这块土地！          ";
						showAnwser = "请下一个玩家操作            ";
						setWord();
						showGame();
						break;
					}
					else
					{
						showText = "请重新                          ";
						showAnwser = "输入                               ";
						setWord();
						showGame();
						input = getch();
					}
				}
			}
			else if (p[i][j] >= 10)
			{
				money[player-1] -= 500;
				money[p[i][j] - 11] += 300;
				showText = "你被打劫掉500块钱";
				showAnwser = "房子的主人得到300块钱（剩下的交税了）";
				setWord();
				showGame();
				return 1;
			}
			else
				printf("check() WRONG!");
			return 0;
		}
		else
		{
			showText = "等待";
			showAnwser = "请按下空格";
			showGame();
		}
	}
}

int getWiner(void)
{
	int i;
	for (i = 0; i < PLAYERS; i++)
	{
		if (money[i] <= 0)
		{
			showText = "你输掉了游戏               ";
			setWord();
			return i + 1;
		}
	}
	return 0;
}

int runGame(void)
{
	int player=1,result;
	Initialize();
	setPan();
	while (1)
	{
		setPan();
		setWord();
		setWhose();
		setPlayer();
		showGame();
		doStep(player);
		check(wherePlayer[player - 1][0], wherePlayer[player - 1][1], player);
		result = getWiner();
		player += 1;
		count++;
		if (player == 5)
			player = 1;
		if (result == 0)
			;
		else
		{
			showAnwser = "游戏结束                              ";
			setWord();
			showGame();
			return 0;
		}
	}
}

void setSqr(void)//以wi,wj为左上角做一个方块
{
		copyStr(&buff[wi][wj], "┏  ┓");
		wi += 1;
		copyStr(&buff[wi][wj], "      ");
		wi += 1;
		copyStr(&buff[wi][wj], "┗  ┛");
		wi -= 2;
		wj += 6;
}

void setSpace(void)
{
	copyStr(&buff[wi][wj], "      ");
	wi += 1;
	copyStr(&buff[wi][wj], "      ");
	wi += 1;
	copyStr(&buff[wi][wj], "      ");
	wi -= 2;
	wj += 6;
}

void setPan(void)
{
	int i;
	wi = 0, wj = 0;
	for (i = 0; i < 9; i++)//重复用自身覆盖掉'\0'
	{
		setSqr();
	}
	for (i = 0, wi = 3, wj = 0; i < 8; wi += 3, i++, wj = 0)
	{
		setSqr();
			for (int e = 1; e < 8; e++)
			{
			setSpace(); 
			}
		setSqr();
	}
	for (i = 0,wi = 24,wj=0; i < 9; i++)
	{
		setSqr();
	}
}

void setWord(void)
{
	wi = 4;
	wj = 8;
	copyStr(&buff[wi][wj], tip1);
	wi = 5;
	wj = 8;
	copyStr(&buff[wi][wj], tip2);
	wi = 6;
	wj = 8;
	copyStr(&buff[wi][wj], tip3);
	wj = 8;// 还没保证在中间
	wi = 12;
	copyStr(&buff[wi][wj], showText);
	wj = 8 ;
	wi = 15;
	copyStr(&buff[wi][wj], showAnwser);
}

void setPlayer(void)
{
	int i;
	for (i = 0; i < PLAYERS; i++)
	{
		wi = (wherePlayer[i][0]-1) * 3 + 1;
		wj = (wherePlayer[i][1]-1) * 6 + 3;
		buff[wi][wj] = 'A'+i;
	}
}

void setWhose(void)
{
	int i, j;
	for (i = 0; i < MAXIMUS; i++)
	{
		for (j = 0; j < MAXIMUS; j++)
		{
			wi = (i - 1) * 3 + 1;
			wj = (j - 1) * 6 + 2;
			if (p[i][j] == 9)
				buff[wi][wj] = ' ';
			else if (p[i][j] % 10 == 1)//用取余来确保以后可能的升级
				buff[wi][wj] = 'a';
			else if (p[i][j] % 10 == 2)
				buff[wi][wj] = 'b';
			else if (p[i][j] % 10 == 3)
				buff[wi][wj] = 'c';
			else if (p[i][j] % 10 == 4)
				buff[wi][wj] = 'd';
			else if (p[i][j] == 0)
				;
			else
				printf("setWho is WORONG!");
		}
	}

}

void showGame(void)
{
	int i;
	system("cls");
	for (i = 0; i < MAXIMUS*3+1; i++)
	{
		printf("%s", buff[i]);
		putchar('\n');
	}
	printf("A的钱有%d   ", money[0]);
	printf("B的钱有%d   ", money[1]);
	printf("C的钱有%d   ", money[2]);
	printf("D的钱有%d   \n", money[3]);
	printf("现在进行了%d个回合", count);
}

char* copyStr(char* strDel, const char* string)
{
	char* pz = strDel;
	while (*string != '\0')
	{
		*strDel++ = *string++;//复制除了\0的字符串
	}
	return pz;

}

