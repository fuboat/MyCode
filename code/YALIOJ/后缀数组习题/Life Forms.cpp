/*
	MISTAKES:
	1. "m = '~' + k + 1", not "m = 'z' + k + 1";
	2. "cnt > (k >> 1) + 1", neither '>=' nor '(k >> 1) + (k & 1)';
*/
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
const int MAXK = 100 + 20, MAXN = 100000 + 3000, MAXM = MAXN;
const int MAXD = 21;
int c[MAXM];
inline void jsort(int *s, int *rank, int *sa, int m, int n)
{
	CLEAR(c);
	REP(i, 0, n - 1)
	 	c[s[rank[i]]] ++;
	REP(i, 1, m - 1)
		c[i] += c[i - 1];
	rep(i, n - 1, 0)
		sa[-- c[s[rank[i]]]] = rank[i];
}
int fs[MAXN], k;
struct rmq{
	int minv[MAXN][MAXD];
	void Init(int *a, int n)
	{
		REP(i, 0, n - 1) minv[i][0] = a[i];
		int d = log(1.0 * n)/log(2.0);
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
	void Init(){ CLEAR(ok); }
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
			swap(x, y);//Ð¡¼¼ÇÉ 
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
		//DEBUG("n = %d\nheight[] = ", n);
		//REP(i, 0, n - 1) DEBUG(i == n - 1? "%d\n" : "%d ", height[i]);
	}
	void Solve()
	{
		
		t.Init(height, n);
		vector<int> ans;
		int cnt = 0, head = 0, maxx = 0;
		REP(i, 0, n - 1){
			if(fs[sa[i]] == 0){ head = i + 1; continue; }
			if(!ok[fs[sa[i]]]) cnt ++;
			ok[fs[sa[i]]] ++;
			if(cnt >= (k >> 1) + 1){
				while(fs[sa[head]] == 0 || ok[fs[sa[head]]] > 1 || cnt > (k >> 1) + 1){
					ok[fs[sa[head]]] --;
					if(ok[fs[sa[head]]] == 0) cnt --;
					head ++;
				}
				if(head == 4 && i == 9)
				{
					
				}
				int tmp = t.Query(head + 1, i);
				if(Chkmax(maxx, tmp)){
					ans.clear();
					ans.push_back(sa[i]);
				}else if(tmp == maxx)
					ans.push_back(sa[head]);
			}
		}
		if(maxx){
			char tmp[MAXN] = {0};
			set<string> again;
			REP(i, 0, ans.size() - 1){
				int from = ans[i];
				REP(j, 0, maxx - 1)
					tmp[j] = s[from + j] + 'a' - 1;
				tmp[maxx] = 0;
				if(again.count(string(tmp))) continue;
				else{
					again.insert(string(tmp));
					puts(tmp);
				}
			}
		}else puts("?");
	}
}t;
void Init()
{
	char s[3000] = {0};
	int v = -1;
	t.Init();
	REP(i, 1, k){
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
	t.buildSA(100 + k + 1);
	t.getHeight();
}
int main()
{
	bool flag = 0;
	while(scanf("%d", &k) && k){
		if(!flag) flag = 1;
		else puts("");
		if(k == 1){
			char s[3000];
			scanf("%s", s);
			puts(s);
			continue;
		}
		Init();
		t.Solve();
	}
}
