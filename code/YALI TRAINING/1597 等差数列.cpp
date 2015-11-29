#include <iostream>
#include <cstdio>
#include <algorithm>

#define X first
#define Y second
#define MAXM 251
#define MAXN 26
#define MAXS 100000
#define REP(i,x,y) for(int i=x,_end_=y;i<=_end_;i++)
#define Rep(i,x,y) for(int i=x,_end_=y;i>=_end_;i--)
int a[MAXS],num,n,m,kind;
int ok[700000];
std::pair<int,int>ans[1000000];

void init(){
	scanf("%d%d",&n,&m);
	REP(i,0,m)REP(j,0,m)
		ok[i*i+j*j] = 1;
	REP(i,0,m*m + m*m)
	if(ok[i]){
		a[++num] = i;
		ok[i] = 1;
	}
}

bool find(int l,int r,int d){
	if(d==n){
		ans[++kind].Y=l;
		return 1;
	}
	int next = l*2 - r;
	return (next>=0 && ok[next])? find(next,l,d+1):0;
}

void print(){
	if(!kind)
		printf("NONE\n");
	REP(i,1,kind)
		printf("%d %d\n",ans[i].Y,ans[i].X);
}

void solve(){
	REP(i,1,num)Rep(j,i-1,1){
		if(a[i] < (n-1)*(a[i]-a[j]))
			break;
		if(find(a[j],a[i],2))
			ans[kind].X=a[i]-a[j];
	}
	sort(ans+1,ans+kind+1);
}

int main(){
	init();
	solve();
	print();
}
