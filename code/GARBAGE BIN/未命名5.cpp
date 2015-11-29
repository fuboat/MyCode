#include<iostream>
#include<cstdio>
#define MAXN (500 + 10)
#define For(i,x,y) for(int i=(x);i<=(y);i++)
#include<algorithm>
#define LL unsigned long long
using namespace std;
struct node{
	LL x,y,h;
}a[MAXN*MAXN+MAXN];
LL d[4][2]={{-1,0},{1,0},{0,1},{0,-1}};
LL maxn,s[MAXN][MAXN],h[MAXN][MAXN];
bool comp(node a,node b){
	return a.h>b.h;
}
int main(){
	int n,m,num=0;
	scanf("%d%d",&n,&m);
	For(i,1,n)For(j,1,m){
		LL w;
		scanf("%d",&w);
		num++;a[num].h=w;a[num].x=i;a[num].y=j;
		h[i][j]=w;
	}
	sort(a+1,a+num+1,comp);
	For(i,1,num){
		LL x=a[i].x,y=a[i].y;
		For(i,0,3)
			if(h[x+d[i][0]][y+d[i][1]]>h[x][y])
			s[x][y]=max(s[x][y],s[x+d[i][0]][y+d[i][1]]);
		s[x][y]++;
		maxn=max(s[x][y],maxn);
	}
	printf("%lld\n",maxn);
}
