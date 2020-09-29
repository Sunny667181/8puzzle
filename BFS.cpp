// BFS
// 广度优先搜索-八数码问题
/*	八数码实现问题八数码问题也称为九宫问题。
	在3×3的棋盘，摆有八个棋子，每个棋子上标有1至8的某一数字，不同棋子上标的数字不相同。
	棋盘上还有一个空格，与空格相邻的棋子可以移到空格中。
	要求解决的问题是：给出一个初始状态和一个目标状态，找出一种从初始转变成目标状态的移动棋子步数最少的移动步骤。
	所谓问题的一个状态就是棋子在棋盘上的一种摆法。
	解八数码问题实际上就是找出从初始状态到达目标状态所经过的一系列中间过渡状态。
	思路移动棋子最少，当然是使用广度优先搜索来解决。所以这里的每个节点就要是一个3*3的矩阵。
	可以使用结构体：
		struct node 
		{ 
			int xy[3][3]; 
		};
	实现方案：空白棋子用0代替。
			  接受初始节点的信息和目标节点的信息找到空白棋子很简单，直接遍历就好。
			  如何返回它的x和y坐标，使用一个数字代替。
				int loction(int num) 
				{ int i;
				  for (i = 0; i < 9; i++) 
					if (sh[num].xy[i / 3][i % 3] == 0) 
						return i; }
	从初始节点开始判断，然后扩展，即上下左右移动，当然我们要考虑具体的位置，比如说已经到边界了，就不能越出边界。
	还要考虑以前移动过的方向，所以记录下来以前移动过的方向，可以直接加在结构体里。
	每次扩展的节点就加在数组后面。
*/

//测试用例
/*
2 8 3
1 6 4
7 0 5
1 2 3
7 8 4
0 6 5
*/

#include <stdio.h>
#define N 102	//定义从初始状态到目标状态的最大移动次数为N

// 3*3数组，代表3*3棋盘，1-8代表数字，0代表空格
struct node
{
    int xy[3][3];
    int dir;	//dir的0 1 2 3分别代表左 上 右 下
};
struct node sh[N], end; 
int count = 1;
 
void init()
{
    printf("输入起始节点的位置:\n");
    int i, j;
    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
            scanf("%d", &sh[0].xy[i][j]);
    sh[0].dir = -1;
    printf("输入目标节点的位置:\n");
    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
            scanf("%d", &sh[N-1].xy[i][j]);
    sh[N-1].dir = -1;
}
 
//找出0的位置
int location(int num)
{
    int i;
    for (i = 0; i < 9; i++)
        if (sh[num].xy[i / 3][i % 3] == 0) return i;
}
 
 
//进行标记
long long sign(int num)
{
    long long sum;
    sum = sh[num].xy[0][0]*100000000 + sh[num].xy[0][1]*10000000 + sh[num].xy[0][2]*1000000 + sh[num].xy[1][0]*100000 + sh[num].xy[1][1]*10000 + sh[num].xy[1][2]*1000 + sh[num].xy[2][0]*100 + sh[num].xy[2][1]*10 + sh[num].xy[2][2];
    return sum;
}
 
void mobile(int num)
{
 
    int temp;
    int loc;	//找出0的位置
    int up = 1, down = 1, left = 1, right = 1;
    loc = location(num);
    int stand = sh[num].dir;
    //dir的0 1 2 3分别代表左 上 右 下
    if (loc / 3 != 0 && stand != 1)
    {
        sh[count] = sh[num];
        temp = sh[count].xy[loc / 3][loc % 3];
        sh[count].xy[loc / 3][loc % 3] = sh[count].xy[loc / 3 - 1][loc % 3];
        sh[count].xy[loc / 3 - 1][loc % 3] = temp;
        sh[count].dir = 3;
        count++;
    };
    if (loc / 3 != 2 && stand != 3)
    {
        sh[count] = sh[num];
        temp = sh[count].xy[loc / 3][loc % 3];
        sh[count].xy[loc / 3][loc % 3] = sh[count].xy[loc / 3 + 1][loc % 3];
        sh[count].xy[loc / 3 + 1][loc % 3] = temp;
        sh[count].dir = 1;
        count++;
    }
    if (loc % 3 != 0 && stand != 0)
    {
        sh[count] = sh[num];
        temp = sh[count].xy[loc / 3][loc % 3];
        sh[count].xy[loc / 3][loc % 3] = sh[count].xy[loc / 3][loc % 3 - 1];
        sh[count].xy[loc / 3][loc % 3 - 1] = temp;
        sh[count].dir = 2;
        count++;
    }
    if (loc % 3 != 2 && stand != 2)
    {
        sh[count] = sh[num];
        temp = sh[count].xy[loc / 3][loc % 3];
        sh[count].xy[loc / 3][loc % 3] = sh[count].xy[loc / 3][loc % 3 + 1];
        sh[count].xy[loc / 3][loc % 3 + 1] = temp;
        sh[count].dir = 0;
        count++;
    }
 
}
void display(int num)
{
    int i, j;
	printf("第%d次移动：\n",num);
    for (i = 0; i < 3; i++)
    {
		for (j = 0; j < 3; j++)
            printf("%d ", sh[num].xy[i][j]);
        printf("\n");
    }
}
 
int search()
{
    int i = 0;
    while (1)
    {
        printf("\n");
        display(i);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            
        if (i == 100)
        {
            printf("超出了上限次数\n");
            return 0;
        }
        if (sign(i) == sign(N-1))
        {
            printf("\n\n在第%d次找到了\n", i);
            display(i);
            return i;
        }
        mobile(i);
        i++;
    }
}
 
int main()
{
    init();
    search();
    return 0;
}