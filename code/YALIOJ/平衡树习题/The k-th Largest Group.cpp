#include <cstdio>
#include <iostream>
#include <algorithm>
#define REP(i, x, y) for(register int i = x, _ = y; i <= _; i ++)
const int MAXN = 400000 + 10000;
int W;
int readin()
{
	int x = 0;
	char c = 0;
	bool flag = 0;
	while(c = getchar()){
		if('0' <= c && c <= '9') (x *= 10) += c - '0', flag = true;
		else if(flag) return x;
	}
}
struct Splay_tree{
	int sumv[MAXN], son[MAXN][2], fa[MAXN], f[MAXN], sz;
	int root;
	inline void Maintain(int o){
		int lc = son[o][0], rc = son[o][1];
		sumv[o] = sumv[lc] + sumv[rc];
		if(o) sumv[o] ++;
		else sumv[o] = 0;
	}
	void Build(int w, int o, int n)
	{
		if(!n) return ;
		if(!o){
			root = ++ sz;
			f[root] = w;
			fa[root] = 0;
			Build(w, root, n);
		}else{
			f[o] = w;
			n --;
			if(n >> 1){ son[o][0] = ++ sz; fa[sz] = o; Build(w, sz, n >> 1); };
			if(n - (n >> 1)){ son[o][1] = ++ sz; fa[sz] = o; Build(w, sz, n - (n >> 1)); };
		}
		if(o) Maintain(o);
	}
	inline void Rotate(int o)
	{
		int pa = fa[o], up = fa[pa], d = (o == son[pa][1]), c = son[o][d ^ 1];
		fa[o] = up; fa[pa] = o;
		if(up) son[up][pa == son[up][1]] = o;
		if(c) fa[c] = pa;
		son[pa][d] = c;	
		son[o][d ^ 1] = pa;
		fa[pa] = o;
		Maintain(o);
		Maintain(pa);
	}
	inline void Splay(int o, int F)
	{
		while(fa[o] != F){
			int pa = fa[o], up = fa[pa];
			if(up == F){ Rotate(o); break; }
			if((son[up][0] == pa) ^ (son[pa][0] == o))
				Rotate(pa), Rotate(o);
			else Rotate(o), Rotate(o);
		}
		if(F == 0) root = o;
	}
	inline void New(int w, int o, int d)
	{
		son[o][d] = ++ sz;
		sumv[sz] = 1;
		f[sz] = w;
		fa[sz] = o;
		Splay(sz, 0);
	}
	inline void Insert(int w, int o)
	{
		if(!o){
			root = ++ sz;
			fa[root] = 0;
			f[root] = w;
			sumv[root] = 1;
			return ;
		}
		bool d = (w > f[o]);
		while(son[o][d]){
			o = son[o][d];
			d = (w > f[o]);
		}
		New(w, o, d);
	}
	inline int Query(int o){
		#define lc son[o][0]
		#define rc son[o][1]
		while(W != f[o]) o = W < f[o]? lc : rc;
		return o;
	}
	inline int Query(int k, int o)
	{
		#define lc son[o][0]
		#define rc son[o][1]
		int self = sumv[rc] + 1;
		while(k != self){
			if(k <= self - 1) o = rc;
			else k -= self, o = lc;
			self = sumv[rc] + 1;
		}
		return f[o];
	}
	inline void Delete(int old)
	{
		Splay(old, 0);
		root = old;
		int lson = son[old][0], rson = son[old][1];
		if(!lson) root = rson, fa[rson] = 0;
		else if(!rson) root = lson, fa[lson] = 0;
		else if(lson && rson){
			root = lson;
			fa[lson] = 0;
			int o = root;
			while(son[o][1]) o = son[o][1];
			Splay(o, 0);
			fa[rson] = o;
			son[o][1] = rson;
			Maintain(o);
		}
	}/*
	void print()
	{
		DEBUG("root = %d\n", root);
		DEBUG(" num[] "); REP(i, 1, sz) DEBUG(i == sz? "%3d\n" : "%3d ", i);
		DEBUG("here[] "); REP(i, 1, sz) DEBUG(i == sz? "%3d\n" : "%3d ", here[i]);
		DEBUG("sumv[] "); REP(i, 1, sz) DEBUG(i == sz? "%3d\n" : "%3d ", here[i]? sumv[i] : 0);
		DEBUG("lson[] "); REP(i, 1, sz) DEBUG(i == sz? "%3d\n" : "%3d ", here[i]? son[i][0] : 0);
		DEBUG("rson[] "); REP(i, 1, sz) DEBUG(i == sz? "%3d\n" : "%3d ", here[i]? son[i][1] : 0);
		DEBUG("   f[] "); REP(i, 1, sz) DEBUG(i == sz? "%3d\n" : "%3d ", here[i]? f[i] : 0);
		DEBUG("  fa[] "); REP(i, 1, sz) DEBUG(i == sz? "%3d\n" : "%3d ", here[i]? fa[i] : 0);
		DEBUG("\n");
	}*/
}t;
struct bcj{
	int f[MAXN], sumv[MAXN];
	inline void Init(int n){ REP(i, 1, n) f[i] = i, sumv[i] = 1; }
	int Find(int x){ return x == f[x]? x : (f[x] = Find(f[x])); }
	inline bool Union(int x, int y)
	{
		x = Find(x); y = Find(y);
		if(x == y) return false;
		W = sumv[x]; t.Delete(t.Query(t.root));// t.print();
		W = sumv[y]; t.Delete(t.Query(t.root));// t.print();
		sumv[y] += sumv[x];
		sumv[x] = sumv[y];
		t.Insert(sumv[y], t.root);
		f[x] = y;
		return true;
	}
}g;
int main()
{
	freopen("in.txt", "r", stdin);
	//freopen("debug.cpp", "w", stderr); 
	freopen("out.txt", "w", stdout);
	int n, m, flag, a, b;
	n = readin();
	m = readin();
	g.Init(n);
	t.Build(1, 0, n);
	REP(i, 1, m){
		flag = readin();
		if(!flag){
			a = readin();
			b = readin();
			g.Union(a, b);
		}else{
			a = readin();
			printf("%d\n", t.Query(a, t.root));
		}
	}
}
