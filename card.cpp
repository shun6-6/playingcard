#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
 
struct node
{
    int num,mark;
} white[10],black[10];
 
int cmp(node a,node b)
{
    return a.num<b.num;
}
 
int  set(char c)
{
    if(c<='9' && c>='2')
        return c-'0';
    if(c == 'T')
        return 10;
    if(c == 'J')
        return 11;
    if(c == 'Q')
        return 12;
    if(c == 'K')
        return 13;
    if(c == 'A')
        return 14;
    if(c == 'C')
        return 1;
    if(c == 'D')
        return 2;
    if(c == 'H')
        return 3;
    if(c == 'S')
        return 4;
}
 
int up[10];
 
int same(node *a)
{
    int i,l = 0;
    for(i = 2; i<=5; i++)
        if(a[i].num!=a[i-1].num)
            up[l++] = i;
    return l;
}
/*
我们用数字表示牌面
1-同花顺
2-四条
3-葫芦
4-同花
5-顺子
6-三条
7-两对
8-一对
9-单牌
*/
int judge(node *a)
{
    int flag1 = 0;
    int flag2 = 0;
    if(a[1].mark == a[2].mark && a[2].mark == a[3].mark &&a[3].mark == a[4].mark &&a[4].mark == a[5].mark)
        flag1 = 1;
    if(a[1].num+1 == a[2].num && a[2].num+1 == a[3].num &&a[3].num+1 == a[4].num &&a[4].num+1 == a[5].num)
        flag2 = 1;
    if(flag1 && flag2)
        return 1;
   else  if(flag1 && !flag2)
        return 4;
    else if(flag2 && !flag1)
        return 5;
    int k = same(a);
    if(k == 0)
        return 2;
    else if(k == 1)
    {
        if(up[0] == 2 || up[0] == 5)
            return 2;
        if(up[0] == 3 || up[0] == 4)
            return 3;
    }
    else if(k == 2)
    {
        if(up[0] == 2 && up[1] == 3 || up[0] == 4 && up[1] == 5 || up[0] == 2 && up[1] == 5)
            return 6;
        else
            return 7;
    }
    else if(k == 3)
        return 8;
    else if(k == 4)
        return 9;
    return 0;
}
 
int find_one(node *a)
{
    int i;
    for(i = 1; i<=5; i++)
    {
        if(i == 1 && a[i].num!=a[i+1].num)
            return 1;
        if(i == 5 && a[i].num!=a[i-1].num)
            return 5;
        if(a[i].num!=a[i-1].num && a[i].num!=a[i+1].num)
            return i;
    }
    return 0;
}
 
int find_pair(node *a)
{
    int i;
    for(i = 1; i<=5; i++)
    {
        if(i == 1 && a[i].num == a[i+1].num)
            return 2;
        if(a[i].num == a[i-1].num)
            return i;
    }
    return 0;
}
 
int compare(int x)
{
    int i,j,a,b;
    if(x == 1 || x == 5)
    {
        if(white[5].num>black[5].num)
            return -1;
        else if(white[5].num<black[5].num)
            return 1;
        return 0;
    }
    else if(x == 2 || x == 3 || x == 6)
    {
        if(white[3].num>black[3].num)
            return -1;
        else if(white[3].num<black[3].num)
            return 1;
        return 0;
    }
    else if(x == 4 || x == 9)
    {
        for(i = 5; i>=1; i--)
        {
            if(black[i].num<white[i].num)return -1;
            else if(black[i].num>white[i].num)
                return 1;
        }
        return 0;
    }
    else if(x == 7)
    {
        if(white[4].num>black[4].num)
            return -1;
        else if(white[4].num<black[4].num)
            return 1;
        else
        {
            if(white[2].num>black[2].num)
                return -1;
            else if(white[2].num<black[2].num)
                return 1;
            int a = find_one(white);
            int b = find_one(black);
            if(black[b].num<white[a].num)
                return -1;
            else if(black[b].num>white[a].num)
                return 1;
            return 0;
        }
    }
    else if(x == 8)
    {
        int a = find_pair(white);
        int b = find_pair(black);
        int tem_w[10],tem_b[10],i,lb = 1,lw = 1;
        if(white[a].num>black[b].num)
            return -1;
        else if(white[a].num<black[b].num)
            return 1;
        for(i = 1; i<=5; i++)
        {
            if(i!=a && i!=a-1)
                tem_w[lw++] = white[i].num;
            if(i!=b && i!=b-1)
                tem_b[lb++] = black[i].num;
        }
        for(i = 3; i>=1; i--)
        {
            if(tem_w[i]>tem_b[i])
                return -1;
            else if(tem_b[i]>tem_w[i])
                return 1;
        }
        return 0;
    }
    return 0;
}
 
int main()
{
    char str[5];
    int sumb,sumw,j,k,i;
    while(~scanf("%2s",str))
    {
        j = 1;
        k = 1;
        black[j].num = set(str[0]);
        black[j++].mark = set(str[1]);
        for(i = 2; i<=10; i++)
        {
            scanf("%2s",str);
            if(i<6)
            {
                black[j].num = set(str[0]);
                black[j++].mark = set(str[1]);
            }
            else
            {
                white[k].num = set(str[0]);
                white[k++].mark = set(str[1]);
            }
        }
        sort(black+1,black+6,cmp);
        sort(white+1,white+6,cmp);
        sumb = judge(black);
        sumw = judge(white);
        if(sumb>sumw)
            printf("White wins.\n");
        else if(sumb<sumw)
            printf("Black wins.\n");
        else
        {
            int flag = compare(sumb);
            if(flag == -1)
                printf("White wins.\n");
            else if(flag == 1)
                printf("Black wins.\n");
            else
                printf("Tie.\n");
        }
    }
 
    return 0;
}


