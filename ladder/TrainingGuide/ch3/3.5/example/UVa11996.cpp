// UVa11996
// Fuboat
// Splay
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define CLEAR(a) memset(a, 0, sizeof(a))
#define lc ch[o][0]
#define rc ch[o][1]
#define LL unsigned long long
int n, all;
using namespace std;
const int MAXN = 400000 + 1000, T = 127;
LL X[MAXN];
char s[MAXN];
struct Splay_tree{
	int ch[MAXN][2], fa[MAXN], sumv[MAXN];
	bool flag[MAXN];
	LL hash[MAXN][2], val[MAXN];
	int root, sz, end;
	void Clear(){ CLEAR(hash); CLEAR(sumv); CLEAR(fa); CLEAR(ch); CLEAR(flag); root = 0; }
	inline int idx(int x){ return x + 1; }
	inline void Build(int pa, int son, int d)
	{
		if(pa != 0) ch[pa][d] = son;
		if(son != 0) fa[son] = pa;
	}
	inline void Pushdown(int o)
	{
		if(flag[o]){
			Update(lc);
			Update(rc);
			swap(lc, rc);
			flag[o] = 0;
		}
	}
	inline void Maintain(int o)
	{ 
		if(!o) return ;
		sumv[o] = sumv[lc] + sumv[rc] + 1;
		bool d = flag[o];
		int son[] = {ch[o][d], ch[o][!d]};
		hash[o][0] = hash[son[0]][0] + idx(val[o]) * X[sumv[son[0]]] + hash[son[1]][0] * X[sumv[son[0]] + 1];
		hash[o][1] = hash[son[1]][1] + idx(val[o]) * X[sumv[son[1]]] + hash[son[0]][1] * X[sumv[son[1]] + 1];
	}
	inline void Update(int o)
	{
		flag[o] ^= 1;
		swap(hash[o][0], hash[o][1]);
	}
	inline void Rotate(int o)
	{
		int pa, up, d;
		pa = fa[o];
		up = fa[pa];
		Pushdown(pa);
		Pushdown(o);
		d = (o == ch[pa][1]);
		Build(up, o, ch[up][1] == pa);
		Build(pa, ch[o][!d], d);
		Build(o, pa, !d);
		Maintain(pa);
		Maintain(o);
	}
	inline void Splay(int o, int F)
	{
		if(o == 0 || o == F) return ;
		while(fa[o] != F){
			int pa = fa[o], up = fa[pa];
			if(up == F){ Rotate(o); break; }
			if((ch[up][0] == pa) ^ (ch[pa][0] == o)) Rotate(pa);
			else Rotate(o);
			Rotate(o);
		}
		if(!F) root = o;
		Maintain(o); 
	}
	inline int Get(int o, int k)
	{
		Pushdown(o);
		while(k != sumv[lc] + 1){
			if(k <= sumv[lc]) o = lc;
			else k -= sumv[lc] + 1, o = rc;
			Pushdown(o);
		}
		return o;
	}
	void Delete(int o)
	{
		int head, tail;
		head = Get(root, o - 1);
		tail = Get(root, o + 1);
		Splay(head, 0);
		Splay(tail, head);
		ch[tail][0] = 0;
		Maintain(tail);
		Maintain(head);
	}
	void Insert(int pos, int w)
	{
		int head, tail, o;
		head = Get(root, pos);
		tail = Get(root, pos + 1);
		Splay(head, 0);
		Splay(tail, head);
		o = ++ sz;
		val[o] = w;
		Build(tail, o, 0);
		Maintain(o);
		Maintain(tail);
		Maintain(head);
	}
	void Turn(int l, int r)
	{
		int head, tail, o;
		head = Get(root, l - 1);
		tail = Get(root, r + 1);
		Splay(head, 0);
		Splay(tail, head);
		o = ch[tail][0];
		Update(o);
		Maintain(head);
		Maintain(tail); 
	}
	LL GetHash(int o, int k)
	{
		Splay(o, end);
		Pushdown(o);
		LL Hash = hash[rc][0] * X[1] + val[o];
		int son = Get(rc, k - 1);
		// 'son' is the node meaning the end of the string;
		Splay(son, o);
		Pushdown(son);
		o = ch[son][1];
		Hash -= hash[o][0] * X[k]; 
		return Hash;
		// Kill the part which is not belong to the string we need to cheng it into Hash Value;
	}
	bool Check(int x, int y, int k){ return GetHash(x, k) == GetHash(y, k); }
	int Query(int x, int y)
	{
		int l = 2, r = all - y, ans = 1, mid;
		// 'all' means how many node without deleting are in the tree;
		// the longest suffix is in at most 'all - y' length;
		x = Get(root, x);
		y = Get(root, y);
		if(val[x] != val[y]) return 0;
		Splay(end, 0);
		// Avoid the false node influence our check(especially the Hash Value);
		while(l <= r){
			mid = (l + r) >> 1;
			if(GetHash(x, mid) == GetHash(y, mid))
				l = mid + 1, ans = mid;
			else r = mid - 1;
		}
		return ans;
	}
    void Build(int l, int r, int pa, int d)
	{
		if(l > r) return ;
    	int mid = (l + r) >> 1;
    	fa[mid] = pa;
    	if(s[mid - 1] != 0) val[mid] = s[mid - 1] - '0';
    	if(pa != 0){
			ch[pa][d] = mid;
			end = sz = r;
		}
    	else root = mid;
		if(l != r){
			Build(l, mid - 1, mid, 0);
    		Build(mid + 1, r, mid, 1);
    	}
    	Maintain(mid);
    }
}t;
int main()
{
	X[0] = 1;
	REP(i, 1, 400000)
		X[i] = X[i - 1] * T;
	// Init;
	int m, flag, x, y;
	while(scanf("%d%d", &n, &m) == 2 && n && m){
		all = n + 2;
		scanf("%s", s + 1);
		// 's + 1' is better for building Splay Tree than 's';
		t.Clear();
		t.Build(1, n + 2, 0, 0);
		REP(i, 1, m){
			scanf("%d%d", &flag, &x);
			if(flag == 2){ t.Delete(x + 1); all --; continue; }
			scanf("%d", &y);
			switch(flag){
				case 1: t.Insert(x + 1, y); all ++; break;
				case 3: t.Turn(x + 1, y + 1); break;
				case 4: printf("%d\n", t.Query(x + 1, y + 1)); break;
			}
			// all '+1' above are due to the false node;
		}
	}
}
