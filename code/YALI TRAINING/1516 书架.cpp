#include <cstdio>
#include <algorithm>
#include <iostream>
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define lc son[o][0]
#define rc son[o][1]
using std::swap;
const int MAXN = 80000 + 1000;
int a[MAXN];
int n;
struct Splay_tree{
	int son[MAXN][2];
	int sumv[MAXN], num[MAXN], fa[MAXN], fnum[MAXN];
	int root;
	void Maintain(int o)
	{
		if(o) sumv[o] = sumv[lc] + sumv[rc] + 1;
		else sumv[o] = 0;
	}
	void Pushdown(int o){}
	void Build(int pa, int l, int r, bool d)
	{
		if(l > r) return ;
		int mid = (l + r) >> 1;
		if(!pa) root = mid;
		if(pa) son[fa[mid] = pa][d] = mid;
		if(l != r){
			Build(mid, l, mid - 1, 0);
			Build(mid, mid + 1, r, 1);
		}if(mid){
			fnum[num[mid] = a[mid - 1]] = mid;
			Maintain(mid);
		}
	}
	void Rotate(int o)
	{
		int pa = fa[o], up = fa[pa];
		bool d = (o == son[pa][1]);
		// Make sure whether or not it is left-turn;
		// if d == 1, it is left-turn;
		// else, it is right turn;
		Pushdown(pa);
		// We should Pushdown 'pa' first because 'pa' is the father of 'o';
		Pushdown(o);
		// 'Pushdown' may change the sons of node 'o';
		int c = son[o][!d];
		son[fa[o] = up][pa == son[up][1]] = o;
		// Exchange the fathers of 'pa' and 'o';
		// 'pa == son[up][1]' is for making sure the direct of turning;
		son[fa[c] = pa][d] = c;
		son[fa[pa] = o][!d] = pa;
		Maintain(pa);
		// Do this first, because now 'o' is the father of 'pa';
		Maintain(o);
	}
	void Splay(int o, int F)
	{
		if(F == 0)
		if(!o) return ;
		while(fa[o] != F){
			int pa = fa[o], up = fa[pa];
			if(up == F){ Rotate(o); break; }
			else if((son[up][0] == pa) ^ (son[pa][0] == o))
			// If the value is true, the three node('o', 'pa', 'up') is on the same line(三点共线); 
				Rotate(pa), Rotate(o);
			else Rotate(o), Rotate(o);
		}
		if(!F) root = o;
	}
	void Swap(int x, int y)
	{
		swap(num[x], num[y]);
		fnum[num[x]] = x, fnum[num[y]] = y;
	}
	void Insert(int o, int d)
	{
		if(!d) return;
		else if(d == -1) d = 0;
		o = fnum[o];
		Splay(o, 0);
		Swap(o, Get(son[o][d], !d));
	}
	int Get(int o, bool d)
	{
		if(!o) return 0;
		while(son[o][d]) o = son[o][d];
		return o;
	}
	void Clear(int o)
	{ 
		fa[lc] = fa[rc] = 0;
		fa[o] = lc = rc = 0; 
		sumv[o] = 1;
	}
	void Put(int o, bool d)
	{
		o = fnum[o];
		Splay(o, 0);
		int pa = Get(son[o][d], d), up = Get(son[o][d], !d), c = son[o][!d];
		Clear(o);
		son[fa[c] = up][!d] = c;
		Splay(up, 0);
		son[fa[o] = pa][d] = o;
		Swap(pa, o);
		Splay(pa, 0);
	}
	int Ask(int o)
	{
		o = fnum[o];
		Splay(o, 0);
		return sumv[lc] - 1;
	}
	int Query(int k)
	{
		int o = root;
		while(sumv[lc] + 1 != k){
			if(k <= sumv[lc]) o = lc;
			else k -= sumv[lc] + 1, o = rc;
			// Remeber, 'k -= sumv[lc]' is not enough!
		}
		return num[o];
	}
}t;
int main()
{
	int m, x, y;
	char c[10];
	scanf("%d%d", &n, &m);
	REP(i, 1, n) scanf("%d", &a[i]);
	t.Build(0, 1, n + 2, 0);
	REP(i, 1, m){
		scanf("%s%d", c, &x);
		switch(c[0]){
			case 'A': printf("%d\n", t.Ask(x)); break;
			case 'B': t.Put(x, 1); break;
			case 'I':
				scanf("%d", &y);
				t.Insert(x, y); 
				break;
			case 'Q': printf("%d\n", t.Query(x + 1)); break;
			case 'T': t.Put(x, 0); break;
		}
	}
}

