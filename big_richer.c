#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <time.h>


#define MAXIMUS 9 //�������̴�С
#define SLARY 10000
#define PLAYERS 4

int p[MAXIMUS][MAXIMUS];//�洢������Ϣ
char buff[MAXIMUS * 3 + 1][MAXIMUS * 6 + 1] = { 0 };//���������
int wi=0, wj=0;//��ǰд�뻺����������������λ��
char* showText="���̣���";
char* showAnwser="��Ϸ��ʼ�����ո���·";
char* tip1 = "��д��ĸΪ�����ƶ�����";
char* tip2 = "Сд��ĸΪ���˵ķ���";
char* tip3 = "����1000�������500�����300";
int count=0;//�غ���
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
char* delStr0(char* strDest, const char* string);
void setSpace(void);
void setWord(void);
void setPlayer(void);
void setWhose(void);

int main(void)
{
	system("title ���״���");//���ñ���
	system("mode con cols=70 lines=34");//���ô��ڴ�С
	system("color E0");//������ɫ
	runGame();
	return 0;
}

void Initialize(void)//��ʼ��һ���Ծֺ���
{
	int i, j, e;
	for (e =0; e < PLAYERS; e++)
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
	int step,count=0,i,j,i1,j1;//�����޸ĵĸ���
	i = wherePlayer[player-1][0];
	j = wherePlayer[player-1][1];
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
	wherePlayer[player - 1][0]=i;
	wherePlayer[player - 1][1]=j;
	
}

int buyHouse(int i, int j,int player) //��ұ��+10˵�����ӱ��������
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
	while (1)
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
				showText = "����û�����ˣ������Ƿ�Ҫ����";
				showAnwser = "����y���򣬻���һǧԪ������n������";
				setWord();
				showGame();
				input = getch();
				while (1)
				{
					if (input == 'y')
					{
						showText = "��������������أ�         ";
						showAnwser = "����һ����Ҳ���        ";
						setWord();
						showGame();
						buyHouse(i, j, player);
						break;
					}
					else if (input == 'n')
					{
						showText = "��û�й���������أ�          ";
						showAnwser = "����һ����Ҳ���            ";
						setWord();
						showGame();
						break;
					}
					else
					{
						showText = "������                          ";
						showAnwser = "����                               ";
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
				showText = "�㱻��ٵ�500��Ǯ";
				showAnwser = "���ӵ����˵õ�300��Ǯ��ʣ�µĽ�˰�ˣ�";
				return 1;
			}
			else
				printf("check() WRONG!");
			return 0;
		}
		else
		{
			showText = "�ȴ�";
			showAnwser = "�밴�¿ո�";
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
			showText = "���������Ϸ";
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
			showAnwser = "����һλ�����·";
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
	wi = 0, wj = 0;
	for (i = 0; i < 9; i++)
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
	delStr0(&buff[wi][wj], tip1);
	wi = 5;
	wj = 8;
	delStr0(&buff[wi][wj], tip2);
	wi = 6;
	wj = 8;
	delStr0(&buff[wi][wj], tip3);
	wj = 8;// ��û��֤���м�
	wi = 12;
	delStr0(&buff[wi][wj], showText);
	wj = 8 ;
	wi = 15;
	delStr0(&buff[wi][wj], showAnwser);
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
			else if (p[i][j] % 10 == 1)
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
	printf("A��Ǯ��%d   ", money[0]);
	printf("B��Ǯ��%d   ", money[1]);
	printf("C��Ǯ��%d   ", money[2]);
	printf("D��Ǯ��%d   \n", money[3]);
	printf("���ڽ�����%d���غ�", count);
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

