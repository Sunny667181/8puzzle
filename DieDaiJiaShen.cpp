/*
    qwerta
    P1379 八数码难题
    Accepted
    100
    代码 C++，1.06KB
    提交时间 2018-10-01 21:50:56
    耗时/内存
    2106ms, 816KB
*/
/*
这中间的状态记录把九宫格如下编号：
1 2 3
4 5 6
7 8 9
*/
#include<iostream>
#include<cstdlib>
#include<cstdio>
using namespace std;
#define LL long long
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
LL ans=123804765;//目标态
LL sub()//把拆开的压起来
{
    LL x=0;
    for(register int i=1;i<=9;++i)
    x=x*10+a[i];
    return x;
}
void dfs(int k,int d,int bef)// k:0在哪儿 d：当前深度 bef:上一次的操作
{
    if(sub()==ans){cout<<d-1;exit(0);}//找到了就输出
    if(d>dep)return;//超过限定深度啦
    //mvup 把空格往上移
    if(k>3&&bef!=1){swap(a[k-3],a[k]);dfs(k-3,d+1,3);swap(a[k-3],a[k]);}
    //mvdown 把空格往下
    if(k<7&&bef!=3){swap(a[k+3],a[k]);dfs(k+3,d+1,1);swap(a[k+3],a[k]);}
    //mvleft 往左
    if(k%3!=1&&bef!=2){swap(a[k-1],a[k]);dfs(k-1,d+1,4);swap(a[k-1],a[k]);}
    //mvright 往右
    if(k%3!=0&&bef!=4){swap(a[k+1],a[k]);dfs(k+1,d+1,2);swap(a[k+1],a[k]);}
}
int main()
{
    //freopen("a.in","r",stdin);
    LL x;
    cin>>x;
    dep=0;
    while(1)
    {
        ++dep;//迭代加深
        int k=chai(x);
        dfs(k,1,0);
    }
    return 0;
}