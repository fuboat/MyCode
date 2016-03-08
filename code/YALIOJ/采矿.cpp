#include <cstdio>
#include <algorithm>
#include <iostream>
#include <vector>
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
#define CLEAR(a) memset(a, 0, sizeof(a))
#define lc o->ch[0]
#define rc o->ch[1]
const int MAXN = 15000 + 1000;
using namespace std;
struct node{
	node *ch[2];
	int val, r, sumv;
	void Maintain();
};
node *null = new node();
void node::Maintain()
{
	sumv = 1;
	if(ch[0] != null) sumv += ch[0]->sumv;
	if(ch[1] != null) sumv += ch[1]->sumv;
}
struct Treap{
	node* root;
	void Init(){ root = null; }
	void Rotate(node* &o, bool d)
	{
		node* k = o->ch[!d];
		o->ch[!d] = k->ch[d];
		k->ch[d] = o;
		o = k;
	}
	void Insert(node* &o, node* &tmp, int x)
	{
		if(o == null){
			o = new node();
			o->val = x;
			o->r = rand();
			o->ch[0] = o->ch[1] = null;
			tmp = o;
		}else{
			bool d = (o->val >= x);
			Insert(o->ch[d], tmp, x);
			if(o != null && o->ch[d]->r > o->r) Rotate(o, !d);
		}
		o->Maintain();
	}
	void Delete(node* &o)
	{
		if(lc == null) o = lc;
		else if(rc == null) o = rc;
		else{
			bool d = (lc->r >= rc->r);
			Rotate(o, d);
			Delete(o->ch[d]);
		}
		if(o != null) o->Maintain();
	}
}t;
int main()
{
	t.Init();
}
