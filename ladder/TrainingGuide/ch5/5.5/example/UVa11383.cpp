// UVa11383
// Bitpartitle
// Fuboat
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;
#ifdef WIN32
	#define ll "%I64d"
#else
	#define ll "%lld"
#endif
#define MSET(a, x) memset(a, x, sizeof(a))
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
#define LL long long
#define LD double
#define DEBUG(...) fprintf(stderr, __VA_ARGS__)
template <typename T> bool Chkmin(T &x, T y){ return y < x? (x = y, true) : false; }
template <typename T> bool Chkmax(T &x, T y){ return y > x? (x = y, true) : false; }
const int oo = 0x3f3f3f3f, MAXN = 500 + 10;
int val[MAXN][MAXN];
int S[MAXN], T[MAXN], slack[MAXN], Lx[MAXN], Ly[MAXN], link[MAXN];
int cur, n;
bool Match(int u)
{
	int t;
	S[u] = cur;
	REP(v, 1, n){
		if(T[v] == cur) continue;
		
		t = Lx[u] + Ly[v] - val[u][v];
		if(t > 0) Chkmin(slack[v], t);
		else{
			T[v] = cur;
			if(link[v] == 0 || Match(link[v])){
				link[v] = u;
				return true;
			}
		}
	}
	return false;
	// Don't forget return the bool;
}
void Update()
{
	int a = oo;
	REP(v, 1, n) if(T[v] < cur)
		Chkmin(a, slack[v]);
	REP(u, 1, n)
		if(S[u] == cur)
			Lx[u] -= a;
	REP(v, 1, n)
		if(T[v] == cur)
			Ly[v] += a;
		else slack[v] -= a;
	
}
void Init()
{
	MSET(S, 0);
	MSET(T, 0);
	MSET(link, 0);
	REP(u, 1, n) REP(v, 1, n)
		scanf("%d", &val[u][v]);
}
void Solve()
{
	int w, ans = 0;
	REP(u, 1, n){
		Lx[u] = 0;
		REP(v, 1, n)
			Chkmax(Lx[u], val[u][v]);
	}
	REP(u, 1, n){
		REP(v, 1, n) slack[v] = oo;
		for(cur ++; !Match(u); cur ++)
			Update();
	}
	REP(u, 1, n){
		printf(u == n? "%d\n" : "%d ", Lx[u]);
		ans += Lx[u];
	}
	REP(v, 1, n){
		printf(v == n? "%d\n" : "%d ", Ly[v]);
		ans += Ly[v];
	}
	printf("%d\n", ans);
}
int main()
{
	while(~scanf("%d", &n)){
		Init();
		Solve();
	}
}
