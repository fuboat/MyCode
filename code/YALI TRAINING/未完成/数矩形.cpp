#include <cstdio>
#include <iostream>
#include <algorithm>
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define LL long long
using namespace std;
template<typename T>bool Chkmax(T &x, T y){ return y > x? x = y, true : false; }
const int MOD = 379373, MAXN = 1500 + 100;
const LL MAXA = 1e8;
struct Node{
	int x, y;
	Node(){}
	Node(int x, int y):x(x), y(y){}
	void Val(int &a, int &b){ a = x, b = y; }
	int Hash(){ return (1LL * (x + MAXA) * MAXA * 10 + y + MAXA) % MOD; }
};
bool operator == (const Node &a, const Node &b){
	return a.x == b.x && a.y == b.y;
}
struct edge{
	Node node;
	int next;
	edge(){}
	edge(Node node, int next):node(node), next(next){}
} HASH[MAXN];
int edge_cnt;
/*Hash--------------------------------------------------------------------*/
int pre[MOD];
bool Find(Node x)
{
	LL hash = x.Hash();
	for(int i = pre[hash]; i; i = HASH[i].next)
		if(HASH[i].node == x) return true;
	return false;
}
void Insert(Node x)
{
	int hash = x.Hash();
	for(int i = pre[hash]; i; i = HASH[i].next)
		if(HASH[i].node == x) return ;
	HASH[++ edge_cnt] = edge(x, pre[hash]);
	pre[hash] = edge_cnt;
}
/*--------------------------------------------------------------------*/
Node a[MAXN];
int main()
{
	int n, x, y, x1, x2, y1, y2;
	LL ans = 0;
	scanf("%d", &n);
	REP(i, 1, n){
		scanf("%d%d", &x, &y);
		Insert(a[i] = Node(x, y));
	}
	REP(i, 1, n) REP(j, i + 1, n){
		a[i].Val(x1, y1);
		a[j].Val(x2, y2);
		if(Find(Node(x1, y2)) && Find(Node(x2, y1)))
			Chkmax(ans, 1LL * (x2 - x1) * (y2 - y1));
	}
	printf("%I64d\n", ans);
}
