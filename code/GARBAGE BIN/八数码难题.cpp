#include<iostream>
#include<cstdio>
#include<cstring>
#define FOR(i) for(int i=0;i<=8;i++)
#define HASH 7000007
#define OK return 0
using namespace std;
bool ok[2][HASH];
int num[HASH],k[9]={2,3,2,3,4,3,2,3,2},r[2][400000],a[400000][9],b[400000][9],x,head=1,tail[2]={1,1},y;
int f[9][4]={{1,3,0,0},{0,2,4,0},{1,5,0,0},{0,4,6,0},{1,3,5,7},{2,4,8,0},{3,7,0,0},{4,6,8,0},{5,7,0,0}};
int main(){
 	FOR(i) scanf("%d",&a[1][i]);
 	FOR(i) scanf("%d",&b[1][i]);
	FOR(c) {x=x*10+a[1][c],y=y*10+b[1][c];}x=x%HASH,y=y%HASH;
	if(x==y){printf("0\n");return 0;}
	ok[0][x]=1,r[0][1]=0,ok[1][y]=1,r[1][0];
	do{
		int i0=0,i1=0,*t0=a[head],*t1=b[head];
		while(t0[i0]!=0)i0++; while(t1[i1]!=0)i1++;
		for(int j=0;j<k[i0];j++){
			int s0=f[i0][j];
			t0[i0]^=t0[s0]^=t0[i0]^=t0[s0];x=0;
			FOR(c) x=x*10+t0[c];x=x%HASH;
			if(!ok[0][x]){
				if(ok[1][x]){printf("%d\n",num[x]+r[0][head]+1);return 0;}
				++tail[0];ok[0][x]=1;r[0][tail[0]]=r[0][head]+1;num[x]=r[0][tail[0]];		
				memcpy(a[tail[0]],t0,sizeof(a[tail[0]]));
			}
			t0[i0]^=t0[s0]^=t0[i0]^=t0[s0];
		}
		for(int j=0;j<k[i1];j++){
			int s1=f[i1][j];
			t1[i1]^=t1[s1]^=t1[i1]^=t1[s1];x=0;y=0;
			FOR(c) y=y*10+t1[c];y=y%HASH;
			if(!ok[1][y]){
				if(ok[0][y]){printf("%d\n",num[y]+r[1][head]+1);return 0;}
				++tail[1];ok[1][y]=1;r[1][tail[1]]=r[1][head]+1;num[y]=r[1][tail[1]];
				memcpy(b[tail[1]],t1,sizeof(b[tail[1]]));
			}
			t1[i1]^=t1[s1]^=t1[i1]^=t1[s1];
		}
	}while(head<tail[0]&&head++<tail[1]);
	printf("-1\n");
}
