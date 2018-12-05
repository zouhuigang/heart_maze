#pragma once
#include "queue.h"

#define N 100	
#define M 100
#define DELAY 1

//枚举类型(SCENE:场景辅助区，ROAD：路,INWALL:内墙，OUTWALL:外墙
typedef enum { SCENE = 0, ROAD = 1, INWALL = 2, OUTWALL = 3,VISITED=4} BlockType;
typedef enum { EAST = 6, SOUTH = 7, WEST = 8, NORTH = 9 } Direction;
typedef int Maze;

//一个点上下左右四个点的位置
int around[4][2] = { { 0,1 },{ 1,0 },{ 0,-1 },{ -1,0 } };

//定义函数
void initHeart();//初始化心的形状区域
void drawHeartMaze();//绘制心形迷宫
void draw();//绘制图案不同的元素
int findHeartWall();//判断是否是心的边界点
void generatingMaze();//生成迷宫