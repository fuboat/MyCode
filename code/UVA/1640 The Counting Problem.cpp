#include<iostream>
#include<cstdio>
#include<cstring>
#define FOR(i,x,y) for(int i=x;i<=y;i++)
#define For(i,x,y) for(int i=x;i>=y;i--)
#define REP(i) for(int i=0;i<10;i++)
#define empty(x) memset(x,0,sizeof(x))
using namespace std;
int ret[2000][10],ret_cnt;
int ans[10],sum[10];

int ycl(int n){    //n个自由位时各数的数量 
	if(!n)return 1;
	int x=1;
	FOR(i,1,n-1) x*=10;
	REP(i) ans[i]+=n*x;
	return x*10;
}
void solve(int r,int n){
	int r0=r,s[10]={0};
	while(r0){
		s[r0%10]++;
		r0/=10;
	}
	int sum=ycl(n);
	REP(i) ans[i]+=s[i]*sum;
}

int Count(int r){
	empty(ans);
	int tmp=r,s[10]={0},len=0;
	while(tmp){
		s[++len]=tmp%10;
		tmp/=10;
	}
	if(r>=10)ycl(1);
    else ans[0]++;
	FOR(j,2,len-1)FOR(i,1,9)solve(i,j-1);//不允许有前导零的自由位 
	int T=s[len];
	FOR(j,1,s[len]-1)
		solve(j,len-1);
	For(i,len-1,1){
		FOR(j,0,s[i]-1)
			solve(T*10+j,i-1);
		T=T*10+s[i];
	}
	solve(r,0);
	ret_cnt++;
	REP(i)ret[ret_cnt][i]=ans[i];
}
int main(){
	int n=0,m=0;
	while(scanf("%d%d",&n,&m)==2&&n&&m){
		if(n>m)n^=m^=n^=m;
		Count(n-1);
		Count(m);
		printf("%d",ret[ret_cnt][0]-ret[ret_cnt-1][0]);
		REP(i)
			printf(" %d",ret[ret_cnt][i]-ret[ret_cnt-1][i]);
		putchar('\n');
	}
}
