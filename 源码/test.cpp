#define _CRT_SECURE_NO_WARNINGS 1
#include"game.h"
//char* record = (char*)malloc(sizeof(char)* (15 * 15 * 225));
int rec_count = 0;
char arr[15][15] = { '0' };//用来存放棋子。1为黑棋，2为白棋。
char win = '0';//是否有人获胜
//IMAGE menu_png;
void begin()
{
	//loadimage(&menu_png, L"menu.png", 590, 590);
	initgraph(600, 600);
	//putimage(0, 0, &menu_png);
	setbkcolor(RGB(222, 184, 135));
	cleardevice();
	setlinecolor(BLACK);
	line(100, 0, 100, 600);
	line(200, 0, 200, 600);
	line(300, 0, 300, 600);
	line(400, 0, 400, 600);
	line(500, 0, 500, 600);
	line(0, 100, 600, 100);
	line(0, 200, 600, 200);
	line(0, 300, 600, 300);
	line(0, 400, 600, 400);
	line(0, 500, 600, 500);
	setfillcolor(WHITE);
	solidcircle(300,300, 30);
	solidcircle(400, 300, 30);
	solidcircle(500, 300, 30);
	solidcircle(300, 200, 30);
	solidcircle(200, 200, 30);
	setfillcolor(BLACK);
	solidcircle(200, 300, 30);
	solidcircle(600, 300, 30);
	solidcircle(500, 400, 30);
	settextstyle(40, 20, L"楷体");//设置字体形式（高度，宽度，字体）
	outtextxy(0, 0, L"人人对战");//160 40
	outtextxy(0, 40, L"人机对战");
	outtextxy(0, 80, L"加载记录");
	outtextxy(0, 120, L"退出游戏");
	outtextxy(0, 160, L"机机对战");

}

void Init()
{
	for (int i = 0; i < 15; i++)
	for (int j = 0; j < 15; j++)
		arr[i][j] = '0';
	win = '0';
	rec_count = 0;
}


int main()
{
	int graph = 0;
	int choice=-1;
	ExMessage msg = { 0 };
	while (1)
	{
		if (!graph)
		{
			graph = 1;
			begin();
		}
		Sleep(10);
		if (peekmessage(&msg, EM_MOUSE))//检测鼠标信息
		{
			if (msg.message == WM_LBUTTONDOWN)
			{
				if (msg.x >= 0 && msg.x <= 160 && msg.y >= 0 && msg.y <= 40)
				{
					choice = 1;
				}
				if (msg.x >= 0 && msg.x <= 160 && msg.y >= 40 && msg.y <= 80)
				{
					choice = 2;
				}
				if (msg.x >= 0 && msg.x <= 160 && msg.y >= 80 && msg.y <= 120)
				{
					choice = 3;
				}
				if (msg.x >= 0 && msg.x <= 160 && msg.y >= 120 && msg.y <= 160)
				{
					choice = 0;
				}
				if (msg.x >= 0 && msg.x <= 160 && msg.y >= 160 && msg.y <= 200)
				{
					choice = 4;
				}
			}
			//case 1   PVP
			if (choice == 1)
			{
				closegraph();
				graph = 0;
				char* record = (char*)malloc(sizeof(char)* (15 * 15 * 225));  //开拓内存空间存放每一步的棋盘数据，方便之后写入文件。
				for (int i = 0; i < 15 * 15 * 225; i++)
					*(record + i) = '0';
				PVP(arr, &win, &record, &rec_count);
				choice = -1;
				Init();
			}

			//case 3 复盘
			else if (choice == 3)
			{
				closegraph();
				graph = 0;
				ShowRecord(arr);
				choice = -1;
				Init();

			}

			// case 2 人机对战(简单)
			else if (choice == 2)
			{
				closegraph();
				graph = 0;
				char* record = (char*)malloc(sizeof(char)* (15 * 15 * 225));
				BVP(arr, &win, &record, &rec_count);
				choice = -1;
				Init();
			}


			else if (choice == 4)
			{
				closegraph();
				graph = 0;
				char* record = (char*)malloc(sizeof(char)* (15 * 15 * 225));
				BVB(arr, &win, &record, &rec_count);
				choice = -1;
				Init();
			}

			else if (choice == 0)
			{
				closegraph();
				graph = 0;
				break;
			}
		}
	}
	return 0;
}