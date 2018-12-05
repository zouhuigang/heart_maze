/*

随机进，随机出
*/
#pragma once
#include "public.h"

typedef struct {
	Block *data;//存入的结构体数据
	int front;//front指向第一个元素的位置
	int rear;//rear指向最后一个元素的下一个位置。
}SqQueue;

#define MAXQSIZE 1001 //循环队列的大小,牺牲一个存储单元,实际最大容量为(MAXQSIZE-1)
#define OK 1
#define ERROR 0


//初始化操作,建立一个空队列Q
void initQueue(SqQueue *Q)
{
	Q->data = (Block*)malloc(MAXQSIZE * sizeof(Block));
	if (!Q->data)
		return;
	Q->front = Q->rear = 0;
}

//如果队列Q存在，则插入新元素e到队列的尾部
int EnQueue(SqQueue *Q, Block e)
{
	if ((Q->rear + 1) % MAXQSIZE == Q->front)//队列满，牺牲一个存储单元
		return ERROR;

	Q->data[Q->rear] = e;
	Q->rear = (Q->rear + 1) % MAXQSIZE;
	return OK;
}


//队列的长度
int getLength(SqQueue *Q)
{
	return (Q->rear - Q->front + MAXQSIZE) % MAXQSIZE;
}

//删除队列的头部元素，并用e返回其值
void DeRandQueue(SqQueue *Q, Block *e)
{
	int randIdx;
	if (Q->front == Q->rear)
		return;
	srand((unsigned)time(NULL));
	randIdx = rand() % getLength(Q);
	*e = Q->data[randIdx];
	Q->data[randIdx] = Q->data[Q->rear - 1];
	Q->data[Q->rear - 1] = *e;

	Q->rear = (Q->rear - 1) % MAXQSIZE;
}

//删除队列头部元素
int DeQueue(SqQueue *Q, Block *e){
	if(Q->front==Q->rear){
		return ERROR; //队列为空
	}
	*e= Q->data[Q->front];
	Q->front=(Q->front+1)%MAXQSIZE;
	return OK;
}


//判断队列是否为空,当rear==front时，队列为空。当rear与front中间仅差一个存储单元时，队列为满
int IsEmpty(SqQueue *Q)
{
	if (Q->front == Q->rear)
		return OK;
	else
		return ERROR;
}

//判断队列是否已满
int IsFull(SqQueue *Q){
	if ((Q->rear + 1) % MAXQSIZE == Q->front)//队列满，牺牲一个存储单元
		return OK;
	else
		return ERROR;
}


//清空队列
int ClearQueue(SqQueue *Q){
    Q->front=Q->rear;
	return OK;
}


//销毁队列
int DestroyQueue(SqQueue *Q){
    free(Q->data);
	Q->data=NULL;
	Q->front=Q->rear=0;
	return OK;
}

