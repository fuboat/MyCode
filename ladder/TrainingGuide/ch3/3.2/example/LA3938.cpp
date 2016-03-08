/*
	NOTICE: There are many details in the code. Please pay attention!
	FROM: UVaLive
	TASK: 3938
	ID: fuboat
	DATA STRUCTURE: Segment tree
	ALGORITHM: Default
	NOTE:
	1. lmax[] means prefix, rmax means suffix;
	2. rightmax(o, l, r) can get the best suffix in [max(l, L), min(r, R)];
	3. leftmax(o, l, r) can get the best prefix in [max(l, L), min(r, R)];
	4. prefix_sum[r] - prefix_sum[l - 1] can get the sum of [l, r]
	MISTAKE:
	1. lmax[]
*/
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define Rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
#define LL long long
#define MSET(a, x) memset(a, x, sizeof(a))
template <typename T> bool chkmin(T &x, T y){return y < x? (x = y, true) : false;}
template <typename T> bool chkmax(T &x, T y){return y > x? (x = y, true) : false;}
const int MAXN = 500000 + 100, MAXM = 500000 + 100;
int a[MAXN], L, R, n, m;
LL prefix_sum[MAXN];
struct sta{
	int l, r;
	sta(){}
	sta(int l, int r):
		l(l), r(r){}
	bool operator < (const sta &a) const{
		if(l != a.l) return l < a.l;
		return r < a.r;
	}
};

LL sum(int l, int r)
{
	return prefix_sum[r] - prefix_sum[l - 1];
}

LL sum(sta a)
{
	return sum(a.l, a.r);
}

sta better(sta a, sta b)
{
	LL suma = sum(a), sumb = sum(b);
	if(suma != sumb)
		if(suma > sumb) return a;
		else return b;
	return a < b? a : b;
}

struct segment{
	int lmaxv[MAXN * 2], rmaxv[MAXN * 2];
	sta maxv[MAXN * 2];
	void build(int o, int l, int r)
	{
		if(l == r){
			lmaxv[o] = rmaxv[o] = l;
			maxv[o] = sta(l, l);
		}else{
			int lc = o << 1, rc = o << 1|1, mid = (l + r) >> 1;
			build(lc, l, mid);
			build(rc, mid + 1, r);
			sta tmp = better(sta(l, lmaxv[lc]), sta(l, lmaxv[rc]));;
			maxv[o] = better(better(maxv[lc], maxv[rc]), sta(rmaxv[lc], lmaxv[rc]));
			lmaxv[o] = tmp.r;
			tmp = better(sta(rmaxv[rc], r), sta(rmaxv[lc], r));
			rmaxv[o] = tmp.l;
		}
		//printf("build(o = %d, l = %d, r = %d, max(l = %d, r = %d)), w = %d, lmax = %d, rmax = %d\n", o, l, r, maxv[o].l, maxv[o].r, sum(maxv[o]), lmaxv[o], rmaxv[o]);
	}
	
	sta leftmax(int o, int l, int r)
	{
		sta best;
		if(r <= R)
			best = sta(l, lmaxv[o]);
		else{
			int lc = o << 1, rc = o << 1|1, mid = (l + r) >> 1;
			if(R <= mid)
				best = leftmax(lc, l, mid);
			else{
				best = leftmax(rc, mid + 1, r);
				best.l = l;
				best = better(best, sta(l, lmaxv[lc]));
			}
		}
		//printf("leftmax(o = %d, l = %d, r = %d, best(l = %d, r = %d))\n", o, l, r, best.l, best.r);
		return best;
	}
	
	sta rightmax(int o, int l, int r)
	{
		sta best;
		if(L <= l) best = sta(rmaxv[o], r);
		else{
			int lc = o << 1, rc = o << 1|1, mid = (l + r) >> 1;
			if(L > mid) best = rightmax(rc, mid + 1, r);
			else{
				best = rightmax(lc, l, mid);
				best.r = r;
				best = better(best, sta(rmaxv[rc], r));
			}
		}
		//printf("rightmax(o = %d, l = %d, r = %d, best(l = %d, r = %d))\n", o, l, r, best.l, best.r);	
		return best;
	}
	
	sta query(int o, int l, int r)
	{
		sta best;
		if(L <= l && r <= R)
			best = maxv[o];		
		else{
			int lc = o << 1, rc = o << 1|1, mid = (l + r) >> 1;
			if(R <= mid) best = query(lc, l, mid);
			else if(L > mid) best = query(rc, mid + 1, r);
			else{
				best = better(query(lc, l, mid), query(rc, mid + 1, r));
				best = better(sta(rightmax(lc, l, mid).l, leftmax(rc, mid + 1, r).r), best);
			}
		}
		//printf("query(o = %d, l = %d, r = %d, best(l = %d, r = %d))\n", o, l, r, best.l, best.r);
		return best;
	}
	
	void clear()
	{
		MSET(lmaxv, 0);
		MSET(rmaxv, 0);
		MSET(maxv, 0);
	}
}t;
int main()
{
	int T = 0;
	while(scanf("%d%d", &n, &m) == 2){
		printf("Case %d:\n", ++T);
		REP(i, 1, n){
			scanf("%d", &a[i]);
			prefix_sum[i] = prefix_sum[i - 1] + a[i];
		}
		t.clear();
		t.build(1, 1, n);
		REP(i, 1, m){
			scanf("%d%d", &L, &R);
			sta ans = t.query(1, 1, n);
			printf("%d %d\n", ans.l, ans.r);
		}
	}
}
