#include <cstdio>
#include <algorithm>
using namespace std;
const int MAXN = 1000000;
struct Splay_tree{
	int sumv[MAXN], son[MAXN][2], fa[MAXN], f[MAXN], fnode[MAXN], sz;
	int root;
	inline void Maintain(int o){
		int lc = son[o][0], rc = son[o][1];
		sumv[o] = sumv[lc] + sumv[rc];
		if(o) sumv[o] ++;
		else sumv[o] = 0;
	}
	inline void Rotate(int o)
	{
		int pa = fa[o], up = fa[pa], d = (o == son[pa][1]), c = son[o][d ^ 1];
		fa[o] = up;
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
		if(!o) return ;
		while(fa[o] != F){
			int pa = fa[o], up = fa[pa];
			if(up == F){ Rotate(o); break; }
			if((son[up][0] == pa) ^ (son[pa][0] == o))
				Rotate(pa), Rotate(o);
			else Rotate(o), Rotate(o);
		}
		if(F == 0) root = o;
	}
	inline void New(int w, int o, int d, int num)
	{
		son[o][d] = ++ sz;
		sumv[sz] = 1;
		f[sz] = w;
		fa[sz] = o;
		fnode[sz] = num;
		Splay(sz, 0);
	}
	inline void Insert(int w, int num)
	{
		if(!root){
			root = ++ sz;
			fa[root] = 0;
			f[root] = w;
			sumv[root] = 1;
			fnode[sz] = num;
			return ;
		}
		int o = root;
		bool d = (w > f[o]);
		while(son[o][d]){
			o = son[o][d];
			d = (w > f[o]);
		}
		New(w, o, d, num);
	}
	inline int Query(bool flag)
	{
		if(!root) return 0;
		int o = root;
		while(son[o][flag]) o = son[o][flag];
		Splay(o, 0);
		int c = son[o][flag ^ 1];
		root = c;
		fa[c] = 0;
		return fnode[o];
	}
}t;
int to[] = {0, 0, 1, 0, 0};
int main()
{
	int flag, w, num;
	while(scanf("%d", &flag) && flag){
		if(flag == 1){
			scanf("%d%d", &num, &w);
			t.Insert(w, num);
		}else printf("%d\n", t.Query(to[flag]));
	}
}
