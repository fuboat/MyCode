#include <cstdio>
#include <cstring>

const int MAX_N=16,INF=0x7fffffff;
int n,dis[MAX_N][MAX_N],ans=INF;
int f[1<<MAX_N][MAX_N];
bool ok[1<<MAX_N][MAX_N];
int min(int x,int y){
	return x>y? y:x;
}

void init(){
	scanf("%d",&n);
	for(int i = 0;i < n;i++)
		for(int j = 0;j < n;j++)
			scanf("%d",&dis[i][j]);
}

int solve(int s,int k){
	if(!(s^1<<k))return dis[0][k];
	if(ok[s][k])return f[s][k];
	ok[s][k]=1;
	for(int i = 0;i < n;i++)
		if(s&(1<<i) && i!=k)f[s][k] = min(f[s][k],solve(s^(1<<k),i)+dis[i][k]);
	return f[s][k];
}

int main(){
	init();
	memset(f,0x7f,sizeof(f));
	ans = min(ans,solve((1<<n)-1,0));
	printf("%d\n",ans);
}
