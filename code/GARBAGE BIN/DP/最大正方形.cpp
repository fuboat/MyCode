#include<cstdio>
#define MAXN 1600
int min(int x,int y){
	if(x<y)return x;
	return y;
}
short a[MAXN][MAXN];
int main(){
	int m,n;
	scanf("%d%d",&m,&n);
	for(int i=1;i<=m;i++)
		for(int j=1;j<=n;j++){
			int x;
			scanf("%d",&x);
			if(x==0)a[i][j]=-1;
			else a[i][j]=1;
		}
	for(int s=2;s<=min(m,n);s++){
		bool flag=0;
		for(int i=1;i<=n-s+1;i++)
			for(int j=1;j<=n-s+1;j++)
				if(!a[i][j]||!a[i+1][j]||!a[i][j+1]||!a[i+1][j+1]){
					a[i][j]=0;continue;
				}
				else if(a[i][j]==a[i][j+1]||a[i+1][j]==a[i+1][j+1]){
					a[i][j]=0;continue;
				}
				else if(a[i+1][j+1]!=a[i][j]||a[i][j+1]!=a[i+1][j])continue;
				else flag=1;
		if(!flag){
			printf("%d\n",s-1);
			return 0;
		}
	}
	printf("%d\n",min(m,n));
}
		
