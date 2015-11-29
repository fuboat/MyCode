#include<cstdio>
#include<iostream>
#define MAX_N 300
int a[MAX_N][MAX_N],ok[MAX_N][MAX_N][MAX_N];
int sum[MAX_N][MAX_N][MAX_N],maxn;
int main(){
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=((n-i)<<1)+1;j++){
			char c;
			std::cin>>c;
			if(c=='-')a[i][j]=1;
		}
	for(int k=1;k<=n;k++)
		for(int i=1;i<=((n-k)<<1|1);i++)
			for(int j=i;j<=((n-k)<<1|1);j++)	
				if((ok[k][i][j-1]||j==i)&&a[k][j])
					ok[k][i][j]=1;
				else break;
	for(int k=1;k<=n;k++)
		for(int i=1;i<=(((n-k)<<1)+1);i+=2)
			for(int j=i;j<=(((n-k)<<1)+1);j+=2){
				if(ok[k][i][j])
					if(ok[k-1][i][j+2])sum[k][i][j]+=j-i+1+sum[k-1][i][j+2];
					else sum[k][i][j]=j-i+1;
				maxn=std::max(sum[k][i][j],maxn);
				if(sum[k][i][j])printf("f[%d][%d][%d]=%d\n",k,i,j,sum[k][i][j]);
			}
	printf("%d\n",maxn);
	return 0;
}
				
	
