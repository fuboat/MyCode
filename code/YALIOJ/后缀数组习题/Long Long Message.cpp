#include <algorithm>
#include <cstdio>
#include <map>
#include <iostream>
#include <cstring>
#include <cmath>
#include <set>
#include <vector>
#define DEBUG(...) fprintf(stderr, __VA_ARGS__)
using namespace std;
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
#define CLEAR(a) memset(a, 0, sizeof(a))
template <typename T> bool Chkmin(T &x, T y){ return y < x? (x = y, true) : false; }
template <typename T> bool Chkmax(T &x, T y){ return y > x? (x = y, true) : false; }
const int MAXK = 100 + 20, MAXN = 200000 + 3000, MAXM = MAXN;
const int MAXD = 26;
int c[MAXM];
inline void jsort(int *s, int *rank, int *sa, int m, int n)
{
	CLEAR(c);
	REP(i, 0, n - 1) c[s[rank[i]]] ++;
	REP(i, 1, m - 1) c[i] += c[i - 1];
	rep(i, n - 1, 0) sa[-- c[s[rank[i]]]] = rank[i];
}
int fs[MAXN];
struct rmq{
	int minv[MAXN][MAXD];
	void Init(int *a, int n)
	{
		REP(i, 0, n - 1) minv[i][0] = a[i];
		int d = log(1.0 * n)/log(2.0);
		REP(k, 1, d) REP(i, 0, n - 1)
			if(i + (1 << k) - 1 <= n)
				minv[i][k] = min(minv[i][k - 1], minv[i + (1 << (k - 1))][k - 1]);
	}
	
	int Query(int l, int r){
		int k = log(r - l + 1) / log(2.0);
		return min(minv[l][k], minv[r - (1 << k) + 1][k]);
	}
};
struct suffix_array{
	int tmp[MAXN], t2[MAXN], t1[MAXN], sa[MAXN], height[MAXN], n;
	int s[MAXN], rank[MAXN], ok[MAXN];
	rmq t;
	void Init()
	{
		CLEAR(ok); CLEAR(s); CLEAR(sa); CLEAR(rank); CLEAR(t1); CLEAR(t2); CLEAR(tmp); CLEAR(height);
	}
	void buildSA(int m)
	{
		int *x = t1, *y = t2;
		REP(i, 0, n - 1)
			tmp[i] = i, x[i] = s[i]; 
		jsort(x, tmp, sa, m, n);
		for(int k = 1; k <= n; k <<= 1){
			int p = 0, now, last;
			REP(i, n - k, n - 1) y[p ++] = i;
			REP(i, 0, n - 1) if(sa[i] >= k) y[p ++] = sa[i] - k;
			jsort(x, y, sa, m, n);
			swap(x, y);
			p = 1;
			x[sa[0]] = 0;
			REP(i, 1, n - 1){
				now = sa[i], last = sa[i - 1];
				x[now] = y[now] == y[last] && y[now + k] == y[last + k]? p - 1 : p ++;
			}
			if(p >= n) break;
			m = p;
		}
		//REP(i, 0, n - 1) printf("%d ",s[i]);
		//puts("");
		//DEBUG("n = %d\nsa[] = ", n);
		//REP(i, 0, n - 1) DEBUG(i == n - 1? "%d\n" : "%d ", sa[i]);
	}
	inline bool OK(int c){ return 1 <= c && c <= 26; } 
	void getHeight()
	{
		int k = 0;
		REP(i, 0, n - 1) rank[sa[i]] = i;
		REP(i, 0, n - 1){
			if(k) k --;
			if(rank[i] == 0){ k = 0; continue; }
			int j = sa[rank[i] - 1];
			while(s[i + k] == s[j + k] && OK(s[i + k]) && OK(s[j + k]))
				k ++;
			height[rank[i]] = k;
		}
	}
	void Solve()
	{
		
		t.Init(height, n);
		int cnt = 0, head = 0, maxx = 0;
		REP(i, 0, n - 1){
			if(fs[sa[i]] == 0) continue;
			if(!ok[fs[sa[i]]]) cnt ++;
			ok[fs[sa[i]]] ++;
			if(cnt == 2){
				while(fs[sa[head]] == 0 || ok[fs[sa[head]]] > 1){
					ok[fs[sa[head]]] --;
					head ++;
				}
				Chkmax(maxx, t.Query(head + 1, i));
			}
		}
		printf("%d\n", maxx);
	}
}t;
char s[MAXN];
int main()
{
	int v = -1;
	t.Init();
	REP(i, 1, 2){
		scanf("%s", s);
		int len = strlen(s);
		REP(j, 0, len){
			t.s[v + 1 + j] = j == len? 100 + i - 1 : s[j] - 'a' + 1;
			if(j != len) fs[v + 1 + j] = i;
			else fs[v + 1 + j] = 0;
		}
		v += len + 1;
	}
	t.s[v + 1] = 0;
	t.n = v + 2;
	t.buildSA(100 + 2 + 1);
	t.getHeight();
	t.Solve();
}
