/*
  ID: 60303451
  TASK: hamming
  LANG: C++
*/
#include <cstdio>
#include <iostream>
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)    
using namespace std;
const int MAXN = 64, MAXB = 8, MAXD = 7, MAXA = (1 << 9) - 1;
int n, b, d, cnt(0);
int ans[MAXN + 10];

void Begin()
{
	freopen("hamming.in", "r", stdin);
	freopen("hamming.out", "w", stdout);
}

bool Is_hamming(int x, int y)
{
	int tmp = x ^ y, ok(0);
	while(tmp){
		if(tmp & 1) ok ++;
		tmp >>= 1;
		if(ok == d) return true;
	}
	return false;
}		

void End()
{
	fclose(stdin);
	fclose(stdout);
}

int main()
{
    Begin();
    scanf("%d%d%d", &n, &b, &d);
    int maxa = (1 << (b + 1)) - 1;
    ans[++ cnt] = 0;
    REP(i, 1, maxa){
		bool flag = true;
    	REP(j, 1, cnt)
			if(!Is_hamming(i, ans[j])){
				flag = false;
				break;
			}
		if(flag) ans[++ cnt] = i;
		if(cnt == n) break;
	}
  	REP(i, 1, n){
		printf("%d", ans[i]);
		if(i == n || i % 10 == 0)
			putchar('\n');
		else putchar(' ');
	}
	End();
	return 0;
}
