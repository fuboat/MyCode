// BZOJ #1269
// Fuboat
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define lc ch[o][0]
#define rc ch[o][1]
const int MAXN = 3 * 1e6 + 1e3;
struct Splay_tree{
	int sumv[MAXN], ch[MAXN][2], fa[MAXN], flag[MAXN];
	char val[MAXN];
	int root, sz;

	void Pushdown(int o)
	{
		if(flag[o]) {
			std::swap(lc, rc);
			// 'Swap' is necessary!
			flag[o] = 0;
			flag[lc] ^= 1;
			flag[rc] ^= 1;
		}
	}

	void Maintain(int o)
	{
		if(o)
			sumv[o] = sumv[lc] + sumv[rc] + 1;
	}

	void Build(int pa, int o, int d)
	{
		if(o != 0)
			fa[o] = pa;
  		if(pa)
			ch[pa][d] = o;
	}

	void Rotate(int o)
	{
		int pa = fa[o], up = fa[pa], d;
		Pushdown(pa);
		Pushdown(o);

		d = (ch[pa][1] == o);
		Build(up, o, ch[up][1] == pa);
		Build(pa, ch[o][!d], d);
		Build(o, pa, !d);

		Maintain(pa);
		Maintain(o);
	}

	void Splay(int o, int F)
	{
		int up, pa;
		Maintain(o);
		while(fa[o] != F) {
			pa = fa[o], up = fa[pa];
			if(fa[pa] == F) {
				Rotate(o);
				break;
			}
			else if((ch[pa][1] == o) ^ (ch[up][1] == pa))
				Rotate(o), Rotate(o);
			else Rotate(pa), Rotate(o);
		}

		if(!F)
			root = o;
		Pushdown(o);
		// Adding this is better.
	}

	int Get(int o, int x)
	{
		Pushdown(o);
		while(x != sumv[lc] + 1) {
			if(x <= sumv[lc])
				o = lc;
			else {
				x -= sumv[lc] + 1;
				o = rc;
			}
			Pushdown(o);
		}
		return o;
	}

	void Insert(int o, char *s)
	{
		int son, N, now;
		// There is 'k', not 'k + 1';
		N = strlen(s);

		Splay(o, 0);
		son = Get(rc, 1);
		Splay(son, 0);
		now = o;

		REP(i, 0, N - 1) {
			// There is 'N - 1'!
			val[++ sz] = s[i];
			Build(now, sz, 1);
			Maintain(now);
			Splay(sz, o);
			now = sz;
		}

		Splay(o, 0);
	}

	char Get(int o)
	{
		Splay(o, 0);
		return val[Get(rc, 1)];
	}

	void Delete(int o, int N)
	{
		int son;
		Splay(o, 0);
		son = Get(rc, N + 1);
		Splay(son, o);
		// Attention!
		// We can't use 'Splay(son, 0)'!
		// Because if you use it, 'o' may not be the left son of 'son'!
		// There are n nodes between them!

		o = son;
		fa[lc] = 0;
		lc = 0;
		
		Maintain(o);
		Maintain(fa[o]);
	}

	void Rotate(int o, int N)
	{
		int son;

		Splay(o, 0);
		son = Get(rc, N + 1);
		Splay(son, o);
		// Attention!
		// We can't use 'Splay(son, 0)'!
		// Because if you use it, 'o' may not be the left son of 'son'!
		// There are n nodes between them!

		o = son;
		flag[lc] ^= 1;

		Maintain(o);
		Maintain(fa[o]);
	}

	void Init()
	{
		sz = 2;
		Build(2, 1, 0);
		Splay(1, 0);
		root = 1;
	}

	void Prev(int &o)
	{
		Splay(o, 0);
		o = Get(lc, sumv[lc]);
	}

	void Next(int &o)
	{
		Splay(o, 0);
		o = Get(rc, 1);
	}
};

namespace solve
{
	char s[MAXN];
	int pos, n;
	Splay_tree t;

	void Insert()
	{
		int N;
		scanf("%d", &N);
		getchar(); 

		REP(i, 0, N - 1)
			s[i] = getchar();
		s[N] = 0;

		t.Insert(pos, s);
	}

	void Move()
	{
		int x;
		scanf("%d", &x);
		pos = t.Get(t.root, x + 1);
	}

	void Delete()
	{
		int N;
		scanf("%d", &N);
		t.Delete(pos, N);
	}

	void Rotate()
	{
		int N;
		scanf("%d", &N);
		t.Rotate(pos, N);
	}

	void Solve()
	{
		pos = 1;
		scanf("%d", &n);
		t.Init();

		REP(i, 1, n) {
			scanf("%s", s);
			switch(s[0]) {
				case 'I': Insert();    break;
				case 'N': t.Next(pos); break;
				case 'G': printf("%c\n", t.Get(pos));
				                       break;
				case 'M': Move();      break;
				case 'D': Delete();    break;
				case 'R': Rotate();    break;
				case 'P': t.Prev(pos); break;
			}
		}
	}
}

int main()
{
	solve::Solve();
}
