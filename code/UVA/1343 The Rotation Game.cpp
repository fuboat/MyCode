#include <cstdio>
#include <cstring>
#include <iostream>
#define REP(i,x,y) for(int i=x,_end_=y;i<=_end_;i++)
#define Rep(i,x,y) for(int i=x,_end_=y;i>=_end_;i--)
const int oo = 0x3f3f3f3f;
const int D[8][9]=
{
	{22, 0, 2, 6,11,15,20,22, 0},//A
	{23, 1, 3, 8,12,17,21,23, 1},//B
	{10, 4, 5, 6, 7, 8, 9,10, 4},//C
	{19,13,14,15,16,17,18,19,13},//D
	{ 1,23,21,17,12, 8, 3, 1,23},//E
	{ 0,22,20,15,11, 6, 2, 0,22},//F
	{19,13,14,15,16,17,18,19,13},//G
	{10, 4, 5, 6, 7, 8, 9,10, 4} //H
};
const int A[]={6,7,8,11,12,15,16,17};
char X[]="ABCDEFGH";
int l[24],ans[100000],best = oo;
bool ok[17000000];
//void bfs();
bool init(){
	scanf("%1d",&l[23]);
	if(!l[23])return 0;
	Rep(i,22,0) scanf("%1d",&l[i]);
	return 1;
}

bool pd(int k){
 	REP(i,0,7)
		if(!(k & 1<<A[i]))return 0;
	return 1;
}

bool dfs(int from,int deep){
	ok[from] = true;
	if(pd(from))
		if(deep < best){
			best = deep;
			return true;
		}
		else return false;
	int next;
	REP(i,0,7){
		next = from;
		const int *d = D[i];
		REP(j,1,7){
				if(from & 1<<d[j+1])
					next |= 1<<d[j];
				else next &= ~(1<<d[j]);
			}
		if(!ok[next]){
			if(dfs(next,deep + 1)){
				ans[deep + 1] = i;
				return true;
			}
		}
	}
	ok[next] = false;
}

void solve(int k){
	memset(ok,0,sizeof(ok));
	int from = 0;
	REP(i,0,23)
		if(l[i] == k)from |= 1<<i;
	//bfs();
	dfs(from,0);
}

int main(){
	for(;;){
		if(!init()) return 0;
		REP(i,1,3) solve(i);
		REP(i,1,best)
			printf("%c",X[ans[i]]);
		printf("\n%d\n",best);
	}
}
/*
void bfs(){
	memset(ok,0,sizeof(ok));
	int head = 0,tail = 1;
	ok[h[1]] = 1;
	do{
		head ++;
		int from = h[head];
		REP(i,0,3){
			const int *d=D[i];
			int temp = from;
			REP(j,1,7){
				if(temp & 1<<d[j+1]) from |= 1<<d[j];
				else{
					from &= ~(1<<d[j]);
				}
			}
			if(!ok[from]){
				tail++,ok[from] = 1,h[tail] = from,u[tail] = head,f[tail] = i<<1;
				if(pd(from)) ANS(tail);
				return ;
			}
			from = temp;
			REP(j,1,7){
				if(temp & 1<<d[j-1]) from |= 1<<d[j];
				else{
					from &= ~(1<<d[j]);
				}
			}
			if(!ok[from]){
				tail++,ok[from] = 1,h[tail] = from,u[tail] = head,f[tail] = i<<1|1;
				if(pd(from)) ANS(tail);
				return ;
			}
		}
	}while(head!=tail);
}
*/
