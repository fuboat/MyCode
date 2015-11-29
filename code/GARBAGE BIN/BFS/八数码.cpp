#include<iostream>
#include<cstdio>
#include<cstring>
#define FOR(i) for(int i=0;i<=8;i++)
#define HASH 100007
using namespace std;
void bfs();
int change(int []);
bool ok[HASH];
int ANS[]={1,2,3,8,0,4,7,6,5};
int k[9]={2,3,2,3,4,3,2,3,2},r[400000],a[400000][9],ans=change(ANS),x,head=0,tail=1;;
int f[9][4]={{1,3,0,0},{0,2,4,0},{1,5,0,0},{0,4,6,0},{1,3,5,7},{2,4,8,0},{3,7,0,0},{4,6,8,0},{5,7,0,0}};
int main(){
 	FOR(i) a[1][i]=getchar()-'0';
	x=change(a[1]),ok[x]=1,r[1]=0;
	if(x==ans){
		printf("0\n");return 0;
	}
	do{
		int i=0,*t=a[head];
		while(t[i]!=0)
			i++;
		for(int j=0;j<k[i];j++){
			int s=f[i][j];
			t[i]^=t[s]^=t[i]^=t[s];
			x=change(t);
			if(x==ans){
				printf("%d\n",r[head]+1);return 0;
			}
			else if(!ok[x]){
				++tail,ok[x]=1,r[tail]=r[head]+1;
				memcpy(a[tail],t,sizeof(a[tail]));
			}
			t[i]^=t[s]^=t[i]^=t[s];
		}
	}while(head++<tail);
	printf("-1\n");
}
int change(int d[]){
	int x=0;
	FOR(i) x=x*10+d[i];
	//return x/10;
	return x%HASH;
}
