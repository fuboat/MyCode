#include<iostream>
#include<cstdio>
#include<algorithm>
#define MAXN 500000 + 100
#define For(i,x,y) for(int i=(x);i<=(y);i++)
#define MAX(a1,a2,a3,a4) max(max(a1,a2),max(a3,a4))
using namespace std;
struct node{
	int x,y;
}a[MAXN];
bool comp(node a,node b){
	if(a.x<b.x)return 1;
	if(a.x>b.x)return 0;
	if(a.y>b.y)return 0;
	return 1;
}
int n,m,k,sum[MAXN],MINX,num;
int cnt(int x,int y){
	return MAX(a[x].x-a[y].x,a[y].x-a[x].x,a[x].y-a[y].y,a[y].y-a[x].y);
}
int main(){
	scanf("%d%d%d",&n,&m,&k);
	For(i,1,k){
		int x,y;
		scanf("%d%d",&x,&y);
		//if(hash(x,y))continue;
		num++;
		a[num].y=x,a[num].x=y;
	}
	MINX=m;
	sort(a+1,a+num+1,comp);
	For(i,1,num){
		int minx=a[i].x-1;
		For(j,1,i-1)
		minx=min(cnt(i,j)+sum[j]-1,minx);
		sum[i]=minx;
		MINX=min(minx+m-a[i].x,MINX);
	}
	printf("%d\n",MINX);
}
	
			
