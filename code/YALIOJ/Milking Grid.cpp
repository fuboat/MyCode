/*
	ID: fuboat
	TASK: 
*/
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

#define MSET(a, x) memset(a, x, sizeof(a))
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define Rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
#define LL long long
template <typename T> bool chkmin(T &x, T y){return y < x? (x = y, true) : false;}
template <typename T> bool chkmax(T &x, T y){return y > x? (x = y, true) : false;}
const int MAXC = 150 + 25, MAXR = 20000 + 1000;
char s[MAXR][MAXC];
char tmp[MAXR];
int ans[2][MAXR];
int f[MAXR];
int len, m, n;
void getFail(char *P, int len, int *ans)
{
	f[0] = 0; f[1] = 0;
	REP(i, 1, len - 1){
		int j = f[i];
		while(j && P[i] != P[j]) j = f[j];
		f[i + 1] = P[i] == P[j]? j + 1 : 0;
	}
	int j = len;
	do{
		ans[len - f[j]] ++;
		j = f[j];
	}while(j);
}
inline void Solve()
{
	int minr = n, minc = m;
	REP(i, 1, n) if(ans[0][i] == m) chkmin(minr, i);
	REP(i, 1, m) if(ans[1][i] == n) chkmin(minc, i);
	printf("%d\n", minc * minr);
}
inline void Init()
{
	scanf("%d%d", &m, &n);
	REP(i, 0, m - 1) scanf("%s", s[i]);
	REP(i, 0, m - 1) getFail(s[i], n, ans[0]);
	REP(i, 0, n - 1){
		REP(j, 0, m - 1) tmp[j] = s[j][i];
		getFail(tmp, m, ans[1]);
	}
}
int main()
{
	Init();
	Solve();
	return 0;
}
