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
		MessageBox(NULL, TEXT("�����������û�뵽��"), TEXT("�رոô��ں󷵻ص��˵���"), MB_SYSTEMMODAL);
		Sleep(1000);
		closegraph();
		return 1;
	}
	return 0;
}

void DrawBoard(char arr[][15])
{
	//��ʼ������
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

//��Һ�����
void PPlay(char arr[][15], char* win, char** record, int* rec_count)
{
	int count = 10;
	ExMessage msg = { 0 };
	while (1)
	{
		Sleep(10);
		if (peekmessage(&msg, EM_MOUSE))//��������Ϣ
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

//PVP�еİ�����
void CPlay(char arr[][15], char* win, char** record, int* rec_count)
{
	int count = 10;//���ڼ���
	ExMessage msg = { 0 };
	while (1)
	{
		Sleep(10);
		if (peekmessage(&msg, EM_MOUSE))//��������Ϣ
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



//ÿ��һ����͵��øú����ж��Ƿ�Ӯ�ˣ�i��jΪarr[i][j]�е��±ꡣ����ֵ0ΪûӮ��1Ϊ����Ӯ��2Ϊ����Ӯ��
char IsWin(char arr[][15],int i,int j)
{
	int flag = 0; //flag�ж��Ƿ��ʤ��0Ϊ��ʤ
	const char value = arr[i][j];
	int x = j, y = i;
	//�����Ƿ�5��
	for (int a = x >= 4 ? x - 4 : 0; a <= x; a++)
	{
		flag = 0;
		for (int count = 0; count < 5; count++)
		{
			if (arr[i][a + count] != value)
			{
				flag = -1;  //-1����û�л�ʤ
				break;
			}		
		}
		if (flag == 0)
			return value;
	}
	//�����Ƿ�5��
	for (int a = y >= 4 ? y - 4 : 0; a <= y; a++)
	{
		flag = 0;
		for (int count = 0; count < 5; count++)
		{
			if (arr[a+count][j] != value)
			{
				flag = -1;  //-1����û�л�ʤ
				break;
			}
		}
		if (flag == 0)
			return value;
	}

	//  \�����Ƿ�5�ӣ��˴���������
	int det = x < y ? x : y;
	while (x-det+4 <= 14 && y-det+4 <= 14) //û��ͷ�ͼ���ѭ��
	{
		flag = 0;
		for (int count = 0; count < 5; count++)
		{
			if (arr[y-det+count][x-det+count] != value)
			{
				flag = -1;  //-1����û�л�ʤ
				break;
			}
		}
		if (flag == 0)
			return value;
		det--;
	}

	//   /�����Ƿ�5�ӣ��˴���������
	det = 15-x < y ? 15-x : y;
	while (x + det  -4 >= 0 && y - det + 4 <= 14) //û��ͷ�ͼ���ѭ��
	{
		flag = 0;
		for (int count = 0; count < 5; count++)
		{
			if (arr[y - det + count][x + det - count] != value)
			{
				flag = -1;  //-1����û�л�ʤ
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
		MessageBox(NULL, TEXT("����Ӯ��"), TEXT("ʤ���ѷ�"), MB_SYSTEMMODAL);//���һ������ʹ��������ǰ��

	else
		MessageBox(NULL, TEXT("����Ӯ��"), TEXT("ʤ���ѷ�"), MB_SYSTEMMODAL);
}

//����������д������
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
		settextstyle(20, 0, L"����");
		outtextxy(10, 10, L"����");
	}
	return;
}

//����������д���ļ�
void RecordInText(char**record, int* rec_count)
{
	int n;
	char file_name[20] = {'0'};
	printf("�Ƿ��¼������֣�1.��¼ 0.����¼\n");//��������Ĭ��Ϊ��¼
	scanf("%d", &n);
	if (n)
	{
		*record -= 225;  //��ָ���ƶ������һ�����������ǰ
		FILE* fp;
		while (file_name[0] == '0') //���ļ���������Ҫ���ѭ��
		{
			printf("�������ļ�����\n");
			strcat(file_name, ".txt");
			scanf("%s", &file_name);
			if (file_name[0] == '0');//û���벻���κ��£�����ѭ��
			else if ((fp = fopen(file_name, "r")) == NULL)  //���������ļ�������ͻ�ʹ����ļ���д��
			{
				printf("please wait...\n");
				fp = fopen(file_name, "w");
				while (*rec_count) //����д��֮ǰѭ��
				{
					for (int i = 0; i < 225; i++)  
						fputc(*((*record) + i), fp);
					(*rec_count)--;		
					(*record) -= 225;
				}
				//�ͷ���ؿռ䲢�ر��ļ�
				fclose(fp);
				fp = NULL;
				*record = 0;
				free(*record);
				*record = NULL;
			}
			else
			{
				printf("�ļ��Ѵ��ڣ�����������\n");
				for (int i = 0; i < 20; i++)
					file_name[i] = '0';  //���ļ�����Ϊ0ʹ�����ѭ��
			}	
		}
	}
	else//����¼���ͷ�
	{
		*record = 0;
		free(*record);
		*record = NULL;
	}
}


void PVP(char arr[][15], char* win, char** record, int* rec_count)
{
	DrawBoard(arr);
	settextstyle(20, 0, L"����");
	outtextxy(10, 10, L"����");
	outtextxy(100, 10, L"��  ����");
	while (1)
	{
		Sleep(10);
		outtextxy(100, 10, L"��  ����");
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
		outtextxy(100, 10, L"��  ����");
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
	settextstyle(20, 0, L"����");//����������ʽ���߶ȣ���ȣ����壩
	//setbkmode(TRANSPARENT);//���ǵ����ֱ���Ҳ��Ĭ����ɫ�����ܷ����ڵ������Խ����ֱ�����Ϊ͸��
	outtextxy(10, 10, L"��һ��");//ָ��λ�ô�ӡ�ַ���
	outtextxy(80, 10, L"��һ��");//ָ��λ�ô�ӡ�ַ���
	outtextxy(700, 10, L"�˳�");
}

void ShowRecord(char arr[][15])
{
	char file_name[20] = { '0' };
	printf("�������¼���ļ���������0�˳�\n");
	scanf("%s", &file_name);
	if (file_name[0] != '0')
	{
		FILE* fp;
		if ((fp = fopen(file_name, "r")) == NULL)
		{
			printf("�ļ������ڣ���ȡʧ�ܡ����س�����\n");
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


				if (peekmessage(&msg, EM_MOUSE))//��������Ϣ
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

