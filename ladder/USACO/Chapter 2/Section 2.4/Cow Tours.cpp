/*
	ID: fuboat
	TASK: cowtour
	LANG: C++
*/
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#define REP(i, x, y) for(int i = x; i <= y; i ++)
#define DB double
template <typename T> bool chkmin(T &x, T y){return y < x? (x = y, true) : false;}
template <typename T> bool chkmax(T &x, T y){return y > x? (x = y, true) : false;}
const int MAXN = 150 + 100;
bool s[MAXN][MAXN];
DB l[MAXN][MAXN], maxl[MAXN];
int n;
struct node{
	int x, y;
}a[MAXN];

DB dis(int i, int j)
{
	return sqrt((DB)pow((a[i].x - a[j].x), 2) + pow((a[i].y - a[j].y), 2));
}

void Init()
{
	int x = 0;
	scanf("%d", &n);
	REP(i, 1, n)
		scanf("%d%d", &a[i].x, &a[i].y);
	REP(i, 1, n) REP(j, 1, n){
		char c;
		std::cin >> c;
		if(c == '1') l[i][j] = dis(i, j);
		else l[i][j] = 1e20;
		if(i == j) l[i][j] = 0;
	}
}

void floyd()
{
	REP(k, 1, n) REP(i, 1, n) REP(j, 1, n)
		if(l[i][k] + l[k][j] < l[i][j])
			l[i][j] = l[i][k] + l[k][j];
}

void Solve()
{
	DB ans = 1e10;
	floyd();
	REP(i, 1, n) REP(j, 1, n) if(l[i][j] != 1e20) chkmax(maxl[i], l[i][j]);
	REP(i, 1, n) REP(j, 1, n)
		if(l[i][j] > 1e15)
			chkmin(ans, maxl[i] + maxl[j] + dis(i, j));
	REP(i, 1, n) chkmax(ans, maxl[i]);
	printf("%.6lf\n", ans);
}

int main()
{
	freopen("cowtour.in", "r", stdin);
	freopen("cowtour.out", "w", stdout);
	Init();
	Solve();
}
