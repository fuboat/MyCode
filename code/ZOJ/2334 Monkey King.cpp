#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
const int MAXN = 1e5 + 1e3;
int f[MAXN];
struct Node{
	Node *lc, *rc;
	int val, dis;
	Node(){}
	Node(int x)
	{
		val = x;
		rc = lc = NULL;
		dis = 0;
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
	
	x->rc = Merge(x->rc, y);
	if(x->lc == NULL)
		std::swap(x->lc, x->rc);
	if(x->rc == NULL)
		x->dis = 0;
	else {
		if(x->lc->dis < x->rc->dis)
			std::swap(x->lc, x->rc);
		x->dis = x->rc->dis + 1;
	}
	return x;
}
void Pop(Node* &x)
{
	Node* tmp = x;
	x = Merge(x->lc, x->rc);
	delete tmp;
}
int Find(int x) { return x == f[x]? x : f[x] = Find(f[x]); }
int Union(int x, int y)
{
	x = Find(x);
	y = Find(y);
	if(x == y)
		return -1;
	
	int s1, s2;
	Node *new1, *new2;
	s1 = from[x]->val; Pop(from[x]);
	s2 = from[y]->val; Pop(from[y]);
	
	new1 = new Node(s1 / 2);
	new2 = new Node(s2 / 2);
	
	from[x] = Merge(from[x], from[y]);
	from[x] = Merge(from[x], new1);
	from[x] = Merge(from[x], new2);
	f[y] = x;
	
	return from[x]->val;
}

int main()
{
	int n, m, x, y;
	while (~scanf("%d", &n) && n) {
		REP(i, 1, n)
			f[i] = i;
		REP(i, 1, n) {
			scanf("%d", &x);
			from[i] = new Node(x);
		}
		scanf("%d", &m);
		REP(i, 1, m) {
			scanf("%d%d", &x, &y);
			printf("%d\n", Union(x, y));
		}
	}
}
