/*
	MISTAKES:
	1. Forget add a '\0' after the string;
	2.(line 138, 140) 'i + 1 <= len' , not 'i + 1 < len'(Because there is a '\0' more on the head);
	3.(line 113) 'head = i', not 'head = i + 1'(Because i is OK when 'height[i + 1] > x', and head means the first i which is OK);
	3.(line 38) There are a mistake in RMQ. Pay attention when you use RMQ next time;
	EXPERIENCE:
	1. When all char are the same in a part of the string, the program may be wrong easily. It is a good way to check out the BUG;
*/ 
#include <algorithm>
#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
#define LL long long
#define DEBUG(...) fprintf(stderr, __VA_ARGS__)
#define CLEAR(a) memset(a, 0, sizeof(a))
template <typename T> bool Chkmin(T &x, T y){ return y < x? (x = y, true) : false; }
template <typename T> bool Chkmax(T &x, T y){ return y > x? (x = y, true) : false; }
const int MAXN = 1000 + 1000, MAXM = MAXN, MAXD = 23;
int c[MAXN];
inline void jsort(int *s, int *rank, int *sa, int m, int n)
{
	CLEAR(c);
	REP(i, 0, n - 1) c[s[rank[i]]] ++;
	REP(i, 1, m - 1) c[i] += c[i - 1];
	rep(i, n - 1, 0) sa[-- c[s[rank[i]]]] = rank[i];
}
struct rmq{
	int minv[MAXN][MAXD];
	void Init(int *a, int n)
	{
		REP(i, 0, n - 1) minv[i][0] = a[i];
		int d = log(1.0 * n) / log(2.0);
		REP(k, 1, d) REP(i, 0, n - 1)
			if(i + (1 << k) - 1 < n)
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
		t.Init(height, n);
	}
	LL Solve(int l, int r, int x)
	{
		if(l >= r) return 0;
		while(height[l + 1] < x && l <= r) l ++;
		while(height[r] < x && r >= l) r --;
		if(l >= r) return 0;
		int minx = sa[l], maxx = sa[l], w = t.Query(l + 1, r);
		if(w < x) return 0;
		REP(i, l + 1, r){
			Chkmin(minx, sa[i]);
			Chkmax(maxx, sa[i]);
		}
		if(minx + x <= maxx){
			LL ans = 1;
			int head = l;
			while(height[head + 1] == x && head + 1 <= r) head ++;
			REP(i, head, r){
				while(height[i + 1] > x && i + 1 <= r) i ++;
				ans += Solve(head, i, x + 1);
				while(height[i + 1] == x && i + 1 <= r) i ++;
				head = i;
			}
			return ans;
		}else return 0;
	}
}t;
int main()
{
	char s[2000];
	while(scanf("%s", s) == 1 && s[0] != '#'){
		t.Init();
		int len = strlen(s);
		REP(i, 0, len - 1) t.s[i] = s[i] - 'a' + 1;
		t.s[len] = 0;
		t.n = len + 1;
		if(len == 1){
			puts("0");
			continue;
		}
		t.buildSA(27);
		t.getHeight();
		LL ans = 0;
		int head = 1, r = len;
		while(!t.height[head + 1] && head + 1 <= len) head ++;
		REP(i, head, r){
			while(t.height[i + 1] && i + 1 <= len) i ++;
			if(t.height[i]) ans += t.Solve(head, i, 1);
			while(!t.height[i + 1] && i + 1 <= len) i ++;
			head = i;
		}
		printf("%lld\n", ans);
	}
}
