// BZOJ #1187
// Fuboat
// DP
#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
#include <map>
#define VI vector<int>
#define MVIIit MVII::iterator
#define MVII map<vector<int>, int>
#define LL long long
#define REP(i, x, y) for (int i = x, _ = y; i <= _; i ++)
#define REPit(i, a) for (MVIIit it = a.begin(), _ = a.end(); i != _; i ++) 
template <typename T> bool Chkmax(T &x, T y) { return x < y? x = y, true : false; }
const int MAXN = 200 + 100, MAXM = 6 + 6, MAXS = 3000 + 100, oo = 0x3f3f3f3f;
using std::map;
using std::vector;
int n, m, ans = -oo;
int a[MAXN][MAXM];
MVII dp[MAXN][MAXM];
void Update(int x, int y, VI DP, int f)
{
	if (y > m) {
		if (DP.back())
			return ;
		
		x ++;
		y = 1;
		DP.insert(DP.begin(), 0);
		DP.pop_back();
	}
	
	if (dp[x][y].count(DP))
		Chkmax(dp[x][y][DP], f);
	else
		dp[x][y][DP] = f;
}
void Go(int x, int y, MVIIit s)
{
	#define UpdateAns() Update(x, y + 1, DP, s->second + more)
	VI DP = s->first;
	int f1 = DP[y], f2 = DP[y + 1], minf = std::min(f1, f2), maxf = std::max(f1, f2), cnt = 0, more = a[x][y];
	// there is 'DP[y] and 'DP[y + 1]', not 'DP[x]' or 'DP[x + 1]';
	
	REP (i, 1, m + 1)
		Chkmax(cnt, DP[i]);
		
//	printf("Go(x=%d,y=%d,f=%d,s=(", x, y,s->second);
//	REP (i, 1, m + 1)
//		printf(i == m + 1? "%d))\n" : "%d,", DP[i]);

	if (!f1 && !f2) {
		DP[y] = DP[y + 1] = cnt + 1;
		UpdateAns();
		DP[y] = DP[y + 1] = 0;
		more = 0;
		UpdateAns();
	} else if (f1 && !f2) {
		DP[y] = f1, DP[y + 1] = 0;
		UpdateAns();
		DP[y] = 0, DP[y + 1] = f1;
		UpdateAns();
	} else if (!f1 && f2) {
		DP[y] = f2, DP[y + 1] = 0;
		UpdateAns();
		DP[y] = 0, DP[y + 1] = f2;
		UpdateAns();
	} else if (f1 && f2) {
		if (f1 != f2) {
			DP[y] = DP[y + 1] = 0;
			// Don't forget to CLEAR 'DP[y]' and 'DP[y + 1]'!
			REP (i, 0, DP.size() - 1)
			if (DP[i] == f1 || DP[i] == f2)
				DP[i] = minf;
			else if (DP[i] > maxf)
				DP[i] --;
			UpdateAns();
		} else if (cnt == 1)
			Chkmax(ans, s->second + more); 
	}
	#undef UpdateAns
}
void Init()
{
	REP (i, 1, n)
		REP (j, 1, m)
			scanf("%d", &a[i][j]);
	Update(0, m + 1, vector<int>(m + 2, 0), 0);
}
void Solve()
{
	REP (i, 1, n)
		REP (j, 1, m)
			REPit (it, dp[i][j])
				Go(i, j, it);
	printf("%d\n", ans);
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("1187.in", "r", stdin);
	freopen("1187.out", "w", stdout); 
#endif

	scanf("%d%d", &n, &m);
	Init();
	Solve();
}
