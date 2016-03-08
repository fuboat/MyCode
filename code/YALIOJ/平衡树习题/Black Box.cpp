#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#define LL int
#define lc ch[o][0]
#define rc ch[o][1]
#define CLEAR(a) memset(a, 0, sizeof(a))
#define REP(i, x, y) for(register int i = x; i <= y; i ++)
#define rep(i, x, y) for(register int i = x; i >= y; i --)
using namespace std;
const int MAXN = 30000 + 1000;
int a[MAXN], ans[MAXN], que[MAXN];
struct Treap{
	int ch[MAXN][2];
	int sumv[MAXN], fa[MAXN], val[MAXN], r[MAXN];
	int root, sz;
	void Rotate(int &o, int d)
	{
		int k = ch[o][!d];
		ch[o][!d] = ch[k][d];
		ch[k][d] = o;
		Maintain(o);
		Maintain(k);
		o = k;
	}
	inline void Maintain(int o)
	{ 
		sumv[o] = 1;
		if(lc) sumv[o] += sumv[lc];
		if(rc) sumv[o] += sumv[rc];
	}
	void Insert(int &o, int x)
	{
		if(!o){
			o = ++ sz;
			val[o] = x;
			r[o] = rand();
		}else{
			bool d = (x >= val[o]);
			Insert(ch[o][d], x);
			if(o && r[ch[o][d]] > r[o])
				Rotate(o, !d);
		}
		Maintain(o);
	}
	int Query(int k)
	{
		int o = root;
		while(k != sumv[lc] + 1){
			if(k <= sumv[lc]) o = lc;
			else k -= sumv[lc] + 1, o = rc;
		}
		return val[o];
	}
}t;
int n, m;
void Init()
{
	scanf("%d%d", &n, &m);
	REP(i, 1, n) scanf("%d", &a[i]);
	REP(i, 1, m) scanf("%d", &que[i]);
}
void Solve()
{
	int cnt = 1;
	REP(i, 1, n){
		t.Insert(t.root, a[i]);
		while(cnt <= n && que[cnt] == i){
			printf("%d\n", t.Query(cnt));
			cnt ++;
		}
	}
}
int main()
{
	Init();
	Solve();
}
