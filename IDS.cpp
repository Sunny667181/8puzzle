/*
在3×3的棋盘上，摆有八个棋子，每个棋子上标有1至8的某一数字。
棋盘中留有一个空格，空格用0来表示。空格周围的棋子可以移到空格中。
要求解的问题是：给出一种初始布局（初始状态）和目标布局（为了使题目简单,设目标状态为123804765），
找到一种最少步骤的移动方法，实现从初始布局到目标布局的转变。
输入格式：
输入初始状态，一行九个数字，空格用0表示
输出格式：
只有一行，该行只有一个数字，表示从初始状态到目标状态需要的最少移动次数(测试数据中无特殊无法到达目标状态数据)
*/

/*
这中间的状态记录把九宫格如下编号：
1 2 3
4 5 6
7 8 9
*/
#include <iostream>
#include <cstdlib>
#include <cstdio>
using namespace std;

int dep;//限制深度
int a[13];//把状态拆开之后放这儿
int chai(int x)//拆！
{
    int ret;//记一下0在哪儿
    for(register int i=9;i>=1;--i)
    {
        if(x%10==0)ret=i;
        a[i]=x%10;
        x/=10;
    }
    return ret;
}

long long ans=123804765;//目标态

long long sub()//把拆开的压起来
{
    long long x=0;
    for(register int i=1;i<=9;++i)
    x=x*10+a[i];
    return x;
}
void ids(int k,int d,int bef)// k:0在哪儿 d：当前深度 bef:上一次的操作
{
    if(sub()==ans)
	{
		cout<<"从初始状态到目标状态需要的最少移动次数：";
		cout<<d-1<<endl;exit(0);
	}//找到了就输出
    
	if(d>dep)
		return;//超过限定深度啦
   
	//mvup 把空格往上移
    if(k>3&&bef!=1)
	{
		swap(a[k-3],a[k]);
		dfs(k-3,d+1,3);
		swap(a[k-3],a[k]);
	}
   
	//mvdown 把空格往下
    if(k<7&&bef!=3)
	{
		swap(a[k+3],a[k]);
		dfs(k+3,d+1,1);
		swap(a[k+3],a[k]);
	}
   
	//mvleft 往左
    if(k%3!=1&&bef!=2)
	{
		swap(a[k-1],a[k]);
		dfs(k-1,d+1,4);
		swap(a[k-1],a[k]);
	}
   
	//mvright 往右
    if(k%3!=0&&bef!=4)
	{
		swap(a[k+1],a[k]);
		dfs(k+1,d+1,2);
		swap(a[k+1],a[k]);
	}
}
int main()
{
    //freopen("a.in","r",stdin);
    long long x;
	cout << "请输入初始态：";
	cin>>x;
    dep=0;
    while(1)
    {
        ++dep;//迭代加深
        int k=chai(x);
        ids(k,1,0);
    }
    return 0;
}