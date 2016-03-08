// CodeVS #2403
// Fuboat
// AC - Trie
// For this kind of problem, never forget use 'GetFail()', or it is hard for you to find the bug by eye;
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <map>
#include <queue>
#include <vector>
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
#define MSET(a, x) memset(a, x, sizeof(a))
#define CLEAR(a) MSET(a, 0)
template <typename T> bool Chkmax(T &x, T y) { return y > x? x = y, true : false; }
template <typename T> bool Chkmin(T &x, T y) { return y < x? x = y, true : false; }
const int MAXL = 100000 + 1000, MAXM = 50000 + 1000, MAXN = 20000 + 1000;
void Readin(int &x)
{
	x = 0;
	int c = getchar();
	while (c < '0' || '9' < c)
		c = getchar();
	while ('0' <= c && c <= '9') {
		(x *= 10) += c - '0';
		c = getchar();
	}
}
int cur[MAXM], ans[MAXM];
int totshout[MAXN];
namespace Trie
{
	using std::map;
	using std::vector;
	using std::queue;
	
	int sz;
	int f[MAXL], last[MAXL];
	
	map<int, int> ch[MAXL];
	vector<int> val[MAXL];
	
	void Insert(int *s, int len, int x)
	{
		int u = 0, c;
		
		REP (i, 0, len - 1) {
			c = s[i];
			if (!ch[u].count(c))
				ch[u][c] = ++ sz;
			u = ch[u][c];
		}
		
		val[u].push_back(x);
	}
	void GetFail()
	{
		queue<int> q;
		int u, v, r, c;
		
		for (map<int, int>::iterator it = ch[0].begin(); it != ch[0].end(); it ++)
			q.push(it->second);
			
		while (!q.empty()) {
			r = q.front();
			q.pop();
			
			for (map<int, int>::iterator it = ch[r].begin(); it != ch[r].end(); it ++) {
				c = it->first;
				u = it->second;
				q.push(u);

				v = f[r];
				while (v && !ch[v].count(c))
					 v = f[v];
				f[u] = ch[v][c];
				
				last[u] = val[f[u]].empty()? last[f[u]] : f[u];
			}
		}
	}
	void Update(int u, int x)
	{
		if (cur[u] >= x)
			return ;
		if (val[u].empty())
			u = last[u];
		
		while (u && cur[u] != x) {
			cur[u] = x;
			totshout[x] += val[u].size();
			for (int i = 0; i < val[u].size(); i ++)
				ans[val[u][i]] ++;

			u = last[u];
		}
	}
	void Find(int *s, int len, int x)
	{
		int u = 0, c;
		REP (i, 0, len - 1) {
			c = s[i];
			
			while (!ch[u].count(c)) {
				u = f[u];
				if (!u)
					continue;
			}

			u = ch[u][c];
			Update(u, x);
		}
	}
}

int n, m;
int S[MAXL], T[MAXL], L[MAXN][2], P[MAXN][2];
void Init()
{
	int len, now = 0;
	
	Readin(n);
	Readin(m);
	
	REP (i, 1, n)
		REP (j, 0, 1) {
			P[i][j] = now;
			Readin(L[i][j]);
			REP (k, 0, L[i][j] - 1)
				Readin(S[now ++]);
		}
	
	REP (i, 1, m) {
		Readin(len);
		REP (j, 0, len - 1)
			Readin(T[j]);
		Trie::Insert(T, len, i);
	}
}
void Solve()
{
	Trie::GetFail();
	// Never forget 'GetFail()'!
	REP (i, 1, n)
		REP (j, 0, 1)
			Trie::Find(S + P[i][j], L[i][j], i);
}
void Print()
{
	REP (i, 1, m)
		printf("%d\n", ans[i]);
	REP (i, 1, n)
		printf(i == n? "%d\n" : "%d ", totshout[i]);
}
int main()
{
	Init();
	Solve();
	Print();
}
