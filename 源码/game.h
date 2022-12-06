#pragma once
#include<stdio.h>
#include<graphics.h>
#include<Windows.h>
#include<stdlib.h>

struct Shape
{
	int score;
	char shape[10];
};

int IsOver(char arr[][15]);


void DrawBoard(char arr[][15]);
void DrawChess(char arr[][15]);


void PVP(char arr[][15], char* win, char** record, int* rec_count);
void PPlay(char arr[][15], char* win, char** record, int* rec_count);
void CPlay(char arr[][15], char* win, char** record, int* rec_count);
char IsWin(char arr[][15],int i,int j);
void PrintWinner(char* win);
void LoadRecord(char arr[][15],char**record,int* rec_count);
void RecordInText(char**record, int* rec_count);
void ShowRecord(char arr[][15]);
void BVP(char arr[][15], char* win, char** record, int* rec_count);
void BVB(char arr[][15], char* win, char** record, int* rec_count);
void Regret(char arr[][15], char** record, int*rec_count);
//int MaxStep(char arr[][15], struct Shape Score_Shape[30], int count);
//int MinStep(char arr[][15], struct Shape Score_Shape[30], int count);
int SearchMin(char arr[][15], struct Shape Score_Shape[30], int count);
int SearchMax(char arr[][15], struct Shape Score_Shape[30], int count);
void BVP2(char arr[][15], char* win, char** record, int* rec_count);

