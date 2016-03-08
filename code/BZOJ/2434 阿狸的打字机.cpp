// BZOJ #2434
// Fuboat
// AC - Trie
/*
	In this problem, you make some little mistakes:
	1. some structures haven't been inited when using them;
	2. '0' is one of the number of nodes in the fail tree, so we should improve the adjacency list ;
*/
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>
#include <vector>
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
#define MSET(a, x) memset(a, x, sizeof(a))
#define CLEAR(a) MSET(a, 0) 
using std::vector;
using std::queue;
const int MAXS = 26, MAXN = 1e5 + 1e3;
int P[MAXN], HeadP[MAXN], EndP[MAXN], ans[MAXN];
char s[MAXN];
vector<int> ask[MAXN], num[MAXN]; 

struct Fenwick{
	int sumv[MAXN];
	int n;
	void Init(int N)
	{
		n = N;
	}
	void Add(int p, int x)
	{
		while (p <= n) {
			sumv[p] += x;
			p += p & -p;
		}
	}
	int Query(int p)
	{
		int sum = 0;
		while (p > 0) {
			sum += sumv[p];
			p -= p & -p;
		}
		return sum;
	}
}t;

struct Tree{
	int DfsClock;
	int dfn[MAXN];
	int next[MAXN], head[MAXN]; 
	Tree()
	{
		MSET(head, -1);
		// '0' may be a node!
		// So '0' can't mean null;
		
	}
	void AddEdge(int u, int v)
	{
		next[v] = head[u];
		head[u] = v;
	}
	void Dfs(int u)
	{
		dfn[++ DfsClock] = u;
		HeadP[u] = DfsClock;
		for (int i = head[u]; i != -1; i = next[i])
			Dfs(i);
		EndP[u] = DfsClock;
	}
}tree;

struct Trie{
	int f[MAXN], ch[MAXN][MAXS], val[MAXN], way[MAXN];
	int sz, pos;
	int Idx(int x) { return x - 'a'; }
	void MakeTrie(char *s)
	{
		pos = 0;
		int len = strlen(s), u = 0, cnt = 0;
		char c;
		REP (i, 0, len - 1) {
			c = s[i];
			if (c == 'B')
				u = way[-- pos];
			else if (c != 'P') {
				c = Idx(c);
				if (!ch[u][c])
					ch[u][c] = ++ sz;
				u = ch[u][c];
				way[++ pos] = u;
			} else {
				cnt ++;
				P[cnt] = u;
			}
		}
	}
	void Work(char *s)
	{
		pos = 0;
		int len = strlen(s), u = 0, cnt = 0, query;
		char c;
		t.Init(len);
		// Don't forget to 'Init()' ...
		REP (i, 0, len - 1) {
			c = s[i];
			if (c == 'B') {
				t.Add(HeadP[u], -1);
				u = way[-- pos];
			} else if (c != 'P') {
				c = Idx(c);
				u = ch[u][c];
				way[++ pos] = u;
				t.Add(HeadP[u], 1);
			} else {
				cnt ++;
				REP (j, 0, (int) ask[cnt].size() - 1) {
					query =  P[ask[cnt][j]];
					ans[num[cnt][j]] = t.Query(EndP[query]) - t.Query(HeadP[query] - 1);
				}
			}
		}
	}
	void GetFail()
	{
		queue<int> q;
		
		int u, r, v, j;
		REP (i, 0, MAXS - 1)
			if(u = ch[0][i]) {
				q.push(u);
				tree.AddEdge(0, u);
			}
		
		while (!q.empty()) {
			r = q.front();
			q.pop();
			REP (c, 0, MAXS - 1) {
				u = ch[r][c];
				if (!u) {
					ch[r][c] = ch[f[r]][c];
					continue;
				}
				
				j = f[r];
				while (j && !ch[j][c])
					j = f[j];

				q.push(u);
				v = ch[j][c];
				f[u] = v;
				tree.AddEdge(v, u);
			}
		}
	}
}ac;
int m;
void Init()
{
	int x, y;
	scanf("%s%d", s, &m);
	REP (i, 1, m) {
		scanf("%d%d", &x, &y);
		ask[y].push_back(x);
		num[y].push_back(i);
	}
}
void Solve()
{
	ac.MakeTrie(s);
	ac.GetFail();
	// No 'GetFail()', no fail-tree.
	// How do you forget this?
	// You  have make this mistake many times!
	tree.Dfs(0);
	ac.Work(s);
	REP (i, 1, m)
		printf("%d\n", ans[i]);
}
int main()
{
	Init();
	Solve();
}
