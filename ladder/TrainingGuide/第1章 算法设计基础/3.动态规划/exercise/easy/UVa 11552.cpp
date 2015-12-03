/*
	FROM: UVa
	TASK: 11552
	ID: fuboat
	ALGORITHM: Dynamic Programming
	DATA STRUCTURE: Default
	MISTAKE:
	1. f[0][27] instead of f[0][i]. This is a serious mistake;
	2. 'num[i] == 1' and 'j == k' are special status;
	EXPERIENCE: (Sorry, there is nothing)
*/
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define Rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
#define LL long long
template <typename T> bool chkmin(T &x, T y){return y < x? (x = y, true) : false;}
template <typename T> bool chkmax(T &x, T y){return y > x? (x = y, true) : false;}
const int MAXL = 1000 + 100, oo = 0x7fffffff;
int e, k, L, num[MAXL], f[MAXL][27];
char s[MAXL];
bool ok[MAXL][27];

void Init()
{
	memset(ok, 0, sizeof(ok));
	memset(num, 0, sizeof(num));
	scanf("%d%s", &k, s);
	L = strlen(s);
	e = (L - 1) / k;
	REP(i, 0, L - 1){
		int now = i / k;
		bool &flag = ok[now][s[i] - 'a'];
		if(!flag){
			flag = 1;
			num[now] ++;
		}
	}
}

void Solve()
{
	int ans = oo;
	REP(i, 0, 25) if(ok[0][i]) f[0][i] = num[0];
	REP(i, 1, e)
		REP(j, 0, 25)
			if(ok[i][j]){
				int &now = f[i][j], *F = f[i - 1];
				now = 0x7fffffff;
				REP(k, 0, 25)
				if(ok[i - 1][k]){
					if(ok[i][k] && (num[i] == 1 || j != k))
						chkmin(now, F[k] + num[i] - 1);
					else chkmin(now, F[k] + num[i]);
				}
			}
	REP(i, 0, 25) if(ok[e][i]) chkmin(ans, f[e][i]);
	printf("%d\n", ans);
}

int main()
{
	int T;
	scanf("%d", &T);
	while(T --){
		Init();
		Solve();
	}
}
