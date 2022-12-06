#define _CRT_SECURE_NO_WARNINGS 1
#include"game.h"


int IsOver(char arr[][15])
{
	int count = 0;
	for (int i = 0; i < 15;i++)
	for (int j = 0; j < 15;j++)
	if (arr[i][j] == '0') count = 1;
	if (count == 0)
	{
		MessageBox(NULL, TEXT("打成这样我是没想到的"), TEXT("关闭该窗口后返回到菜单栏"), MB_SYSTEMMODAL);
		Sleep(1000);
		closegraph();
		return 1;
	}
	return 0;
}

void DrawBoard(char arr[][15])
{
	//初始化棋盘
	for (int i = 0; i < 15;i++)
	for (int j = 0; j < 15; j++)
		arr[i][j] = '0';

	initgraph(800, 800);
	setbkcolor(RGB(222, 184, 135));
	cleardevice();
	setlinecolor(BLACK);
	for (int i = 50; i <= 750; i += 50)
	{
		line(50, i, 750, i);
		line(i, 50, i, 750);
	}
}

void DrawLine()
{
	setlinecolor(BLACK);
	for (int i = 50; i <= 750; i += 50)
	{
		line(50, i, 750, i);
		line(i, 50, i, 750);
	}
}

void DrawChess(char arr[][15])
{
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			if (arr[i][j] == '1')
			{
				setfillcolor(BLACK);
				solidcircle(50 + j * 50, 50 + i * 50, 12);
			}
			else if (arr[i][j] == '2')
			{
				setfillcolor(WHITE);
				solidcircle(50 + j * 50, 50 + i * 50, 12);
			}
		}
	}
}

//玩家黑棋走
void PPlay(char arr[][15], char* win, char** record, int* rec_count)
{
	int count = 10;
	ExMessage msg = { 0 };
	while (1)
	{
		Sleep(10);
		if (peekmessage(&msg, EM_MOUSE))//检测鼠标信息
		{
			if (msg.message == WM_LBUTTONDOWN)
			{
				for (int i = 0; i < 15; i++)
					for (int j = 0; j < 15; j++)
					{
						if (msg.x >= 35 + j * 50 && msg.x <= 65 + j * 50 && msg.y >= 35 + i * 50 && msg.y <= 65 + i * 50 && arr[i][j]=='0')
						{
							arr[i][j] = '1';
							*win = IsWin(arr, i, j);
							return;
						}
					}
			}
			if (count && msg.message == WM_LBUTTONDOWN && msg.x >= 5 && msg.x <= 70 && msg.y >= 0 && msg.y <= 40)
			{
				Regret(arr, record, rec_count);
				count--;
			}
		}
	}
}

//PVP中的白棋走
void CPlay(char arr[][15], char* win, char** record, int* rec_count)
{
	int count = 10;//最多悔几步
	ExMessage msg = { 0 };
	while (1)
	{
		Sleep(10);
		if (peekmessage(&msg, EM_MOUSE))//检测鼠标信息
		{
			if (msg.message == WM_LBUTTONDOWN)
			{
				for (int i = 0; i < 15; i++)
				for (int j = 0; j < 15; j++)
				{
					if (msg.x >= 35 + j * 50 && msg.x <= 65 + j * 50 && msg.y >= 35 + i * 50 && msg.y <= 65 + i * 50 && arr[i][j] == '0')
					{
						arr[i][j] = '2';
						*win = IsWin(arr, i, j);
						return;
					}
					
				}
			}
			if (count && msg.message == WM_LBUTTONDOWN && msg.x >= 5 && msg.x <= 70 && msg.y >= 0 && msg.y <= 40)
			{
				Regret(arr, record, rec_count);
				count--;
			}
		}
		
	}
}



//每下一个棋就调用该函数判断是否赢了，i和j为arr[i][j]中的下标。返回值0为没赢，1为黑棋赢，2为白棋赢。
char IsWin(char arr[][15],int i,int j)
{
	int flag = 0; //flag判断是否获胜，0为获胜
	const char value = arr[i][j];
	int x = j, y = i;
	//横向是否5子
	for (int a = x >= 4 ? x - 4 : 0; a <= x; a++)
	{
		flag = 0;
		for (int count = 0; count < 5; count++)
		{
			if (arr[i][a + count] != value)
			{
				flag = -1;  //-1代表没有获胜
				break;
			}		
		}
		if (flag == 0)
			return value;
	}
	//纵向是否5子
	for (int a = y >= 4 ? y - 4 : 0; a <= y; a++)
	{
		flag = 0;
		for (int count = 0; count < 5; count++)
		{
			if (arr[a+count][j] != value)
			{
				flag = -1;  //-1代表没有获胜
				break;
			}
		}
		if (flag == 0)
			return value;
	}

	//  \方向是否5子，此处遍历整行
	int det = x < y ? x : y;
	while (x-det+4 <= 14 && y-det+4 <= 14) //没到头就继续循环
	{
		flag = 0;
		for (int count = 0; count < 5; count++)
		{
			if (arr[y-det+count][x-det+count] != value)
			{
				flag = -1;  //-1代表没有获胜
				break;
			}
		}
		if (flag == 0)
			return value;
		det--;
	}

	//   /方向是否5子，此处遍历整行
	det = 15-x < y ? 15-x : y;
	while (x + det  -4 >= 0 && y - det + 4 <= 14) //没到头就继续循环
	{
		flag = 0;
		for (int count = 0; count < 5; count++)
		{
			if (arr[y - det + count][x + det - count] != value)
			{
				flag = -1;  //-1代表没有获胜
				break;
			}
		}
		if (flag == 0)
			return value;
		det--;
	}

	return '0';
}

void PrintWinner(char* win)
{
	Sleep(500);
	if (*win == '1')
		MessageBox(NULL, TEXT("黑棋赢了"), TEXT("胜负已分"), MB_SYSTEMMODAL);//最后一个参数使窗口在最前面

	else
		MessageBox(NULL, TEXT("白棋赢了"), TEXT("胜负已分"), MB_SYSTEMMODAL);
}

//将棋子数据写入数组
void LoadRecord(char arr[15][15],char** record,int* rec_count)
{
	for (int i = 0; i < 15;i++)
	for (int j = 0; j < 15; j++)
	{
		**record = arr[i][j];
		(*record)++;
	}
	(*rec_count)++;
}


void Regret(char arr[][15], char** record,int*rec_count)
{
	if (*rec_count > 2)
	{
		*(record) -= 675;
		for (int i = 0; i < 15;i++)
		for (int j = 0; j < 15; j++)
		{
			arr[i][j] = **record;
			(*record)++;
		}
		(*rec_count) -= 2;
		cleardevice();
		DrawLine();
		DrawChess(arr);
		settextstyle(20, 0, L"楷体");
		outtextxy(10, 10, L"悔棋");
	}
	return;
}

//将数组数据写入文件
void RecordInText(char**record, int* rec_count)
{
	int n;
	char file_name[20] = {'0'};
	printf("是否记录本次棋局？1.记录 0.不记录\n");//输入其他默认为记录
	scanf("%d", &n);
	if (n)
	{
		*record -= 225;  //将指针移动到最后一次下棋的数据前
		FILE* fp;
		while (file_name[0] == '0') //当文件名不符合要求就循环
		{
			printf("请输入文件名字\n");
			strcat(file_name, ".txt");
			scanf("%s", &file_name);
			if (file_name[0] == '0');//没输入不做任何事，继续循环
			else if ((fp = fopen(file_name, "r")) == NULL)  //输入了且文件名不冲突就创建文件并写入
			{
				printf("please wait...\n");
				fp = fopen(file_name, "w");
				while (*rec_count) //数据写完之前循环
				{
					for (int i = 0; i < 225; i++)  
						fputc(*((*record) + i), fp);
					(*rec_count)--;		
					(*record) -= 225;
				}
				//释放相关空间并关闭文件
				fclose(fp);
				fp = NULL;
				*record = 0;
				free(*record);
				*record = NULL;
			}
			else
			{
				printf("文件已存在，请重新输入\n");
				for (int i = 0; i < 20; i++)
					file_name[i] = '0';  //将文件名置为0使其继续循环
			}	
		}
	}
	else//不记录就释放
	{
		*record = 0;
		free(*record);
		*record = NULL;
	}
}


void PVP(char arr[][15], char* win, char** record, int* rec_count)
{
	DrawBoard(arr);
	settextstyle(20, 0, L"楷体");
	outtextxy(10, 10, L"悔棋");
	outtextxy(100, 10, L"该  走了");
	while (1)
	{
		Sleep(10);
		outtextxy(100, 10, L"该  走了");
		setfillcolor(BLACK);
		solidcircle(130,20,10);
		PPlay(arr,win,record,rec_count);
		LoadRecord(arr, record, rec_count);
		DrawChess(arr);
		if (IsOver(arr)) return;
		if (*win !='0')
		{
			PrintWinner(win);
			closegraph();
			RecordInText(record, rec_count);
			return;
		}
		Sleep(10);
		outtextxy(100, 10, L"该  走了");
		setfillcolor(WHITE);
		solidcircle(130, 20, 10);
		CPlay(arr,win,record,rec_count);
		LoadRecord(arr, record, rec_count);
		DrawChess(arr);
		if (*win != '0')
		{
			PrintWinner(win);
			closegraph();
			RecordInText(record, rec_count);
			return;
		}
	}
	
}

void DrawHint()
{
	settextstyle(20, 0, L"楷体");//设置字体形式（高度，宽度，字体）
	//setbkmode(TRANSPARENT);//考虑到文字背景也有默认颜色，可能发生遮挡，所以将文字背景改为透明
	outtextxy(10, 10, L"上一步");//指定位置打印字符串
	outtextxy(80, 10, L"下一步");//指定位置打印字符串
	outtextxy(700, 10, L"退出");
}

void ShowRecord(char arr[][15])
{
	char file_name[20] = { '0' };
	printf("请输入记录的文件名，输入0退出\n");
	scanf("%s", &file_name);
	if (file_name[0] != '0')
	{
		FILE* fp;
		if ((fp = fopen(file_name, "r")) == NULL)
		{
			printf("文件不存在，读取失败。按回车返回\n");
			getchar();
			getchar();
		}
		else
		{
			fp = fopen(file_name, "r");
			DrawBoard(arr);
			DrawLine();
			DrawHint();
			for (int i = 0; i < 15; i++)
			for (int j = 0; j < 15; j++)
			{
				arr[i][j] = fgetc(fp);
			}
			DrawChess(arr);



			while (1)//(fgetc(fp) != EOF)
			{
				//fseek(fp, -1, SEEK_CUR);
				ExMessage msg = { 0 };


				if (peekmessage(&msg, EM_MOUSE))//检测鼠标信息
				{
					if (msg.message == WM_LBUTTONDOWN && msg.x >= 5 && msg.x <= 70 && msg.y >= 0 && msg.y <= 40)
					{
						BeginBatchDraw();
						cleardevice();
						DrawLine();
						DrawHint();
						for (int i = 0; i < 15; i++)
						for (int j = 0; j < 15; j++)
						{
							arr[i][j] = fgetc(fp);
						}
						DrawChess(arr);
						EndBatchDraw();
					}


					else if (msg.message == WM_LBUTTONDOWN && msg.x >= 80 && msg.x <= 140 && msg.y >= 0 && msg.y <= 40)
					{
						if (ftell(fp) < 450)
							continue;
						BeginBatchDraw();
						cleardevice();
						DrawLine();
						DrawHint();
						fseek(fp, -450, SEEK_CUR);
						for (int i = 0; i < 15; i++)
						for (int j = 0; j < 15; j++)
						{
							arr[i][j] = fgetc(fp);
						}
						DrawChess(arr);
						EndBatchDraw();
					}
					else if (msg.message == WM_LBUTTONDOWN && msg.x >= 690 && msg.x <= 750 && msg.y >= 0 && msg.y <= 40)
					{
						break;
					}
				}
				
				Sleep(10);
			}
			closegraph();
		}
	}
}

