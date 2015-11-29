#include<cstdio>
#include<algorithm>
using std::sort;
using std::max;
int d[4][2]={{0,1},{-1,0},{0,-1},{1,0}};
struct hill{
	int x,y,h;
}a[100001];
bool cmp(hill a,hill b){
	return a.h>b.h;
}
int h[102][102],f[102][102],maxx;
int main(){
	int m,n,num=0;
	scanf("%d%d",&m,&n);
	for(int i=1;i<=m;i++)
		for(int j=1;j<=n;j++){
			scanf("%d",&h[i][j]);
			a[++num].x=i,a[num].y=j,a[num].h=h[i][j];
		}
	sort(a+1,a+num+1,cmp);
	for(int i=1;i<=num;i++){
		f[a[i].x][a[i].y]=1;
		for(int j=0;j<=3;j++)
			if(h[a[i].x+d[j][0]][a[i].y+d[j][1]]>a[i].h)
				f[a[i].x][a[i].y]=max(f[a[i].x][a[i].y],f[a[i].x+d[j][0]][a[i].y+d[j][1]]+1);
		maxx=max(maxx,f[a[i].x][a[i].y]);
	}
	printf("%d\n",maxx);
}
	
