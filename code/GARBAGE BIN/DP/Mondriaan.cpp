#include <iostream>
#include <stdio.h>
#include <cstring>
using namespace std;
const int N=12;
long long dp[N][1<<(N-1)]={0};
int row,col;
void dfs(int r,int c,int prestate,int nstate)
{
    if(c == col)
    {
        dp[r][nstate]+=dp[r-1][prestate];
        //cout<<dp[r][nstate]<<" "<<r<<" "<<nstate<<" "<<prestate<<endl;
        return;
    }
    if(c+1 <= col)
    {
        dfs(r,c+1,prestate<<1,nstate<<1|1);
        dfs(r,c+1,prestate<<1|1,nstate<<1);
    }
    if(c+2 <= col)
        dfs(r,c+2,prestate<<2|3,nstate<<2|3);
}
int main()
{
    int i;
    while(scanf("%d%d",&col,&row))
    {
        if(!col)
            break;
        if(1 == (col * row) %2)
        {
            printf("0\n");
            continue;
        }
        if(col > row) //行列变化，让列是小的值，因为行是线性的，而列的可能值是指数的
        {
            col^=row;
            row^=col;
            col^=row;
        }
        memset(dp,0,sizeof(dp));
        dp[0][(1<<col)-1]=1;
        for(i=1;i<=row;i++)
        {
            dfs(i,0,0,0);
        }
        printf("%I64d\n",dp[row][(1<<col)-1]);
    }
    return 0;
}

