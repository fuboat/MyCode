/*
	ID: fuboat
	TASK: sort3
	LANG: C++
*/
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
#define LL long long
template <typename T> bool chkmin(T &x, T y){return y < x? (x = y, true) : false;}
template <typename T> bool chkmax(T &x, T y){return y > x? (x = y, true) : false;}
const int MAXN = 1000 + 100, MAXA = 3 + 2, oo = 0x7fffffff;
int g[MAXA][MAXA], a[MAXN], s[MAXN], n, ans;
bool vis[MAXA];

void update(int &k, int &x, int &y, int &z)
{
	int w = min(x, min(y, z));
	k += w, x -= w, y -= w, z -= w;
}

int main()
{
	freopen("sort3.in", "r", stdin);
	freopen("sort3.out", "w", stdout);
	scanf("%d", &n);
	REP(i, 1, n){
		scanf("%d", &a[i]);
		s[i] = a[i];
	}
	int num = 0;
	sort(s + 1, s + n + 1);
	REP(i, 1, n) if(s[i] != a[i])
		g[s[i]][a[i]] ++, num ++;
	g[0][0] = 0x7fffffff;
	REP(i, 1, 3) REP(j, 1, 3) if(i != j) 
	update(ans, g[i][j], g[j][i], g[0][0]);
	update(ans, g[1][2], g[2][3], g[3][1]);
	update(ans, g[3][2], g[2][1], g[1][3]);
	printf("%d\n", num - ans);
}
