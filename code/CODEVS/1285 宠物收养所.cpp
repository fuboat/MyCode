/*
	FROM: CODEVS
	PROB: 1285
	ID: Fuboat
*/
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cstring>
#define lc o->ch[0]
#define rc o->ch[1]
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
#define CLEAR(a) memset(a, 0, sizeof(a))
using namespace std;
/*Public------------------------------------------------------------*/
const int MAXN = 80000 + 1000, oo = 0x3f3f3f3f, MOD = 1000000;
void Better(int x, int &best, int y)
{
	int a1 = abs(x - best), a2 = abs(x - y);
	if(a2 < a1 || (a2 == a1 && y < best)) best = y;
}
/*Treap-------------------------------------------------------------*/
/*[1]Node-----------------------------------------------------------*/
struct node{
	int v, r, sum;
	node* ch[2];
	node(){}
	node(int v);
	void Maintain();
	int cmp(int x){
		if(v == x) return -1;
		return (x > v);
	}
};
node *null, *root[2];
node::node(int v):v(v)
{
	sum = 1;
	ch[0] = ch[1] = null;
	r = rand();
}
void node::Maintain()
{
	if(this == null){ sum = 0; return ; }
	sum = 1;
	if(ch[0] != null) sum += ch[0]->sum;
	if(ch[1] != null) sum += ch[1]->sum;
}
/*[2]Operation of Treap---------------------------------------------*/
struct Treap{
	void Rotate(node* &o, int d)
	{
		node *k = o->ch[!d];
		o->ch[!d] = k->ch[d];
		k->ch[d] = o;
		o->Maintain();
		k->Maintain();
		o = k;
	}
	void Insert(node* &o, int x)
	{
		int d;
		if(o == null) o = new node(x);
		else{
			d = o->cmp(x);
			Insert(o->ch[d], x);
			if(o->ch[d]->r > o->r)
				Rotate(o, !d);
		}
	}
	void Delete(node* &o, int x)
	{
		int d = o->cmp(x);
		if(d == -1){
			if(lc == null && rc == null) o = null;
			else if(lc != null && rc != null){
				d = (lc->r < rc->r);
				Rotate(o, !d);
				Delete(o->ch[!d], x);
				// Warning!!!
				// 'o->ch[!d]', not 'o->ch[d]'!
			}else if(lc != null) o = lc;
			else o = rc;
		}else Delete(o->ch[d], x);
		o->Maintain();
	}
	void Find(node* &o, int x, int &best)
	{
		if(o == null) return ;
		// Don't forget this sentences, or the program won't stop;
		int d = o->cmp(x);
		if(d == -1) best = x;
		else{
			if(o->ch[!d] != null)
			Better(x, best, o->ch[!d]->v);
			Better(x, best, o->v);
			Find(o->ch[d], x, best);
		}
	}
}t;
/*operation---------------------------------------------------------*/
int Choose(node* &from, int x)
{
	int best = oo;
	t.Find(from, x, best);
	t.Delete(from, best);
	return abs(x - best);
}
/*Main Program------------------------------------------------------*/
void Init()
{
	null = new node;
	null->ch[0] = null->ch[1] = null;
	null->sum = null->r = null->v = 0;
	root[0] = root[1] = null;
}
void Solve()
{
	int n, x, flag, best, ans = 0;
	scanf("%d", &n);
	REP(i, 1, n){
		scanf("%d%d", &flag, &x);
		if(root[!flag] == null)
			t.Insert(root[flag], x);
		else (ans += Choose(root[!flag], x)) %= MOD;
	}
	printf("%d\n", ans);
}
int main()
{
	Init();
	Solve();
}
