/*
	EXPERIENCES:
	1. Building once is much better than inserting one by one;
*/
#include <cstdio>
#include <algorithm>
#include <cstring>
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define CLEAR(a) memset(a, 0, sizeof(a))
#define lc son[o][0]
#define rc son[o][1]
using namespace std;
const int MAXN = 400000;
int n;
struct Splay_tree{
	int son[MAXN][2], fa[MAXN], sumv[MAXN], ans[MAXN];
	bool flag[MAXN];
	int root;
	void Clear(){ CLEAR(sumv); CLEAR(fa); CLEAR(son); CLEAR(flag); }
	inline void Pushdown(int o)
	{
		if(flag[o]){
			flag[o] = 0; 
			flag[lc] ^= 1;
			flag[rc] ^= 1;
			swap(lc, rc);
		}
	}
	inline void Maintain(int o){ sumv[o] = sumv[lc] + sumv[rc] + 1; }
	inline void Rotate(int o)
	{
		int pa, up, d, c;
		pa = fa[o];
		Pushdown(pa);
		Pushdown(o);
		up = fa[pa];
		d = (o == son[pa][1]);
		c = son[o][d ^ 1];
		fa[o] = up;
		son[up][pa == son[up][1]] = o;
		fa[c] = pa;
		son[pa][d] = c;	
		son[o][d ^ 1] = pa;
		fa[pa] = o;
		Maintain(pa);
		Maintain(o);
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
		if(!F) root = o;
	}
	inline int Query(int k)
	{
		int o = root;
		Pushdown(o);
		while(k != sumv[lc] + 1){
			if(k <= sumv[lc]) o = lc;
			else k -= sumv[lc] + 1, o = rc;
			Pushdown(o);
		}
		return o;
	}
	int Getmin(int o)
	{
		Pushdown(o);
		while(son[o][0]){
			o = son[o][0];
			Pushdown(o);
		}
		return o;
	}
	void Remove(int head, int tail, int up)
	{
		head = Query(head - 1);
		tail = Query(tail + 1);
		Splay(head, 0);
		Splay(tail, head);
		int o = son[tail][0];
		son[tail][0] = 0;
		Maintain(head);
		Maintain(tail);
		up = Query(up);
		Splay(up, 0);
		int pa = Getmin(son[up][1]);
		Splay(pa, up);
		son[fa[o] = pa][0] = o;
		Maintain(pa);
		Maintain(up);
	}
	inline void Round(int head, int tail)
	{
		head = Query(head - 1);
		tail = Query(tail + 1);
		Splay(head, 0);
		Splay(tail, head);
		flag[son[tail][0]] ^= 1;
	}
	inline void Build(int n)
	{
		root = 1;
		REP(i, 2, n){
			int o = root, d = (i > o);
			while(son[o][d]) o = son[o][d], d = (i > o);
			fa[son[o][d] = i] = o;
			Splay(i, 0);
		}
		Maintain(root);
	}
	int cnt;
	void Print(int o)
	{
		Pushdown(o);
		if(!o) return ;
		Print(son[o][0]);
		ans[cnt ++] = o;
		Print(son[o][1]);
	}
	void Print()
	{
		cnt = 0;
		Print(root);
		REP(i, 1, n) printf(i == n? "%d\n" : "%d ", ans[i] - 1);
	}
    void Build(int l, int r, int pa, int d){
    	if(l > r) return ;
    	int mid = (l + r) >> 1;
    	fa[mid] = pa;
    	if(pa) son[pa][d] = mid;
    	else root = mid;
    	if(l != r)
    	{
			Build(l, mid - 1, mid, 0);
    		Build(mid + 1, r, mid, 1);
    	}
    	Maintain(mid);
    }
}t;
 
int main()
{
	int m, l, r, next;
	while(scanf("%d%d", &n, &m) == 2 && n != -1){
		t.Clear();// Don't forget it!
		t.Build(1, n + 2, 0, 0);
		// Inserting the node one by one is too slow!
		//So, building once is much faster.
		char c[20];
		while(m --){
			scanf("%s", c);
			if(c[0] == 'C'){
				scanf("%d%d%d", &l, &r, &next);
				t.Remove(l + 1, r + 1, next + 1);
			}else{
				scanf("%d%d", &l, &r);
				t.Round(l + 1, r + 1);
			}
		}
		t.Print();
	}
}
