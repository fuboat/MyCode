#include <cstdio>
#include <algorithm>
#include <iostream>
#define REP(i, x, y) for(int i = x, _ = y; i <= _;i ++)
#define lc son[o][0]
#define rc son[o][1]
const int MAXN = 100000 + 1000;
int sum;
struct Splay_tree{
	int son[MAXN][2];
	int sumv[MAXN], fa[MAXN], val[MAXN];
	int root, sz;
	void Maintain(int o)
	{
		if(o) sumv[o] = sumv[lc] + sumv[rc] + 1;
		else Clear(0);
	}
	void Rotate(int o)
	{
		int pa = fa[o], up = fa[pa], d = (son[pa][1] == o), c = son[o][!d];
		son[fa[o] = up][son[up][1] == pa] = o;
		son[fa[c] = pa][d] = c;
		son[fa[pa] = o][!d] = pa;
		Maintain(pa);
		Maintain(o);
	}
	void Insert(int x)
	{
		sz ++;
		int o, d;
		if(root == 0){
			root = sz;
			fa[sz] = 0;
		}else{
			o = root, d = (x >= val[o]);
			while(son[o][d]){
				o = son[o][d];
				d = (x >= val[o]);
			}
			son[o][d] = sz;
			fa[sz] = o; // Don't forget this sentences!
		}
		o = sz;
		val[o] = x;
		Maintain(o);
		Splay(o, 0);
	}
	void Splay(int o, int F)
	{
		if(!o) return ;
		while(fa[o] != F){
			int pa = fa[o], up = fa[pa];
			if(up == F){ Rotate(o); break; }
			else if((son[up][0] == pa) ^ (son[pa][0] == o))
				Rotate(pa), Rotate(o);
			else Rotate(o), Rotate(o);
		}
		if(!F) root = o;
		Maintain(o);
	}
	int Query(int k)
	{
		int o = root;
		if(!o || k > sumv[o]) return -1;
		while(k != sumv[rc] + 1){
			if(k <= sumv[rc]) o = rc;
			else k -= sumv[rc] + 1, o = lc;
		}
		return val[o];
	}
	void Clear(int o){
		int pa = fa[o];
		son[pa][son[pa][1] == o] = 0;
		sumv[o] = fa[o] = fa[lc] = fa[rc] = 0;
		lc = rc = 0;
	}
	void Update(int x)
	{
		int o, next = root;
		while(next){
			o = next;
			if(val[o] < x) next = rc;
			else next = lc;
		}
		Splay(o, 0);
		sum += sumv[lc];
		if(val[o] < x){
			root = rc;
			sum ++;
			Clear(o);
		}else{
			Clear(lc);
			Maintain(o);
		}
	}
}t;
int main()
{
	int n, minx, x, change = 0;
	char c[10];
	scanf("%d%d", &n, &minx);
	REP(i, 1, n){
		scanf("%s%d", c, &x);
		switch(c[0]){
			case 'I': if(x >= minx) t.Insert(x - change); break;
			case 'A': change += x; break;
			case 'S': change -= x; t.Update(minx - change); break;
			case 'F':
				int ans = t.Query(x);
				printf("%d\n", ans == -1? ans : ans + change);
				break;
		}
	}
	printf("%d\n", sum);
}
