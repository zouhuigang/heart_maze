#pragma once
#include "queue.h"

#define N 100	
#define M 100
#define DELAY 1

//ö������(SCENE:������������ROAD��·,INWALL:��ǽ��OUTWALL:��ǽ
typedef enum { SCENE = 0, ROAD = 1, INWALL = 2, OUTWALL = 3,VISITED=4} BlockType;
typedef enum { EAST = 6, SOUTH = 7, WEST = 8, NORTH = 9 } Direction;
typedef int Maze;

//һ�������������ĸ����λ��
int around[4][2] = { { 0,1 },{ 1,0 },{ 0,-1 },{ -1,0 } };

//���庯��
void initHeart();//��ʼ���ĵ���״����
void drawHeartMaze();//���������Թ�
void draw();//����ͼ����ͬ��Ԫ��
int findHeartWall();//�ж��Ƿ����ĵı߽��
void generatingMaze();//�����Թ�