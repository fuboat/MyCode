// POJ #3666
// Fuboat
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <queue>
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
const int MAXN = 2000 + 1000;
int a[MAXN], b[MAXN];
int n;
struct Node{
	Node *lc, *rc;
	int val, dis, sz;
	Node(){}
	Node(int x)
	{
		val = x;
		rc = lc = NULL;
		dis = 0;
		sz = 1;
	}
	int Top()
	{ return val; }
};

Node *from[MAXN];
Node* Merge(Node *x, Node *y)
{
	if (x == NULL)
		return y;
	if (y == NULL)
		return x;
	if (x->val < y->val)
		std::swap(x, y);
	
	x->sz = 0;
	x->rc = Merge(x->rc, y);
	if(x->lc == NULL)
		std::swap(x->lc, x->rc);
	if(x->rc == NULL) {
		x->dis = 0;
		if(x->lc != NULL)
			x->sz = x->lc->sz;
	} else {
		if(x->lc->dis < x->rc->dis)
			std::swap(x->lc, x->rc);
		x->dis = x->rc->dis + 1;
		x->sz = x->lc->sz + x->rc->sz;
	}
	
	x->sz ++;
	return x;
}
void Pop(Node* &x)
{
	Node* tmp = x;
	x = Merge(x->lc, x->rc);
	delete tmp;
}

struct Sta{
	int l, r, next, last;
	Node *o;
	Sta() {}
	Sta(int pos, int last, int next):l(pos), r(pos), next(next), last(last)
	{
		o = new Node(a[pos]);
	}
	void Union();
}s[MAXN];

void Sta::Union()
{
	r = s[next].r;
	s[s[next].next].last = s[next].last;
	o = Merge(o, s[next].o);
	while(o->sz - 1 > (r - l + 1) / 2)
	// Don't forget the '-1' in the following!
		Pop(o);
	next = s[next].next;
}

void Init()
{
	REP(i, 1, n)
		scanf("%d", &a[i]);
}

int Solve()
{
	REP (i, 1, n)
		s[i] = Sta(i, i - 1, i < n? i + 1 : 0);
	int l, r, now = 2, ans = 0;
	
	while (now) {
		while (s[now].last && s[now].o->val < s[s[now].last].o->val)
			s[now = s[now].last].Union();
		if (s[now].next == 0)
			break;
		now = s[now].next;
	}
	
	while (now) {
		l = s[now].l;
		r = s[now].r;
		REP(i, l, r)
			b[i] = s[now].o->val;
		now = s[now].last;
	}
	
	REP (i, 1, n)
		ans += abs(b[i] - a[i]);
	return ans;
}

int main()
{
	int ans;
	scanf("%d", &n);
	Init();
	ans = Solve();
	REP(i, 1, n)
		std::swap(a[i], a[n - i + 1]);
	printf("%d\n", std::min(ans, Solve()));
}
