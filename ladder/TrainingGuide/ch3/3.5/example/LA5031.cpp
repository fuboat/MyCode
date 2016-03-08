// LA5031
// Fuboat
// Treap
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#define CLEAR(a) memset(a, 0, szieof(a))
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
#define LL long long
#define lc o->ch[0]
#define rc o->ch[1]
/*Public--------------------------------------------------------------------*/
const int MAXN = 200000 + 40000, MAXM = 600000 + 1000;
int val[MAXN];
/*Treap--------------------------------------------------------------------*/
struct node{
	int v, r, sum;
	node *ch[2];
	node(int v): v(v){
		ch[0] = ch[1] = NULL;
		sum = 1;
		r = rand();
	}
	void Maintain()
	{
		sum = 1;
		if(ch[0] != NULL) sum += ch[0]->sum;
		if(ch[1] != NULL) sum += ch[1]->sum;
	}
}*root[MAXN];
struct Treap{
	void Remove(node* &o)
	{
		if(o == NULL) return ;
		Remove(o->ch[0]);
		Remove(o->ch[1]);
		delete o;
		o = NULL;
	}
	void Init(int n)
	{	
		REP(i, 1, n){
			Remove(root[i]);
			root[i] = new node(val[i]);
		}
	}
	void Rotate(node* &o, int d)
	{
		node* k = o->ch[!d];
		o->ch[!d] = k->ch[d];
		k->ch[d] = o;
		o->Maintain();
		k->Maintain();
		o = k;
	}
	int Query(node* o, int k)
	{
		int rsum;
		if(k > o->sum || k <= 0) return 0;
		rsum = rc == NULL? 0 : rc->sum;
		while(k != rsum + 1){
			if(k <= rsum) o = rc;
			else k -= rsum + 1, o = lc;
			rsum = rc == NULL? 0 : rc->sum;
		}
		return o->v;
	}
	void Delete(node* &o, int x)
	{
		if(o->v == x){
			if(lc != NULL && rc != NULL){
				bool d = (rc->r > lc->r);
				Rotate(o, !d);
				Delete(o->ch[!d], x);
				// These two above are both '!d'!
				if(o != NULL) o->Maintain();
				// We can't read or write the pointer 'NULL';
				// So, use can't maintain the node 'o' if 'o == NULL' to avoid 'Runtime Erorr';
			}else{
				node* old = o;
				if(rc != NULL) o = rc;
				else o = lc;
				delete old;
			}
		}else{
			Delete(o->ch[x > o->v], x);
			if(o != NULL) o->Maintain();
		}
	}
	void Insert(node* &o, int x)
	{
		if(!o) o = new node(x);
		else{
			bool d = (x >= o->v);
			Insert(o->ch[d], x);
			if(o->ch[d]->r > o->r)
				Rotate(o, !d);
		}
		o->Maintain();
	}
	void Union(node* &o, node* &pos)
	{
		if(o == NULL) return ;
		Union(lc, pos);
		Union(rc, pos);
		Insert(pos, o->v);
		delete o;
		o = NULL;
	}
	int Mergeto(int x, int y)
	{
		if(root[x]->sum > root[y]->sum) std::swap(x, y);
		// Heuristic merger(启发式合并)
		Union(root[x], root[y]);
		return y;
	}
}t;
/*Union Set-----------------------------------------------------------------*/
struct Union_set{
	int f[MAXN];
	void Init(int n){ REP(i, 1, n) f[i] = i; }
	int Find(int x){ return x == f[x]? x : f[x] = Find(f[x]); }
	void Union(int x, int y)
	{
		x = Find(x), y = Find(y);
		if(x == y) return ;
		f[x] = f[y] = t.Mergeto(x, y);
	}
}g;
/*Query-------------------------------------------------------------------*/
struct edge{ int from, to; }s[MAXM];
struct Que{
	int type, x, y;
	Que(){}
	Que(int type, int x, int y):
		type(type), x(x), y(y){}
}que[500000];
bool ok[MAXM];
/*Program-------------------------------------------------------------------*/
inline void Gets(char &c)
{
	do c = getchar();
	while(c != 'D' && c != 'Q' && c != 'C' && c != 'E');
}
int num, n, m;
void Init()
{
	memset(ok, 0, sizeof(ok));
	int x, y, tmp;
	char c;
	num = 0;
	g.Init(n);
	REP(i, 1, n) scanf("%d", &val[i]);
	REP(i, 1, m){
		scanf("%d%d", &x, &y);
		s[i] = (edge){x, y};
	}
	Gets(c);
	while(c != 'E'){
		num ++;
		scanf("%d", &x);
		switch(c){
			case 'D': ok[x] = 1; tmp = 1; break;
			case 'Q': scanf("%d", &y); tmp = 2; break;
			case 'C': scanf("%d", &y); std::swap(val[x], y); tmp = 3; break;
		}
		que[num] = Que(tmp, x, y);
		Gets(c);
	}
	t.Init(n);
	REP(i, 1, m) if(!ok[i]) g.Union(s[i].from, s[i].to);
}
void Solve()
{
	LL ans = 0;
	int cnt = 0, type, pa, x, y;
	rep(i, num, 1){
		type = que[i].type;
		x = que[i].x;
		y = que[i].y;
		switch(type){
			case 1:
				g.Union(s[x].from, s[x].to);
				break;
			case 2:
				cnt ++;
				ans += t.Query(root[g.Find(x)], y);
				break;
			case 3:
				pa = g.Find(x);
				t.Delete(root[pa], val[x]);
				t.Insert(root[pa], val[x] = y);
		}
	}
	printf("%.6lf\n", 1.0 * ans / cnt);
}
int main()
{
	int T = 0;
	while(scanf("%d%d", &n, &m) == 2 && n && m){
		printf("Case %d: ", ++ T);
		Init();
		Solve();
	}
}
