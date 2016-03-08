#include <cstdio>
#include <iostream>
#include <algorithm>
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define LL long long
#define lc ch[o][0]
#define rc ch[o][1]
using namespace std;
const int MAXN = 100000 + 1000;
int a[MAXN];
struct Splay_tree{
	int ch[MAXN][2];
	int sumv[MAXN], fa[MAXN], val[MAXN], addv[MAXN];
	LL sum[MAXN];
	int root, sz;
	inline void Pushdown(int o)
	{
		if(addv[o] != 0){
			int &add = addv[o];
			val[o] += add;
			if(lc != 0){
				addv[lc] += add;
				sum[lc] += 1LL * sumv[lc] * add;
			}
			if(rc != 0){
				addv[rc] += add;
				sum[rc] += 1LL * sumv[rc] * add;
			}
			add = 0;
		}
	}
	inline void Build(int pa, int son, int d)
	{
		if(pa) ch[pa][d] = son;
		fa[son] = pa;
	}
	inline void Maintain(int o)
	{
		if(o){
			sumv[o] = sumv[lc] + sumv[rc] + 1;
			sum[o] = sum[lc] + sum[rc] + val[o] + 1LL * addv[o] * sumv[o];
		}
	}
	void Build(int l, int r, int pa, bool d)
	{
		if(l > r) return ;
		int mid = (l + r) >> 1;
		if(pa == 0) root = mid; // Remember, this is not 'if(!fa)' !
		else{
			fa[mid] = pa;
			ch[pa][d] = mid;
		}
		val[mid] = a[mid - 1];
		if(l != r){
			Build(l, mid - 1, mid, 0);
			Build(mid + 1, r, mid, 1);
		}
		Maintain(mid);
	}
	void Rotate(int o)
	{
		int pa = fa[o], up = fa[pa];
		Pushdown(pa); Pushdown(o);
		bool d = (o == ch[pa][1]);
		Build(up, o, ch[up][1] == pa);
		Build(pa, ch[o][!d], d);
		Build(o, pa, !d);
		Maintain(pa); Maintain(o);
	}
	void Update(int l, int r, int x)
	{
		int head = l - 1, tail = r + 1, o;
		Splay(head, 0);
		Splay(tail, head);
		o = ch[tail][0];
		addv[o] += x;
		LL add = 1LL * x * sumv[o];
		sum[o] += add;
		sum[tail] += add;
		sum[head] += add;
	}
	void Splay(int o, int F)
	{
		if(o == 0) return ;
		while(fa[o] != F){
			int pa = fa[o], up = fa[pa];
			if(up == F){ Rotate(o); break; }
			if((ch[up][0] == pa) ^ (ch[pa][0] == o))
				Rotate(pa);
			else Rotate(o);
			Rotate(o);
		}
		if(F == 0) root = o;
		Maintain(o);
	}
	LL Query(int l, int r)
	{
		int head = l - 1, tail = r + 1;
		Splay(head, 0);
		Splay(tail, head);
		Pushdown(head);
		Pushdown(tail);
		return sum[ch[tail][0]];
	}
}t;
void Readin(int &x)
{
	x = 0;
	int ok = 1;
	bool flag = 0;
	char c = 0;
	while((c = getchar())){
		if(!flag && c == '-') ok = -1;
		else if('0' <= c && c <= '9'){
			(x *= 10) += c - '0';
			flag = true;
		}else if(flag){ x *= ok; return; }
	}
}
int main()
{
	int m, n, l, r, x;
	Readin(n); Readin(m);
	REP(i, 1, n) Readin(a[i]);
	t.Build(1, n + 2, 0, 0);
	char c;
	REP(i, 1, m){
		c = getchar();
		while(c != 'C' && c != 'Q') c = getchar();
		Readin(l); Readin(r);
		if(c == 'Q') printf("%lld\n", t.Query(l + 1, r + 1));
		else{
			Readin(x);
			t.Update(l + 1, r + 1, x);
		}
	}
}
