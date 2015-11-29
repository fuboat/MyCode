/*
	ID: fuboat
	FROM: UVALive
	TASK: 3029
	DATE: 2015.11.23
*/
/*
	mistake:
	1: ans should be 0 instead of -oo in init;
	2: left[][], right[][], up[][] can't be used again in different case; 
*/
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using std::max;
using std::min;
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define Rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
template <typename T> bool chkmin(T &x, T y){return y < x? (x = y, true) : false;}
template <typename T> bool chkmax(T &x, T y){return y > x? (x = y, true) : false;}
const int MAXN = 1000, oo = 0x7fffffff;

int up[MAXN + 100][MAXN + 100], left[MAXN + 100][MAXN + 100], right[MAXN + 100][MAXN + 100];
bool a[MAXN + 100][MAXN + 100];

int main(){
	int T, m, n;
	scanf("%d", &T);
	while(T --){
		int ans = 0;
		scanf("%d%d", &m, &n);
		char c = 0;
		REP(i, 1, m) REP(j, 1, n){
			c = getchar();
			while(c == ' ' || c == '\n') c = getchar();
			if(c == 'F') a[i][j] = 1;
			else a[i][j] = 0;
		}
		REP(i, 1, m){
			int lo = 0;
			REP(j, 1, n){
				if(a[i][j]){
					left[i][j] = max(lo + 1, i == 1? -oo : left[i - 1][j]);
					up[i][j] = up[i - 1][j] + 1;
				}else{
					lo = j;
					up[i][j] = 0;
					left[i][j] = -oo;
				}
			}
			int ro = n + 1;
			Rep(j, n, 1){
				if(a[i][j]){
					right[i][j] = min(ro - 1, i == 1? oo : right[i - 1][j]);
					chkmax(ans, up[i][j] * (right[i][j] - left[i][j] + 1));
				}else{
					ro = j;
					right[i][j] = oo;
				}
			}
		}
		printf("%d\n", ans * 3);
	}
}
