#define _CRT_SECURE_NO_WARNINGS 1
#include"game.h"
//#include<malloc.h>
//
int alpha, beta;
int bot_i, bot_j;

int FindSub(char*str, struct Shape Score_Shape[30])
{
	int sum = 0;
	char* local_str, *sub_str;
	char* local_local;
	for (int i = 0; i < 30; i++)
	{
		local_str = str;
		sub_str = Score_Shape[i].shape;
		//1-1
		while (*local_str)
		{
			local_local = local_str;
			sub_str = Score_Shape[i].shape;
			do
			{
				if (*sub_str == '\0')
				{
					sum+=Score_Shape[i].score;
					break;
				}
			} while (*local_local++ == *sub_str++); //没跳出来说明一直满足*local_local == *sub_str
			
			if (*(local_str + 1) == '\0') break;
			else local_str++;
		}
	}
	return sum;
}

int SearchRow(char arr[][15],struct Shape Score_Shape[30])
{
	int sum = 0;
	char* str = (char*)malloc(16 * sizeof(char));
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			str[j] = arr[i][j];
		}
		str[15] = '\0';
		sum += FindSub(str, Score_Shape);
	}
	free(str);
	return sum;
}

int SearchCol(char arr[][15], struct Shape Score_Shape[30])
{
	int sum = 0;
	char* str = (char*)malloc(16 * sizeof(char));
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			str[j] = arr[j][i];
		}
		str[15] = '\0';
		sum += FindSub(str, Score_Shape);
	}
	free(str);
	return sum;
}

int SearchMain(char arr[][15], struct Shape Score_Shape[30])
{
	int sum = 0;
	int count, i;
	//下三角
	char* str = (char*)malloc(16 * sizeof(char));
	for (int m = 10; m >= 0; m--)
	{
		count = 0;
		i = m;

		while (i < 15)
		{
			str[count] = arr[i][count];
			count++;
			i++;
		}
		str[count] = '\0';
		sum += FindSub(str, Score_Shape);
	}
	//上三角
	for (int m = 10; m >= 0; m--)
	{
		count = 0;
		i = m;
		while (i < 15)
		{
			str[count] = arr[count][i];
			count++;
			i++;
		}
		str[count] = '\0';
		sum += FindSub(str, Score_Shape);
		//free(str);
	}
	free(str);
	return sum;
}
int SearchVice(char arr[][15], struct Shape Score_Shape[30])
{
	int sum = 0;
	int count, i;
	//上三角
	char* str = (char*)malloc(16 * sizeof(char));
	for (int m = 4; m < 15; m++)
	{
		count = 0;
		i = m;
		while (i >= 0)
		{
			str[count] = arr[count][i];
			count++;
			i--;
		}
		str[count] = '\0';
		sum += FindSub(str, Score_Shape);
		//free(str);
	}
	//下三角
	for (int m = 1; m <= 10; m++)
	{
		count = 14;
		i = m;
		while (i < 15)
		{
			str[14-count] = arr[i][count];
			count--;
			i++;
		}
		str[14-count] = '\0';
		sum += FindSub(str, Score_Shape);
		//free(str);
	}
	free(str);
	return sum;
}

int StateScore(char arr[][15], struct Shape Score_Shape[30])
{
	int sum = 0;
	sum += SearchRow(arr, Score_Shape);
	sum += SearchCol(arr, Score_Shape);
	sum += SearchMain(arr, Score_Shape);
	sum += SearchVice(arr, Score_Shape);
	return sum;
}

void BotPlay1(char arr[][15], struct Shape Score_Shape[30], char* win)
{
	if (arr[7][7] == '0')
	{
		arr[7][7] = '1';
		return;
	}
	int Score = -999999999, max_i, max_j, CurScore;
	for (int i = 0; i < 15;i++)
	for (int j = 0; j < 15; j++)
	{
		
		if (arr[i][j] == '0')
		{
			arr[i][j] = '1';
			CurScore = StateScore(arr, Score_Shape);
			if (Score < CurScore)
			{
				Score = CurScore;
				max_i = i;
				max_j = j;
			}
			arr[i][j] = '0';
		}

	}
	arr[max_i][max_j] = '1';
	*win = IsWin(arr, max_i, max_j);
	return;
}






//机机对战用，与上面基本一致
void BotPlay2(char arr[][15], struct Shape Score_Shape[30], char* win)
{
	if (arr[7][6] == '0')
	{
		arr[7][6] = '2';
		return;
	}
	int Score = -999999999, max_i, max_j, CurScore;
	for (int i = 0; i < 15; i++)
	for (int j = 0; j < 15; j++)
	{

		if (arr[i][j] == '0')
		{
			arr[i][j] = '2';
			CurScore = StateScore(arr, Score_Shape);
			if (Score < CurScore)
			{
				Score = CurScore;
				max_i = i;
				max_j = j;
			}
			arr[i][j] = '0';
		}

	}

	arr[max_i][max_j] = '2';
	*win = IsWin(arr, max_i, max_j);
	return;
}






void BVP(char arr[][15], char* win, char** record, int* rec_count)
{
	struct Shape Score_Shape[30] =
	{
		{ 50, "01100" },
		{ 50, "00110" },
		{ 200, "11010" },
		{ 500, "00111" },
		{ 500, "11100" },
		{ 5000, "01110" },
		{ 5000, "010110" },
		{ 5000, "011010" },
		{ 5000, "11101" },
		{ 5000, "11011" },
		{ 5000, "10111" },
		{ 6000, "11110" },
		{ 6000, "01111" },
		{ 80000, "011110" },
		{ 99999999, "11111" },
		{ -50, "02200" },
		{ -50, "00220" },
		{ -200, "22020" },
		{ -500, "00222" },
		{ -500, "22200" },
		{ -70000, "02220" },
		{ -70000, "020220" },
		{ -70000, "022020" },
		{ -90000, "22202" },
		{ -90000, "22022" },
		{ -90000, "20222" },
		{ -90000, "22220" },
		{ -90000, "02222" },
		{ -90000, "022220" },
		{ -99999999, "22222" }
	};
	DrawBoard(arr);
	settextstyle(20, 0, L"楷体");
	outtextxy(10, 10, L"悔棋");

	while (1)
	{
		BotPlay1(arr, Score_Shape,win);
		LoadRecord(arr, record, rec_count);
		DrawChess(arr);
		if (IsOver(arr)) return;
		if (*win != '0')
		{
			PrintWinner(win);
			closegraph();
			RecordInText(record, rec_count);
			return;
		}
		CPlay(arr, win,record,rec_count);
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




void BVB(char arr[][15], char* win, char** record, int* rec_count)
{
	struct Shape Score_Shape1[30] =
	{
		{ 50, "01100" },
		{ 50, "00110" },
		{ 200, "11010" },
		{ 500, "00111" },
		{ 500, "11100" },
		{ 5000, "01110" },
		{ 5000, "010110" },
		{ 5000, "011010" },
		{ 5000, "11101" },
		{ 5000, "11011" },
		{ 5000, "10111" },
		{ 6000, "11110" },
		{ 6000, "01111" },
		{ 80000, "011110" },
		{ 99999999, "11111" },
		{ -50, "02200" },
		{ -50, "00220" },
		{ -200, "22020" },
		{ -500, "00222" },
		{ -500, "22200" },
		{ -70000, "02220" },
		{ -70000, "020220" },
		{ -70000, "022020" },
		{ -90000, "22202" },
		{ -90000, "22022" },
		{ -90000, "20222" },
		{ -90000, "22220" },
		{ -90000, "02222" },
		{ -90000, "022220" },
		{ -99999999, "22222" }
	};
	struct Shape Score_Shape2[30] =
	{
		{ 50, "02200" },
		{ 50, "00220" },
		{ 200, "22020" },
		{ 500, "00222" },
		{ 500, "22200" },
		{ 5000, "02220" },
		{ 5000, "020220" },
		{ 5000, "022020" },
		{ 5000, "22202" },
		{ 5000, "22022" },
		{ 5000, "20222" },
		{ 6000, "22220" },
		{ 6000, "02222" },
		{ 80000, "022220" },
		{ 99999999, "22222" },
		{ -50, "01100" },
		{ -50, "00110" },
		{ -200, "11010" },
		{ -500, "00111" },
		{ -500, "11100" },
		{ -70000, "01110" },
		{ -70000, "010110" },
		{ -70000, "011010" },
		{ -90000, "11101" },
		{ -90000, "11011" },
		{ -90000, "10111" },
		{ -90000, "11110" },
		{ -90000, "01111" },
		{ -90000, "011110" },
		{ -99999999, "11111" }
	};
	DrawBoard(arr);
	settextstyle(20, 0, L"楷体");
	//outtextxy(10, 10, L"悔棋");
	while (1)
	{
		Sleep(1000);
		BotPlay1(arr, Score_Shape1, win);
		LoadRecord(arr, record, rec_count);
		DrawChess(arr);
		if (IsOver(arr)) return;
		if (*win != '0')
		{
			PrintWinner(win);
			closegraph();
			RecordInText(record, rec_count);
			return;
		}
		Sleep(1000);
		BotPlay2(arr,Score_Shape2, win);
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
////









//////
//
//void BotPlay2(char arr[][15], struct Shape Score_Shape[30], char* win)
//{
//	if (arr[7][7] == '0')
//	{
//		arr[7][7] = '1';
//		return;
//	}
//	alpha = -999999999;
//	beta =   999999999;
//	/*//int Score = -999999999, max_i, max_j, CurScore;
//	//int x = 7, y = 7;
//	//for (int i = 0; i < 8; i++)
//	//{
//	//	for (int j = 0; j < 8; j++)
//	//	{
//	//		if (arr[y + i][x + j] == '0')
//	//		{
//	//			//arr[y + i][x + j] = '1';
//	//			CurScore = MaxStep(arr, Score_Shape, 0);
//	//			if (Score < CurScore)
//	//			{
//	//				Score = CurScore;
//	//				max_i = y + i;
//	//				max_j = x + j;
//	//			}
//	//			//arr[y + i][x + j] = '0';
//	//		}
//
//	//		if (arr[y + i][x - j] == '0')
//	//		{
//	//			//arr[y + i][x - j] = '1';
//	//			CurScore = MaxStep(arr, Score_Shape, 0);
//	//			if (Score < CurScore)
//	//			{
//	//				Score = CurScore;
//	//				max_i = y + i;
//	//				max_j = x - j;
//	//			}
//	//			//arr[y + i][x - j] = '0';
//	//		}
//
//	//		if (arr[y - i][x - j] == '0')
//	//		{
//	//			//arr[y - i][x - j] = '1';
//	//			CurScore = MaxStep(arr, Score_Shape, 0);
//	//			if (Score < CurScore)
//	//			{
//	//				Score = CurScore;
//	//				max_i = y - i;
//	//				max_j = x - j;
//	//			}
//	//			arr[y - i][x - j] = '0';
//	//		}
//
//	//		if (arr[y - i][x + j] == '0')
//	//		{
//	//			arr[y - i][x + j] = '1';
//	//			CurScore = MaxStep(arr, Score_Shape, 0);
//	//			if (Score < CurScore)
//	//			{
//	//				Score = CurScore;
//	//				max_i = y - i;
//	//				max_j = x + j;
//	//			}
//	//			arr[y - i][x + j] = '0';
//	//		}
//
//	//	}
//	//}
//	//arr[max_i][max_j] = '1';*/
//	SearchMax(arr, Score_Shape, 0);
//	arr[bot_i][bot_j] = '1';
//	*win = IsWin(arr, bot_i, bot_j);
//	return;
//}
//
//int MaxStep(char arr[][15], struct Shape Score_Shape[30],int count)
//{
//	if (count == 2)
//	{
//		int Score = -999999999,CurScore;
//		for (int i = 0; i < 15; i++)
//		for (int j = 0; j < 15; j++)
//		{
//
//			if (arr[i][j] == '0')
//			{
//				arr[i][j] = '1';
//				CurScore = StateScore(arr, Score_Shape);
//				if (Score < CurScore)
//				{
//					Score = CurScore;
//				}
//				arr[i][j] = '0';
//			}
//
//		}
//		return Score;
//	}
//		
//	int x = 7, y = 7, best = -999999999,tmp;
//	for (int i = 0; i < 8; i++)
//	{
//		for (int j = 0; j < 8; j++)
//		{
//			if (arr[y + i][x + j] == '0')
//			{
//				arr[y + i][x + j] = '1';
//				//
//				tmp=MinStep(arr, Score_Shape, count + 1);
//
//				//beta剪枝
//				if (beta<tmp)
//				{
//					arr[y + i][x + j] = '0';
//					return beta + 1;
//				}
//
//				if (tmp>best)
//				{
//					best = tmp;
//					if (count == 0)
//					{
//						bot_i = y + i;
//						bot_j = x + j;
//					}
//				}
//				/*best = tmp > best ? tmp : best;
//				if (count==0)*/
//				arr[y + i][x + j] = '0';
//			}
//
//			if (arr[y + i][x - j] == '0')
//			{
//				arr[y + i][x - j] = '1';
//				//
//				//beta剪枝
//				if (beta<tmp)
//				{
//					arr[y + i][x - j] = '0';
//					return beta + 1;
//				}
//
//				tmp = MinStep(arr, Score_Shape, count + 1);
//				if (tmp>best)
//				{
//					best = tmp;
//					if (count == 0)
//					{
//						bot_i = y + i;
//						bot_j = x - j;
//					}
//				}
//				arr[y + i][x - j] = '0';
//			}
//
//			if (arr[y - i][x - j] == '0')
//			{
//				arr[y - i][x - j] = '1';
//				//
//				//beta剪枝
//				if (beta<tmp)
//				{
//					arr[y - i][x - j] = '0';
//					return beta + 1;
//				}
//
//				tmp = MinStep(arr, Score_Shape, count + 1);
//				if (tmp>best)
//				{
//					best = tmp;
//					if (count == 0)
//					{
//						bot_i = y - i;
//						bot_j = x - j;
//					}
//				}
//				arr[y - i][x - j] = '0';
//			}
//
//			if (arr[y - i][x + j] == '0')
//			{
//				arr[y - i][x + j] = '1';
//				//
//				//beta剪枝
//				if (beta<tmp)
//				{
//					arr[y - i][x + j] = '0';
//					return beta + 1;
//				}
//
//				tmp = MinStep(arr, Score_Shape, count + 1);
//				if (tmp>best)
//				{
//					best = tmp;
//					if (count == 0)
//					{
//						bot_i = y - i;
//						bot_j = x + j;
//					}
//				}
//				arr[y - i][x + j] = '0';
//			}
//
//		}
//	}
//	alpha = best;
//	beta = alpha;
//	return best;
//}
//
//int MinStep(char arr[][15], struct Shape Score_Shape[30], int count)
//{
//	int x = 7, y = 7, best = 999999999, tmp;
//	for (int i = 0; i < 8; i++)
//	{
//		for (int j = 0; j < 8; j++)
//		{
//			if (arr[y + i][x + j] == '0')
//			{
//				arr[y + i][x + j] = '2';
//				//
//				tmp = MaxStep(arr, Score_Shape, count + 1);
//
//				//alpha剪枝
//				if (alpha>tmp)
//				{
//					arr[y + i][x + j] = '0';
//					return alpha - 1;
//				}
//				best = tmp < best ? tmp : best;
//				arr[y + i][x + j] = '0';
//			}
//
//			if (arr[y + i][x - j] == '0')
//			{
//				arr[y + i][x - j] = '2';
//				//
//				tmp = MaxStep(arr, Score_Shape, count + 1);
//
//				//alpha剪枝
//				if (alpha>tmp)
//				{
//					arr[y + i][x - j] = '0';
//					return alpha - 1;
//				}
//				best = tmp < best ? tmp : best;
//				arr[y + i][x - j] = '0';
//			}
//
//			if (arr[y - i][x - j] == '0')
//			{
//				arr[y - i][x - j] = '2';
//				//
//				tmp = MaxStep(arr, Score_Shape, count + 1);
//
//				//alpha剪枝
//				if (alpha>tmp)
//				{
//					arr[y - i][x - j] = '0';
//					return alpha - 1;
//				}
//				best = tmp < best ? tmp : best;
//				arr[y - i][x - j] = '0';
//			}
//
//			if (arr[y - i][x + j] == '0')
//			{
//				arr[y - i][x + j] = '2';
//				//
//				tmp = MaxStep(arr, Score_Shape, count + 1);
//
//
//				//alpha剪枝
//				if (alpha>tmp)
//				{
//					arr[y - i][x + j] = '0';
//					return alpha - 1;
//				}
//				best = tmp < best ? tmp : best;
//				arr[y - i][x + j] = '0';
//			}
//
//		}
//	}
//	beta = best;
//	alpha = beta;
//	return best;
//}
//
//void BVP2(char arr[][15], char* win, char** record, int* rec_count)
//{
//	struct Shape Score_Shape[30] =
//	{
//		{ 50, "01100" },
//		{ 50, "00110" },
//		{ 200, "11010" },
//		{ 500, "00111" },
//		{ 500, "11100" },
//		{ 5000, "01110" },
//		{ 5000, "010110" },
//		{ 5000, "011010" },
//		{ 5000, "11101" },
//		{ 5000, "11011" },
//		{ 5000, "10111" },
//		{ 6000, "11110" },
//		{ 6000, "01111" },
//		{ 80000, "011110" },
//		{ 99999999, "11111" },
//		{ -50, "02200" },
//		{ -50, "00220" },
//		{ -200, "22020" },
//		{ -500, "00222" },
//		{ -500, "22200" },
//		{ -5000, "02220" },
//		{ -5000, "020220" },
//		{ -5000, "022020" },
//		{ -5000, "22202" },
//		{ -5000, "22022" },
//		{ -5000, "20222" },
//		{ -6000, "22220" },
//		{ -6000, "02222" },
//		{ -80000, "022220" },
//		{ -99999999, "22222" }
//	};
//	DrawBoard(arr);
//	while (1)
//	{
//		BotPlay2(arr, Score_Shape, win);
//		LoadRecord(arr, record, rec_count);
//		DrawChess(arr);
//		if (IsOver(arr)) return;
//		if (*win != '0')
//		{
//			PrintWinner(win);
//			closegraph();
//			RecordInText(record, rec_count);
//			return;
//		}
//		CPlay(arr, win,record,rec_count);
//		LoadRecord(arr, record, rec_count);
//		DrawChess(arr);
//		if (*win != '0')
//		{
//			PrintWinner(win);
//			closegraph();
//			RecordInText(record, rec_count);
//			return;
//		}
//	}
//
//}
////
//int SearchMin(char arr[][15], struct Shape Score_Shape[30], int count)
//{
//	int tmp, best = 9999999999;
//	char book[15][15] = { '0' };
//	for (int i = 0; i < 15; i++)
//	for (int j = 0; j < 15; j++)
//	{
//		book[i][j] = '0';
//	}
//	for (int i = 0; i < 15; i++)
//	for (int j = 0; j < 15; j++)
//	{
//		if (j < 13 && i < 13)
//		{
//			if (arr[i][j] == '0' && book[i][j] == '0' && (arr[i + 1][j] != '0' || arr[i + 1][j + 1] != '0' || arr[i][j + 1] != '0' || arr[i + 2][j] != '0' || arr[i + 2][j + 2] != '0' || arr[i][j + 2] != '0' || arr[i + 1][j + 2] != '0' || arr[i + 2][j + 1] != '0'))
//			{
//				book[i][j] = '1'; //1为走到过
//				arr[i][j] = '2';
//				//
//				tmp = SearchMax(arr, Score_Shape, count + 1);
//
//				//beta剪枝
//				if (alpha>tmp)
//				{
//					arr[i][j] = '0';
//					return alpha - 1;
//				}
//
//				if (tmp<best)
//				{
//					best = tmp;
//				}
//				arr[i][j] = '0';
//			}
//		}
//		if (j>1 && i>1)
//		{
//			if (arr[i][j] == '0' && book[i][j] == '0' && arr[i - 1][j] != '0' || arr[i - 1][j - 1] != '0' || arr[i][j - 1] != '0' || arr[i - 2][j] != '0' || arr[i - 2][j - 2] != '0' || arr[i][j - 2] != '0' || arr[i - 1][j - 2] != '0' || arr[i - 2][j - 1] != '0')
//			{
//				book[i][j] = '1'; //1为走到过
//				arr[i][j] = '2';
//				//
//				tmp = SearchMax(arr, Score_Shape, count + 1);
//
//				//alpha剪枝
//				if (alpha>tmp)
//				{
//					arr[i][j] = '0';
//					return alpha-1;
//				}
//
//				if (tmp<best)
//				{
//					best = tmp;
//				}
//				arr[i][j] = '0';
//			}
//		}
//
//	}
//	beta = best;
//	alpha = beta;
//	return best;
//}
//
//
//
//int SearchMax(char arr[][15], struct Shape Score_Shape[30], int count)
//{
//	//最后一步
//	if (count == 2)
//	{
//		int Score = -999999999, CurScore;
//		for (int i = 0; i < 15; i++)
//		for (int j = 0; j < 15; j++)
//		{
//
//			if (arr[i][j] == '0')
//			{
//				arr[i][j] = '1';
//				CurScore = StateScore(arr, Score_Shape);
//				if (Score < CurScore)
//				{
//					Score = CurScore;
//				}
//				arr[i][j] = '0';
//			}
//
//		}
//		return Score;
//	}
//
//	int tmp, best = -9999999999;
//	char book[15][15] = { '0' };
//	for (int i = 0; i < 15; i++)
//	for (int j = 0; j < 15; j++)
//	{
//		book[i][j] = '0';
//	}
//	for (int i = 0; i < 15;i++)
//	for (int j = 0; j < 15; j++)
//	{
//		if (j < 13 && i < 13)
//		{
//			if (arr[i][j]=='0' && book[i][j]=='0' && (arr[i + 1][j] != '0' || arr[i + 1][j + 1] != '0' || arr[i][j + 1] != '0' || arr[i + 2][j] != '0' || arr[i + 2][j + 2] != '0' || arr[i][j + 2] != '0' || arr[i + 1][j + 2] != '0' || arr[i + 2][j + 1] != '0'))
//			{
//				book[i][j] = '1'; //1为走到过
//				arr[i][j] = '1';
//				//
//				tmp = SearchMin(arr, Score_Shape, count + 1);
//
//				//beta剪枝
//				if (beta<tmp)
//				{
//					arr[i][j] = '0';
//					return beta + 1;
//				}
//
//				if (tmp>best)
//				{
//					best = tmp;
//					if (count == 0)
//					{
//						bot_i = i;
//						bot_j = j;
//					}
//				}
//				arr[i][j] = '0';
//			}
//		}
//		if (j>1 && i>1)
//		{
//			if (arr[i][j]=='0' && book[i][j]=='0' && (arr[i - 1][j] != '0' || arr[i - 1][j - 1] != '0' || arr[i][j - 1] != '0' || arr[i - 2][j] != '0' || arr[i - 2][j - 2] != '0' || arr[i][j - 2] != '0' || arr[i - 1][j - 2] != '0' || arr[i - 2][j - 1] != '0'))
//			{
//				book[i][j] = '1'; //1为走到过
//				arr[i][j] = '1';
//				//
//				tmp = SearchMin(arr, Score_Shape, count + 1);
//
//				//beta剪枝
//				if (beta<tmp)
//				{
//					arr[i][j] = '0';
//					return beta + 1;
//				}
//
//				if (tmp>best)
//				{
//					best = tmp;
//					if (count == 0)
//					{
//						bot_i = i;
//						bot_j = j;
//					}
//				}
//				arr[i][j] = '0';
//			}
//		}
//		
//	}
//	alpha = best;
//	beta = alpha;
//	return best;
//}