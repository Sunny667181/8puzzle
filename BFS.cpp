/*广度优先搜索-八数码问题
算法简介：广度优先搜索问题给定一个一幅图和一个起点s，
		回答“从s到给定的顶点v是否存在一条路径？如果有，找出其中最短的那条（所含边数最少）。
		“思路边数最少，很自然想到从从经过1条边能到达的节点有哪些？然后经过这些边再到达的节点有哪些？这样我不就能够想出来最短的路径了吗？
		没错，这是非常简单的想法，然而真正的广度优先算法也是这样，简单而有效。
		解决方法：上面这幅图我要找到从1到12的最短路径，则我会从1经过1条边可以到达的节点（2 3 4）搜索，发现没有，
		接下来搜索节点（2 3 4）通过1条边能够到达的顶点（5 6 7 8），发现没有，接下来搜索节点（5 6 7 8），发现没有，
		接下来搜索节点（5 6 7 8）通过1条边能够到达的节点（9 10 11 12），搜索到最后一个，发现搜索到了。
		如果你每次经过一条边则记录加1，则现在经过了三条边，即最短路径是3条边，实现方案当已经理解了算法思想，接下来就应该实现了。
		最重要的一步是思考使用什么样的数据结构，想想这里的搜索一个集合，那自然就是遍历他们，接下来还要遍历他们通过一条边能够到达节点，普通的想法是先判断他们，
		如果没有，则再遍历他们，然后生成的所有节点再加入一个新的集合当中。问题：发现了没，这里遍历了两遍集合。
		还有就是新的节点加入一个新的集合，每次都要声明新的数组吗？这是有多麻烦。
		解决方案：这里遍历了两遍，其实我先生成新的节点和后生成新的节点只是多占用一点空间而已，我要是在遍历第一个节点如果判断不是就直接生成新的节点也可以，
		这样就不用遍历第二遍了，加入新的集合解决起来有点棘手，如果我可以仍然放在集合里面继续遍历就好了，对！就是这样，所以在集合里会有顺序的关系，
		不能我先遍历第一个节点，接着直接遍历新的节点，所以说我们的数据就要有顺序之分，所以想想有什么样的数据存储方式能够有顺序，常见的数组就够了，
		如果稍微学过数据结构，链表也可以。编程的思路：遍历数组，从第一个节点开始，如果不是，则生成新节点加入到数组的最后一个节点后面，
		所以如果是c语言，一定要将数组声明大一些。然后不断遍历即可，直到找到。
		*/
/*	八数码实现问题八数码问题也称为九宫问题。
	在3×3的棋盘，摆有八个棋子，每个棋子上标有1至8的某一数字，不同棋子上标的数字不相同。
	棋盘上还有一个空格，与空格相邻的棋子可以移到空格中。
	要求解决的问题是：给出一个初始状态和一个目标状态，找出一种从初始转变成目标状态的移动棋子步数最少的移动步骤。
	所谓问题的一个状态就是棋子在棋盘上的一种摆法。解八数码问题实际上就是找出从初始状态到达目标状态所经过的一系列中间过渡状态。
	思路移动棋子最少，当然是使用广度优先搜索来解决。所以这里的每个节点就要是一个3*3的矩阵。
	如果在c语言中，可以使用结构体。struct node { int xy[3][3]; };
	实现方案空白棋子用0代替接受初始节点的信息和目标节点的信息找到空白棋子很简单，直接遍历就好，但是如何返回它的x和y坐标，试着能不能使用一个数字代替，后来发现确实可以。
	int loction(int num) 
	{ int i;
	  for (i = 0; i < 9; i++) 
		if (sh[num].xy[i / 3][i % 3] == 0) return i; }
	从初始节点开始判断，然后扩展，即上下左右移动，当然我们要考虑具体的位置，比如说已经到边界了，就不能越出边界。
	还要考虑以前移动过的方向，所以记录下来以前移动过的方向，可以直接加在结构体里。
	（代码如下所示）每次扩展的节点就加在数组后面。
*/

#include<stdio.h>
 
struct node
{
    int xy[3][3];
    int dir;
};
struct node sh[102], end;
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
            scanf("%d", &sh[101].xy[i][j]);
    sh[101].dir = -1;
}
 
//找出0的位置
int loction(int num)
{
    int i;
    for (i = 0; i < 9; i++)
        if (sh[num].xy[i / 3][i % 3] == 0) return i;
}
 
 
//进行标记
long long sign(int num)
{
    long long  sum;
    sum = sh[num].xy[0][0]*100000000 + sh[num].xy[0][1]*10000000 + sh[num].xy[0][2]*1000000 + sh[num].xy[1][0]*100000 + sh[num].xy[1][1]*10000 + sh[num].xy[1][2]*1000 + sh[num].xy[2][0]*100 + sh[num].xy[2][1]*10 + sh[num].xy[2][2];
    return sum;
}
 
void mobile(int num)
{
 
    int temp;
    int loc;
    int up = 1, down = 1, left = 1, right = 1;
    loc = loction(num);
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
	printf("第%d次：\n",num);
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
        if (sign(i) == sign(101))
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