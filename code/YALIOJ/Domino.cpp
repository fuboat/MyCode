#include<cstdio>
#include<cstring>
#define MAX 7
int f[500][2],s[MAX][MAX],b[MAX],ans[500],num,c[500],n;
void dfs(int k){
	for(int i=0;i<MAX;i++)
		while(s[k][i]&&s[i][k]){
			s[k][i]--;
			s[i][k]--;
			dfs(i);
		}
	ans[++num]=k;
}
void solve(){
	for(int j=num;j>=2;j--){
		for(int i=1;i<=n;i++){
			if(c[i])continue;
			else if(f[i][0]==ans[j]&&f[i][1]==ans[j-1])
				{printf("%d +\n",i);c[i]=1;break;}
			else if(f[i][1]==ans[j]&&f[i][0]==ans[j-1])
				{printf("%d -\n",i);c[i]=1;break;}
		}
	}
}
int main(){
	while(scanf("%d",&n)==1){
		for(int i=1;i<=n;i++){
			int x,y;
			scanf("%d%d",&x,&y);
			f[i][0]=x,f[i][1]=y;
			s[x][y]++;
			s[y][x]++;
			b[x]++;b[y]++;
		}
		int _sum=0,begin=0;
		////for(int i=0;i<MAX;i++)
			//if(b[i])begin=i;
		for(int i=0;i<MAX;i++)
			if(b[i]%2){
				_sum++;
				begin=i;
			}
		if(_sum==1||_sum>2){
			printf("No solution\n");
			return 0;
		}
		dfs(begin);
		if(num<=n){
			printf("No solution\n");
			return 0;	
		}
		solve();
	}
}
