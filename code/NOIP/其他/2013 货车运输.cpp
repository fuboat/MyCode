#include<cstdio>
#include<cstring>
#include<algorithm> 
#include<vector>
#define MAX_M 50000
#define MAX_N 10000
#define INF 999999999
using std::vector;
using std::sort;
using std::min;
vector<int>vec[MAX_N],len[MAX_N];
int f[MAX_N],up[MAX_N],d[MAX_N],lim[MAX_N],n,m;
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
	up[x]=fa;
	d[x]=deep;
	for(int i=0;i<vec[x].size();i++)
		if(vec[x][i]!=fa){
			lim[vec[x][i]]=len[x][i];
			dfs(vec[x][i],x,deep+1);
		}
}
void lca_init(){
	for(int i=1;i<=n;i++)
			lim[i]=INF;
	dfs(1,1,0);
}
int lca(int a, int b){
	int fa=find(a),fb=find(b);
	if(fa!=fb)
		return -1;
	if(d[a]>d[b]) a^=b^=a^=b;
	int ans=INF;
	while(d[b]>d[a]){
		ans=min(lim[b],ans);
		b=up[b];
	}
	while(a!=b){
		ans=min(ans,min(lim[b],lim[a]));
		b=up[b];
		a=up[a];
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
int main(){
	n=readin(),m=readin();
	for(int i=1;i<=n;i++)f[i]=i;
	for(int i=1;i<=m;i++){
		s[i].x=readin();
		s[i].y=readin();
		s[i].w=readin();
	}
	kruskal();
	lca_init();
	int p=readin();
	for(int i=1;i<=p;i++){
		int x=readin(),y=readin();
		printf("%d\n",lca(x,y));
	}
}
	
	
