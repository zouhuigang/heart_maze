#include "maze.h"
#include "queue.h"
#define FALSE 0
#define TRUE 1
int area[N][M];//心形区域
int maze[N][M];//迷宫数据
int visited[N][M];//访问过的点

int main()
{

	drawHeartMaze();


	getchar();
	return 0;
}


//绘制心型迷宫
void drawHeartMaze(){
	int i;
	int j;

	initHeart();

	//初始化:绘制一些交叉的路
	for(i=0;i<N;i++){
		for(j=0;j<M;j++){
			if (findHeartWall(i,j)){//外墙
				maze[i][j] = OUTWALL;
			}else if(area[i][j] && i %2 ==0 && j %2 ==0){//内墙中的路
				maze[i][j] = ROAD;
			}else if(area[i][j]){//内墙
				maze[i][j] = INWALL;
			}else{
				maze[i][j] = SCENE;
			}
		}
	}

	//生成迷宫
	generatingMaze();


	//最终绘制
	draw();
}

void generatingMaze(){
	
	//声明
	SqQueue queue;//一个队列
	Block startPoint;//迷宫起点
	Block endPoint;//迷宫终点
	Block roadStartPoint;//生成迷宫的起点
	Block curBlock; //当前的点
	Block nextBlock;//附近的点
	int i;

	//从起始点开始，寻找
	startPoint.x=1;
	startPoint.y=10;

	//终点
	endPoint.x=33;
	endPoint.y=30;

	//生成迷宫的起点
	roadStartPoint.x=2;
	roadStartPoint.y=10;

	maze[startPoint.x][startPoint.y] = VISITED;
	visited[startPoint.x][startPoint.y]=1;

	maze[endPoint.x][endPoint.y] = VISITED;
	visited[endPoint.x][endPoint.y]=1;

	maze[roadStartPoint.x][roadStartPoint.y] = VISITED;
	visited[roadStartPoint.x][roadStartPoint.y]=1;


	//绘制迷宫,随机入队列，随机出队列
	initQueue(&queue);//初始化队列
	EnQueue(&queue,roadStartPoint);

	while(!IsEmpty(&queue)){//如果随机队列为空，则退出循环

		DeRandQueue(&queue,&curBlock);//最开始取出起点的值
		//遍历当前点四周的方向
		for (i = 0; i < 4; i++){
			nextBlock.x=curBlock.x+around[i][0]*2;//乘2的目的是，间隔了2个单位才有路。
			nextBlock.y=curBlock.y+around[i][1]*2;
			if(area[nextBlock.x][nextBlock.y] && !visited[nextBlock.x][nextBlock.y] && maze[nextBlock.x][nextBlock.y] == ROAD){//判断周边的点，是否在心形范围内,而且是路，且没有被访问过
				EnQueue(&queue, nextBlock);
				maze[nextBlock.x][nextBlock.y] = VISITED;
				visited[nextBlock.x][nextBlock.y]=1;
				//打通2个路之间的墙
				maze[curBlock.x+around[i][0]][curBlock.y+around[i][1]] = VISITED;
			}
		}
	
	}



}

//绘制图案
void draw(){
	int i;
	int j;
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < M; j++)
		{
			if (maze[i][j] == INWALL)
				printf("█");
			else if(maze[i][j] == OUTWALL){
				printf("█");
			}else if(maze[i][j] == ROAD){
				printf("路");
			}else if(maze[i][j] == VISITED){
				printf("  ");
			}else{
				printf("  ");
			}
				
		}
		printf("\n");
	}

}



//判断是心的边界
int findHeartWall(int i,int j){
	int m;
	int n;

	//判断是i,j是在心的范围内
	if(area[i][j]==0){
		return FALSE;
	}

	//九宫格循环查找
	for(m=i-1;m<=i+1;m++){
		for(n=j-1;n<=j+1;n++){
			//上下左右四个位置
			if(m==i || n==j){
				if(m==i && n==j){//排除自己
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




//初始化心的范围
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
