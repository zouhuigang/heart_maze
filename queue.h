/*

������������
*/
#pragma once
#include "public.h"

typedef struct {
	Block *data;//����Ľṹ������
	int front;//frontָ���һ��Ԫ�ص�λ��
	int rear;//rearָ�����һ��Ԫ�ص���һ��λ�á�
}SqQueue;

#define MAXQSIZE 1001 //ѭ�����еĴ�С,����һ���洢��Ԫ,ʵ���������Ϊ(MAXQSIZE-1)
#define OK 1
#define ERROR 0


//��ʼ������,����һ���ն���Q
void initQueue(SqQueue *Q)
{
	Q->data = (Block*)malloc(MAXQSIZE * sizeof(Block));
	if (!Q->data)
		return;
	Q->front = Q->rear = 0;
}

//�������Q���ڣ��������Ԫ��e�����е�β��
int EnQueue(SqQueue *Q, Block e)
{
	if ((Q->rear + 1) % MAXQSIZE == Q->front)//������������һ���洢��Ԫ
		return ERROR;

	Q->data[Q->rear] = e;
	Q->rear = (Q->rear + 1) % MAXQSIZE;
	return OK;
}


//���еĳ���
int getLength(SqQueue *Q)
{
	return (Q->rear - Q->front + MAXQSIZE) % MAXQSIZE;
}

//ɾ�����е�ͷ��Ԫ�أ�����e������ֵ
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

//ɾ������ͷ��Ԫ��
int DeQueue(SqQueue *Q, Block *e){
	if(Q->front==Q->rear){
		return ERROR; //����Ϊ��
	}
	*e= Q->data[Q->front];
	Q->front=(Q->front+1)%MAXQSIZE;
	return OK;
}


//�ж϶����Ƿ�Ϊ��,��rear==frontʱ������Ϊ�ա���rear��front�м����һ���洢��Ԫʱ������Ϊ��
int IsEmpty(SqQueue *Q)
{
	if (Q->front == Q->rear)
		return OK;
	else
		return ERROR;
}

//�ж϶����Ƿ�����
int IsFull(SqQueue *Q){
	if ((Q->rear + 1) % MAXQSIZE == Q->front)//������������һ���洢��Ԫ
		return OK;
	else
		return ERROR;
}


//��ն���
int ClearQueue(SqQueue *Q){
    Q->front=Q->rear;
	return OK;
}


//���ٶ���
int DestroyQueue(SqQueue *Q){
    free(Q->data);
	Q->data=NULL;
	Q->front=Q->rear=0;
	return OK;
}

