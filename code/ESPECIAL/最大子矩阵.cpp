#include<iostream>
#include<cstdio>
#define INF 0x7fffffff
using namespace std;
int a[101][101],ans[101],sum[101][101],maxn=-INF;
int main(){
	int n;
	scanf("%d" ,&n);
	for(int i = 1;i <= n;i ++)
		for(int j = 1;j <= n;j ++)
		{
			int x;
			scanf("%d", &x);
			a[i][j] = a[i][j-1] + x;//第i行从a[i][0]到a[i][j]的连续和 
			sum[i][j] = sum[i-1][j] + a[i][j];//点(0,0)和点(i,j)围成的矩阵的元素和 
		}
	for(int i = 1;i <= n;i ++)
		for(int j = i;j <= n;j ++)
		{
			for(int k = 1;k <= n;k ++)
				ans[k] = sum[j][k] - sum[i-1][k];//点(i,0)和点(j,k)围成的矩阵的元素和 
			int num=0,minx=0;
			for(int k = 1;k <= n;k ++)
			{
				maxn = max(ans[k] - ans[num],maxn);
				if(ans[k] < minx)
					num = k,minx = ans[k]; 
			}
		} 				
	printf("%d", maxn);
	return 0;
}
