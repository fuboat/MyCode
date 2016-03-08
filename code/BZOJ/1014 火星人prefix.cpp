// BZOJ #1014
// Fuboat
// Splay
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define rep(i, x, y) for(int i = x. _ = y; i >= _; i --)
#define U unsigned 
#define LL long long
#define lc ch[o][0]
#define rc ch[o][1]
#define CLEAR(a) memset(a, 0,sizeof(a))
const int MAXN = 200000 + 1000;
bool Chkmax(int &x, int y) { y > x? x = y, true : false; }
U LL Dx[MAXN];
struct Splay_tree{
	int sumv[MAXN], val[MAXN], fa[MAXN];
	int ch[MAXN][2];
	U LL HASH[MAXN];
	char s[MAXN];
	int sz, root;
	inline int Idx(char c)
	{
		if(c == '\0')
			return 0;
		return  c - 'a' + 1;
	}
	void Build(int pa, int o, int d)
	{
		if(pa)
			ch[pa][d] = o;
		if(o)
			fa[o] = pa;
	}
	
	void Maintain(int o)
	{
		if(o == 0)
			return ;

		sumv[o]  = sumv[lc] + sumv[rc] + 1;
		HASH[o]  = HASH[lc];
		HASH[o] += val[o] * Dx[sumv[lc]];
		HASH[o] += HASH[rc] * Dx[sumv[lc] + 1];
	}
	
	void Rotate(int o)
	{
		int pa = fa[o], up = fa[pa], d = (ch[pa][1] == o);

		Build(up, o, ch[up][1] == pa);
		Build(pa, ch[o][!d], d);
		Build(o, pa, !d);
		// Don't fix 'up' and 'pa' there!

		Maintain(pa);
		Maintain(o);
	}
	
	void Splay(int o, int F)
	{
		int pa, up;
		while(fa[o] != F) {
			pa = fa[o];
			up = fa[pa];
			if(up == F) {
				Rotate(o);
				break;
			} else if((ch[up][0] == pa) ^ (ch[pa][0] == o))
				Rotate(o);
			else Rotate(pa);
			
			Rotate(o);
		}
		
		if(!F)
			root = o;
		Maintain(o);
	}
	
	int Get(int o, int k)
	{
		while(sumv[lc] + 1 != k) {
			if(k <= sumv[lc])
				o = lc;
			else {
				k -= sumv[lc] + 1;
				o = rc;
			}
		}
		return o;
	}
	
	void Insert(int pos, char c)
	{
		int o, son;
		o = Get(root, pos + 1);

		Splay(o, 0);
		son = Get(rc, 1);
		Splay(son, o);

		val[++ sz] = Idx(c);
		Build(son, sz, 0);
		Splay(sz, 0);
	}
	
	void Modify(int pos, char c)
	{
		int o;
		o = Get(root, pos + 1);

		Splay(o, 0);
		val[o] = Idx(c);
		Maintain(o);
	}
	
	U LL Hash(int o, int L)
	{
		int son;
		Splay(o, 0);
		son = Get(rc, L + 1);
		Splay(son, o);
		return HASH[ch[son][0]];
	}
	
	int Work(int a, int b)
	{
		int l = 0, r = sz - 1 - std::max(a, b), ans = 0, mid;
		a = Get(root, a);
		b = Get(root, b);

		while(l <= r) {
			mid = (l + r) >> 1;
			if(Hash(a, mid) == Hash(b, mid)) {
				ans = mid;
				l = mid + 1;
			} else 
				r = mid - 1;
		}
		return ans;
	}
	
	int Init(int l, int r)
	{
		if(l > r)
			return 0;

		int mid = (l + r) >> 1;
		if(mid - 2 >= 0)
			val[mid] = Idx(s[mid - 2]);
		
		Build(mid, Init(l, mid - 1), 0);
		Build(mid, Init(mid + 1, r), 1);
		Maintain(mid);
		Chkmax(sz, mid);
		// Make sure how big the splay tree is;

		return mid;
	}
}t;

int main()
{
	char T[10];
	int n, x, y, len;
	
	Dx[0] = 1;
	REP(i, 1, MAXN - 10)
		Dx[i] = Dx[i - 1] * 23333;
		// How to choose a good Hash-val?
		// Don't ask me... I tried many times there...
		// But as far as I know, prime is better.
	
	scanf("%s", t.s);
	scanf("%d", &n);
	len = strlen(t.s);
	t.Init(1, len + 2);
	t.root = (len + 3) / 2;
	t.sz = len + 2;
	REP(i, 1, n) {
		scanf("%s", T);
		switch(T[0]) {
			{
				case 'Q':
				scanf("%d%d", &x, &y);
				printf("%d\n", t.Work(x, y));
				break;
			}
			{
				case 'R':
				scanf("%d%s", &x, T);
				t.Modify(x, T[0]);
				break;
			}
			{
				case 'I':
				scanf("%d%s", &x, T);
				t.Insert(x, T[0]);
				break;
			}
		}
	}
}
