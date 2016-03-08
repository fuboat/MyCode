// BZOJ #1219
// [HNOI2003] 
// Fuboat
// The Dynamic Programming
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
using std::priority_queue;
using std::min;
const int MAXN = 2000 + 1000;
int n, EndMin;
int a[MAXN], InFact[MAXN], f[MAXN], g[MAXN];
// 'InFact[]'用于处理前导零; 
char s[MAXN];
inline bool Bigger(int h1, int e1, int h2, int e2)
{
	h1 = min(e1, InFact[h1]);
	h2 = min(e2, InFact[h2]);
	if (e1 - h1 != e2 - h2)
		return e1 - h1 > e2 - h2;
	else return strncmp(s + h1, s + h2, e1 - h1 + 1) > 0;
}
void GetMinInTheEnd()
{
	int L, R, M;

	f[1] = 1;
	REP (i, 2, n) {
		rep (j, i, 1) {
		// 单调性在这儿不能用 
		// 这里最多改变左端点 
		// 显然没卵用...... 
			if (Bigger(j, i, f[j - 1], j - 1)) {
				f[i] = j;
				break;
			}
		}
	}
	
	EndMin = f[n];
	while (EndMin <= n && a[EndMin] == 0) { 
	// 处理最后一个数字的前导零(zero in the front) 
		EndMin ++;
	}
}
void GetMaxInTheBegin()
{
	int L, R, M, End = EndMin - 1;
	
	g[EndMin] = n;
	rep (i, EndMin - 1, 1) {
	// Not 'REP(...)'!
		if (InFact[i] == EndMin) {
		// 再次处理最后一个数字的前导零 
			g[i] = n; 
			continue;
		}
		
		rep (j, End, i)
			if (Bigger(j + 1, g[j + 1], i, j)) {
				g[i] = j;
				break;
			} else 
				End = j;
			// 传说这地方要用堆(heap) 
			// 然而我用的是单调性 
	}
}
void Init()
{
	n = strlen(s + 1);
	REP (i, 1, n)
		a[i] = s[i] - '0';
	
	InFact[n + 1] = n + 1;
	rep (i, n, 1) {
		if (a[i] == 0)
			InFact[i] = InFact[i + 1];
		else InFact[i] = i;
	}
}
void Solve()
{
	GetMinInTheEnd();
	GetMaxInTheBegin();
}
void Print()
{
	int pos = 1;
	while (true) {
		REP (i, pos, g[pos])
			printf("%d", a[i]);
		pos = g[pos] + 1;
		if(pos <= n)
			putchar(',');
		else break;
	}
	puts("");
}
int main()
{
	while (scanf("%s", s + 1) != EOF) {
		Init();
		Solve();
		Print();
	}
}
