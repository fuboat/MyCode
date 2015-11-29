#include<iostream>
#include<cstdio>
#include<algorithm>
#define For(i,x,y) for(int i=x;i<=y;i++)
using namespace std;
int ans;
int next[1000003][3];
vector<short int>a[1000003][10];
void readin(){
	scanf("%d",&ans);
	For(i,1,5){
		a[1][i].push_back(0);
		int w=0;
		For(j,1,7){
			int x;
			scanf("%d",&x);
			if(!x){w=j;break;}
			a[1][i].push_back(x);
		}
		if(w)For(j,w,7)a[1][i].push_back(0);
	}
}
void drop(int x){
	For(i,1,5)For(j,1,6)
		if(a[x][i][j]&&a[x][i][j+1]==0)
			swap(a[x][i][j+1],a[x][i][j]);
}
void disappear(int x){
	int NEXT=0;
	For(i,1,5)For(j,1,7){
		if(a[x][i][j]&&a[x][i][j]==a[x][i][j+1]&&a[x][i][j+1]==a[x][i][j+2])
			NEXT++;
			next[NEXT]={i,j};
			NEXT++;
			next[NEXT]={i,j+1};
			next[NEXT]={i,j+2};
		}
		if(a[x][i][j]&&a[x][i][j]==a[x][i+1][j]&&a[x][i+1][j]==a[x][i+2][j])
			NEXT++;next[NEXT]={i,j};NEXT++;next[NEXT]={i+1,j};next[NEXT]={i+2,j};
		}
	}
	For(i,1,NEXT)a[next[i][0]][next[i][1]]=0;
	drop(x);
}
void hash(int x){
	
}
void change(int &t){
	
}
void bfs(){
	int h=0,t=1;
	do{
		h++;
		int t0=t;
		if(!change(t)){
			print();
			return ;
		}
	}while(h!=t);
	return;
}
int main(){
	readin();
	bfs();
}
