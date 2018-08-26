#include <stdio.h>
#include <random>
#include <time.h>
#include <stdlib.h>
#include <graphics.h>


#define WIDE 10
#define HIGH 10
#define NUM 10

IMAGE num0, num1, num2, num3, num4, num5, num6, num7, num8, mine, wall, flag;

int map[HIGH + 2][WIDE + 2] = { 0 };//ʵ�����̴�С

//����
void AmpushMine()
{
	srand((unsigned int)time(NULL));

	

	for (int i = 0; i < NUM; i++)
	{
		int mine_x = rand() % 10 + 1;
		int mine_y = rand() % 10 + 1;
		if (map[mine_x][mine_y] == 0)
		{
			map[mine_x][mine_y] = -1;
		}
		else
		{
			i--;
		}
	}

}

//������
void AmpushNum()
{
	for (int i = 1; i < HIGH + 1; i++)
	{
		for (int j = 1; j < WIDE + 1; j++)
		{
			if (map[j][i] != -1)
			{
				int temp_num = 0;
				for (int x = j - 1; x < j + 2; x++)
				{
					for (int y = i - 1; y < i + 2; y++)
					{
						if (map[x][y] == -1)
						{
							temp_num++;
						}
					}
				}
				map[j][i] = temp_num;
			}
		}

	}
}

//����ͼ����Դ
void LoadingImage()
{
	loadimage(&num0, L"./Images/num0.jpg");
	loadimage(&num1, L"./Images/num1.jpg");
	loadimage(&num2, L"./Images/num2.jpg");
	loadimage(&num3, L"./Images/num3.jpg");
	loadimage(&num4, L"./Images/num4.jpg");
	loadimage(&num5, L"./Images/num5.jpg");
	loadimage(&num6, L"./Images/num6.jpg");
	loadimage(&num7, L"./Images/num7.jpg");
	loadimage(&num8, L"./Images/num8.jpg");
	loadimage(&mine, L"./Images/mine.jpg");
	loadimage(&wall, L"./Images/wall.jpg");
	loadimage(&flag, L"./Images/flag.jpg");
}

//��ͼ
void ShowImage()
{
	for (int i = 1; i < HIGH + 1; i++)
	{
		for (int j = 1; j < WIDE + 1; j++)
		{
			switch (map[j][i])
			{
				// + 10
			case 9:putimage((j - 1) * 50, (i - 1) * 50, &mine); break;
			case 10:putimage((j - 1) * 50, (i - 1) * 50, &num0); break;
			case 11:putimage((j - 1) * 50, (i - 1) * 50, &num1); break;
			case 12:putimage((j - 1) * 50, (i - 1) * 50, &num2); break;
			case 13:putimage((j - 1) * 50, (i - 1) * 50, &num3); break;
			case 14:putimage((j - 1) * 50, (i - 1) * 50, &num4); break;
			case 15:putimage((j - 1) * 50, (i - 1) * 50, &num5); break;
			case 16:putimage((j - 1) * 50, (i - 1) * 50, &num6); break;
			case 17:putimage((j - 1) * 50, (i - 1) * 50, &num7); break;
			case 18:putimage((j - 1) * 50, (i - 1) * 50, &num8); break;
			default:
				if (map[j][i] > 18)//��ǣ���-1~8�ļ�20��19~28
				{
					putimage((j - 1) * 50, (i - 1) * 50, &flag);
				}
				else if (map[j][i] < 9)
				{
					putimage((j - 1) * 50, (i - 1) * 50, &wall);
				}
				break;
			}
			
		}
	}
}

//ɨ�ף���Ϸ�߼���
void SweepMine(int x, int y)
{
	if (x < 1 || y < 1 || x > 10 || y > 10)
	{
		return;
	}
	if (map[y][x] < 0)//������ף�������
	{
		return;
	}
	if (map[y][x] > 8)//�����û�з����������ѱ���ǣ��򲻲���
	{
		return;
	}
	map[y][x] += 10;
	if (map[y][x] == 10)//�����ǰ�������0����ʼ������Χɨ�ף��ݹ飩
	{
		
		for (int i = y - 1; i < y + 2; i++)//��
		{
			for (int j = x - 1; j < x + 2; j++)//��
			{
				SweepMine(j, i);
			}
		}
	}
	
}

//��ʼ��Ϸ����Ϸ�߼���
void PlayGame()
{
	MOUSEMSG mouse = GetMouseMsg();//��ȡ�����Ϣ

	for (int i = 1; i < HIGH + 1; i++)
	{
		for (int j = 1; j < WIDE + 1; j++)
		{
			if (mouse.mkLButton)//�ж��������Ƿ񱻰���
			{
				//�ж�������ķ�Χ
				if ((j - 1) * 50 < mouse.x && mouse.x < j * 50 && (i - 1) * 50 < mouse.y && mouse.y < i * 50)
				{
					SweepMine(i, j);
				}
			}
			else if (mouse.mkRButton)
			{
				//�ж�������ķ�Χ
				if ((j - 1) * 50 < mouse.x && mouse.x < j * 50 && (i - 1) * 50 < mouse.y && mouse.y < i * 50)
				{
					if (map[j][i] < 9)
					{
						map[j][i] += 20;
					}
					else if (map[j][i] > 18)
					{
						map[j][i] -= 20;
					}
				}
			}

		}
	}

	
}

int main(void)
{
	HWND windows = initgraph(WIDE * 50, HIGH * 50);//��������
	LoadingImage();//����ͼ��
	AmpushMine();//����
	AmpushNum();//������


	while (1)
	{
		ShowImage();
		PlayGame();
	}


	system("pause");
	return 0;
}