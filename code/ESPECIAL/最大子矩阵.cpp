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
			a[i][j] = a[i][j-1] + x;//��i�д�a[i][0]��a[i][j]�������� 
			sum[i][j] = sum[i-1][j] + a[i][j];//��(0,0)�͵�(i,j)Χ�ɵľ����Ԫ�غ� 
		}
	for(int i = 1;i <= n;i ++)
		for(int j = i;j <= n;j ++)
		{
			for(int k = 1;k <= n;k ++)
				ans[k] = sum[j][k] - sum[i-1][k];//��(i,0)�͵�(j,k)Χ�ɵľ����Ԫ�غ� 
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
