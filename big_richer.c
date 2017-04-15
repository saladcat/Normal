#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <time.h>


#define MAXIMUS 11 //�������̴�С
#define SLARY 10000
#define PLAYERS 4

int p[MAXIMUS][MAXIMUS];//�洢������Ϣ
char buff[MAXIMUS * 3 + 1][MAXIMUS * 6 + 1] = { 0 };//���������
int Cx, Cy;//��ǰ���λ��
int Now;//��ǰ�����
int wi = 0, wj = 0;//��ǰд�뻺����������������λ��
char* showText;//������������ʾ��������Ϣ
char* showAnwser;//������������ʾ��������Ϣ

int count;//�غ���
int money[PLAYERS] = { 0 };
int wherePlayer[4][2] = { { 1,1 },{ 1,9 },{ 9,9 },{ 9,1 } };

void Initialize(void);
void doStep(int player);
int buyHouse(int i, int j, int player);
int check(int i, int j, int player);
int getWiner(void);
int runGame(void);
void setPan(void);
void setSqr(void);
void showGame(void);
char* delStr0(char* strDest, const char* string);
void setSpace(void);

void nextLine(int n)//���������1Ϊ��һ����ͬλ�ã�0Ϊ��һ����ʼλ��
{
	if (n == 1)
	{
		wi++;
	}
	else if (n == 0)
	{
		wi++;
		wj = 0;
	}
	else
		printf("nextLine()WRONG!");
}


int main(void)
/*{
system("title ���������� ����Etsnarl����");//���ñ���
system("mode con cols=63 lines=32");//���ô��ڴ�С
system("color E0");//������ɫ
runGame();
return 0;
}*/
{
	system("title ���������� ����Etsnarl����");//���ñ���
	system("mode con cols=100 lines=40");//���ô��ڴ�С
	system("color E0");//������ɫ
	setPan();
	showGame();
	return 0;
}
void Initialize(void)//��ʼ��һ���Ծֺ���
{
	int i, j, e;
	for (e = 0; e < PLAYERS; e++)
	{
		money[e] = SLARY;
	}

	for (i = 0; i < MAXIMUS; i++)//���öԾ�����
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

void doStep(int player) //����ѡ�ֱ�ţ�Ȼ���ҵ�ѡ�ֽ����ƶ�
{
	int step, count = 0, i, j, i1, j1;//�����޸ĵĸ���
	i = wherePlayer[player - 1][0];
	j = wherePlayer[player - 1][1];
	srand(time(NULL));
	step = (rand() % 6 + 1);
	while (count < step)
	{
		if (i >= 1 && i < 9 && j == 1)//��·
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
	wherePlayer[player - 1][0] = i;
	wherePlayer[player - 1][1] = j;

}

int buyHouse(int i, int j, int player) //��ұ��+10˵�����ӱ��������
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

int check(int i, int j, int player)
{

	int input;
	input = getch();
	if (input == ' ')
	{
		if (p[i][j] == 9)
		{
			showText = "����û�����ˣ������Ƿ�Ҫ����";
			showAnwser = "����y���򻨷�һǧԪ������n������";
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

		else if (p[i][j] >= 10)
		{
			money[player] -= 500;
			money[p[i][j] - 21] += 300;
			showText = "�㱻��ٵ�500��Ǯ";
			showAnwser = "���ӵ����˵õ�300��Ǯ��ʣ�µĽ�˰�ˣ�";
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
			showText = "���������Ϸ";
			return i + 1;
		}
	}
	return 0;
}

int runGame(void)
{
	int player = 1, result;
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
			showText = "����һλ�����·";
		else
		{
			showAnwser = "��Ϸ����";
			return 0;
		}
	}
}



void setSqr(void)//��wi,wjΪ���Ͻ���һ������
{
	delStr0(&buff[wi][wj], "��  ��");
	wi += 1;
	delStr0(&buff[wi][wj], "      ");
	wi += 1;
	delStr0(&buff[wi][wj], "��  ��");
	wi -= 2;
	wj += 6;
}

void setSpace(void)
{
	delStr0(&buff[wi][wj], "      ");
	wi += 1;
	delStr0(&buff[wi][wj], "      ");
	wi += 1;
	delStr0(&buff[wi][wj], "      ");
	wi -= 2;
	wj += 6;
}

void setPan(void)
{
	int i;
	for (i = 0; i < MAXIMUS; i++)
	{
		setSqr();
	}
	for (i = 0, wi = 3, wj = 0; i < 9; wi += 3, i++, wj = 0)
	{
		setSqr();
		for (int e = 1; e < MAXIMUS - 1; e++)
		{
			setSpace();
		}
		setSqr();
	}
	for (i = 0, wi = 30, wj = 0; i < MAXIMUS; i++)
	{
		setSqr();
	}
}



void showGame(void)
{
	int i;
	for (i = 0; i < MAXIMUS * 3 + 1; i++)
	{
		printf("%s", buff[i]);
		putchar('\n');
	}

}


char* delStr0(char* strDest, const char* string)
{
	char* pz = strDest;
	while (*string != '\0')
	{
		*strDest++ = *string++;
	}
	return pz;

}
