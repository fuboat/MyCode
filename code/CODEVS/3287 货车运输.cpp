#include<cstdio>
#include<cstring>
#include<algorithm> 
#include<vector>
#define MAX_M 50000
#define MAX_N 10000
#define MAX_D 12
#define INF 999999999
using std::vector;
using std::sort;
using std::min;
vector<int>vec[MAX_N],len[MAX_N];
int f[MAX_N],parent[MAX_N][MAX_D],d[MAX_N],lim[MAX_N][MAX_D],n,m;
struct line{
	int w,x,y;
}s[MAX_M];
bool cmp(line a,line b){
	return a.w>b.w;
}
int find(int x){
	if(x!=f[x])f[x]=find(f[x]);
	return f[x];
}
void Union(int x,int y){
	x=find(x);
	y=find(y);
	f[x]=y;
}
void dfs(int x, int fa, int deep){
	parent[x][0]=fa;
	d[x]=deep;
	for(int i=0;i<vec[x].size();i++)
		if(vec[x][i]!=fa){
			lim[vec[x][i]][0]=len[x][i];
			dfs(vec[x][i],x,deep+1);
		}
}
void lca_init(){
	for(int i=1;i<=n;i++)
		for(int j=1;j<MAX_D;j++)
			lim[i][j]=INF;
	dfs(1,1,0);
	for(int j=1;j<MAX_D;j++)
		for(int i=1;i<=n;i++){
			parent[i][j]=parent[parent[i][j-1]][j-1];
			lim[i][j]=min(lim[i][j-1],lim[parent[i][j-1]][j-1]);
		}
}
int lca(int a, int b){
	int fa=find(a),fb=find(b);
	if(fa!=fb)
		return -1;
	int ans=INF;
	if(d[a]>d[b]) a^=b^=a^=b;
	int H=d[b]-d[a];
	for(int i=0;H>0;i++){
		if(H&1)
			ans=min(ans,lim[b][i]),b=parent[b][i];
		H>>=1;
	}
	if(a==b) return ans;
	for(;;){
		int i;
		for(i=0;parent[a][i]!=parent[b][i];i++);
		if(i==0)
			return ans=min(ans,min(lim[a][i],lim[b][i]));
		ans=min(ans,min(lim[a][i-1], lim[b][i-1]));
		a=parent[a][i-1];b=parent[b][i-1];
	}
	return ans;
}
int readin(){
	int x=0;bool flag=0;char c=0;
	while(c=getchar()){
		if(c>='0'&&c<='9'){
			x=x*10+c-'0';
			flag=1;
		}
		else if(flag)return x;
	}
}
void kruskal(){
	sort(s+1,s+m+1,cmp);
	for(int i=1;i<=m;i++){
		int x=find(s[i].x),y=find(s[i].y),w=s[i].w;
		if(x==y)continue;
		vec[x].push_back(y);
		len[x].push_back(w);
		vec[y].push_back(x);
		len[y].push_back(w);
		f[x]=y;
	}
}
void init(){
	n=readin(),m=readin();
	for(int i=1;i<=n;i++)f[i]=i;
	for(int i=1;i<=m;i++){
		s[i].x=readin();
		s[i].y=readin();
		s[i].w=readin();
	}
}
void solve(){
	int p=readin();
	for(int i=1;i<=p;i++){
		int x=readin(),y=readin();
		printf("%d\n",lca(x,y));
	}
}
int main(){
	init();
	kruskal();
	lca_init();
	solve();
}
	
	
