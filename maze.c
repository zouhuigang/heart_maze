#include "maze.h"
#include "queue.h"
#define FALSE 0
#define TRUE 1
int area[N][M];//��������
int maze[N][M];//�Թ�����
int visited[N][M];//���ʹ��ĵ�

int main()
{

	drawHeartMaze();


	getchar();
	return 0;
}


//���������Թ�
void drawHeartMaze(){
	int i;
	int j;

	initHeart();

	//��ʼ��:����һЩ�����·
	for(i=0;i<N;i++){
		for(j=0;j<M;j++){
			if (findHeartWall(i,j)){//��ǽ
				maze[i][j] = OUTWALL;
			}else if(area[i][j] && i %2 ==0 && j %2 ==0){//��ǽ�е�·
				maze[i][j] = ROAD;
			}else if(area[i][j]){//��ǽ
				maze[i][j] = INWALL;
			}else{
				maze[i][j] = SCENE;
			}
		}
	}

	//�����Թ�
	generatingMaze();


	//���ջ���
	draw();
}

void generatingMaze(){
	
	//����
	SqQueue queue;//һ������
	Block startPoint;//�Թ����
	Block endPoint;//�Թ��յ�
	Block roadStartPoint;//�����Թ������
	Block curBlock; //��ǰ�ĵ�
	Block nextBlock;//�����ĵ�
	int i;

	//����ʼ�㿪ʼ��Ѱ��
	startPoint.x=1;
	startPoint.y=10;

	//�յ�
	endPoint.x=33;
	endPoint.y=30;

	//�����Թ������
	roadStartPoint.x=2;
	roadStartPoint.y=10;

	maze[startPoint.x][startPoint.y] = VISITED;
	visited[startPoint.x][startPoint.y]=1;

	maze[endPoint.x][endPoint.y] = VISITED;
	visited[endPoint.x][endPoint.y]=1;

	maze[roadStartPoint.x][roadStartPoint.y] = VISITED;
	visited[roadStartPoint.x][roadStartPoint.y]=1;


	//�����Թ�,�������У����������
	initQueue(&queue);//��ʼ������
	EnQueue(&queue,roadStartPoint);

	while(!IsEmpty(&queue)){//����������Ϊ�գ����˳�ѭ��

		DeRandQueue(&queue,&curBlock);//�ʼȡ������ֵ
		//������ǰ�����ܵķ���
		for (i = 0; i < 4; i++){
			nextBlock.x=curBlock.x+around[i][0]*2;//��2��Ŀ���ǣ������2����λ����·��
			nextBlock.y=curBlock.y+around[i][1]*2;
			if(area[nextBlock.x][nextBlock.y] && !visited[nextBlock.x][nextBlock.y] && maze[nextBlock.x][nextBlock.y] == ROAD){//�ж��ܱߵĵ㣬�Ƿ������η�Χ��,������·����û�б����ʹ�
				EnQueue(&queue, nextBlock);
				maze[nextBlock.x][nextBlock.y] = VISITED;
				visited[nextBlock.x][nextBlock.y]=1;
				//��ͨ2��·֮���ǽ
				maze[curBlock.x+around[i][0]][curBlock.y+around[i][1]] = VISITED;
			}
		}
	
	}



}

//����ͼ��
void draw(){
	int i;
	int j;
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < M; j++)
		{
			if (maze[i][j] == INWALL)
				printf("��");
			else if(maze[i][j] == OUTWALL){
				printf("��");
			}else if(maze[i][j] == ROAD){
				printf("·");
			}else if(maze[i][j] == VISITED){
				printf("  ");
			}else{
				printf("  ");
			}
				
		}
		printf("\n");
	}

}



//�ж����ĵı߽�
int findHeartWall(int i,int j){
	int m;
	int n;

	//�ж���i,j�����ĵķ�Χ��
	if(area[i][j]==0){
		return FALSE;
	}

	//�Ź���ѭ������
	for(m=i-1;m<=i+1;m++){
		for(n=j-1;n<=j+1;n++){
			//���������ĸ�λ��
			if(m==i || n==j){
				if(m==i && n==j){//�ų��Լ�
					continue;
				}
				if(area[m][n]==0){
						return TRUE;
				}
			}

		}
	}

	return FALSE;
}




//��ʼ���ĵķ�Χ
void initHeart()
{
	int i = 1, j = 1;
	float x;
	float y;
	float a;
	for ( y = 1.2f; y > -1.0f; y -= 0.06f)
	{
		for ( x = -1.1f; x < 1.2f; x += 0.05f)
		{
			 a = x * x + y * y - 1;
			if (a * a * a - x * x * y * y * y <= 0.0f)
				area[i][j] = 1;
			else
				area[i][j] = 0;
			j++;
		}
		i++;
		j = 1;
	}
}
