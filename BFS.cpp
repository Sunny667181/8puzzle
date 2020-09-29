// BFS
// �����������-����������
/*	������ʵ���������������Ҳ��Ϊ�Ź����⡣
	��3��3�����̣����а˸����ӣ�ÿ�������ϱ���1��8��ĳһ���֣���ͬ�����ϱ�����ֲ���ͬ��
	�����ϻ���һ���ո���ո����ڵ����ӿ����Ƶ��ո��С�
	Ҫ�����������ǣ�����һ����ʼ״̬��һ��Ŀ��״̬���ҳ�һ�ִӳ�ʼת���Ŀ��״̬���ƶ����Ӳ������ٵ��ƶ����衣
	��ν�����һ��״̬���������������ϵ�һ�ְڷ���
	�����������ʵ���Ͼ����ҳ��ӳ�ʼ״̬����Ŀ��״̬��������һϵ���м����״̬��
	˼·�ƶ��������٣���Ȼ��ʹ�ù��������������������������ÿ���ڵ��Ҫ��һ��3*3�ľ���
	����ʹ�ýṹ�壺
		struct node 
		{ 
			int xy[3][3]; 
		};
	ʵ�ַ������հ�������0���档
			  ���ܳ�ʼ�ڵ����Ϣ��Ŀ��ڵ����Ϣ�ҵ��հ����Ӻܼ򵥣�ֱ�ӱ����ͺá�
			  ��η�������x��y���꣬ʹ��һ�����ִ��档
				int loction(int num) 
				{ int i;
				  for (i = 0; i < 9; i++) 
					if (sh[num].xy[i / 3][i % 3] == 0) 
						return i; }
	�ӳ�ʼ�ڵ㿪ʼ�жϣ�Ȼ����չ�������������ƶ�����Ȼ����Ҫ���Ǿ����λ�ã�����˵�Ѿ����߽��ˣ��Ͳ���Խ���߽硣
	��Ҫ������ǰ�ƶ����ķ������Լ�¼������ǰ�ƶ����ķ��򣬿���ֱ�Ӽ��ڽṹ���
	ÿ����չ�Ľڵ�ͼ���������档
*/

//��������
/*
2 8 3
1 6 4
7 0 5
1 2 3
7 8 4
0 6 5
*/

#include <stdio.h>
#define N 102	//����ӳ�ʼ״̬��Ŀ��״̬������ƶ�����ΪN

// 3*3���飬����3*3���̣�1-8�������֣�0����ո�
struct node
{
    int xy[3][3];
    int dir;	//dir��0 1 2 3�ֱ������ �� �� ��
};
struct node sh[N], end; 
int count = 1;
 
void init()
{
    printf("������ʼ�ڵ��λ��:\n");
    int i, j;
    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
            scanf("%d", &sh[0].xy[i][j]);
    sh[0].dir = -1;
    printf("����Ŀ��ڵ��λ��:\n");
    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
            scanf("%d", &sh[N-1].xy[i][j]);
    sh[N-1].dir = -1;
}
 
//�ҳ�0��λ��
int location(int num)
{
    int i;
    for (i = 0; i < 9; i++)
        if (sh[num].xy[i / 3][i % 3] == 0) return i;
}
 
 
//���б��
long long sign(int num)
{
    long long sum;
    sum = sh[num].xy[0][0]*100000000 + sh[num].xy[0][1]*10000000 + sh[num].xy[0][2]*1000000 + sh[num].xy[1][0]*100000 + sh[num].xy[1][1]*10000 + sh[num].xy[1][2]*1000 + sh[num].xy[2][0]*100 + sh[num].xy[2][1]*10 + sh[num].xy[2][2];
    return sum;
}
 
void mobile(int num)
{
 
    int temp;
    int loc;	//�ҳ�0��λ��
    int up = 1, down = 1, left = 1, right = 1;
    loc = location(num);
    int stand = sh[num].dir;
    //dir��0 1 2 3�ֱ������ �� �� ��
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
	printf("��%d���ƶ���\n",num);
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
            printf("���������޴���\n");
            return 0;
        }
        if (sign(i) == sign(N-1))
        {
            printf("\n\n�ڵ�%d���ҵ���\n", i);
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