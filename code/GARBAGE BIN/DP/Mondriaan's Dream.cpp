#include<cstdio>
#include<cstring>
#define LL long long
LL f[12][10000];
int n;
void dfs(int i,int d,int now,int last){
	if(d==n){
		f[i][now]+=f[i-1][last];
		return ;
	}
	if(d+1<=n){
		dfs(i,d+1,now<<1|1,last<<1);
		dfs(i,d+1,now<<1,last<<1|1);
	}
	if(d+2<=n)
		dfs(i,d+2,now<<2|3,last<<2|3);
}
int main(){	
	int m;
	while(scanf("%d%d",&n,&m)){
		if(!n)break;
		if(1 == (n*m) %2)
        {
            printf("0\n");
            continue;
        }
		memset(f,0,sizeof(f));
		if(n>m)m^=n^=m^=n;
		f[0][(1<<n)-1]=1;
		for(int i=1;i<=m;i++)
			dfs(i,0,0,0);
		printf("%I64d\n",f[m][(1<<n)-1]);
	}
}
