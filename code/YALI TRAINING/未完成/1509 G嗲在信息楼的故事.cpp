#include<iostream>
#include<cstdio>
#include<cstring>
#define MAXN 5000
using namespace std;
int m,n,k,i1,j1,i0,j0,minx=0x7fffffff;
int s[MAXN][MAXN],d[4][2]={{-1,0},{1,0},{0,-1},{0,1}};
int a[2][MAXN*MAXN][2],step[MAXN][MAXN];
bool ok(int,int);
void bfs();
int main(){
	memset(step,0x7f,sizeof(step));
	scanf("%d%d%d",&m,&n,&k);
	char z;
	for(int i=1;i<=m;i++)
		for(int j=1;j<=n;j++){
			z=getchar();
			while(z==' '||z=='\n')z=getchar();
			switch (z){
				case 'D':i1=i,j1=j;break;
				case 'X':s[i][j]=1;break;
				case 'G':i0=i,j0=j,step[i0][j0]=0;break;
				case '.':break;
			}
		}
	bfs();
	if(step[i1][j1]>=200000)printf("Help me!");
	else printf("%d\n",step[i1][j1]);
}
void bfs(){
	int tot=0,h=0,t=1,x,y,z1,z2;
	a[1][1][0]=i0,a[1][1][1]=j0;
	do{
		if(tot>k)return ;
		h=1-h;
		int t0=0;
		for(int i=0;i<=3;i++){
			z1=d[i][0],z2=d[i][1];
			for(int i=1;i<=t;i++){
				x=a[h][i][0];
				y=a[h][i][1];
				while(ok(x+z1,y+z2)){
					x+=z1;y+=z2;
					if(step[x][y]<step[x-z1][y-z2]+1)continue;
					t0++;
					a[1-h][t0][0]=x;
					a[1-h][t0][1]=y;
					step[x][y]=step[x-z1][y-z2]+1;
				}
			}
		}
		t=t0;
		tot++;
	}while(t);
}
bool ok(int x,int y){
	if(min(x,y)<=0||x>m||y>n||s[x][y]==1)
		return 0;
	return 1;
}
