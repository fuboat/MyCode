// BZOJ 2877
// Fuboat
// SegmentTree2D
#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
#define MSET(a, x) memset(a, x, sizeof(a))
#define CLEAR(a) MSET(a, 0)
#define LL long long
#define int long long
#define lc o << 1
#define rc o << 1|1
#ifdef WIN32
#define ll "%I64d"
#else
#define ll "%lld"
#endif
const int MAXN = 500000 + 1000;
int Gcd(int a, int b)
{
	if (a < 0)
		a = -a;
	if (b < 0)
		b = -b;

	int r;
	while (b) {
		r = a % b;
		a = b;
		b = r;
	}
	return a;
}
struct SegmentTree{
	int n, L, R, P, X, flag, *gcd;
	SegmentTree() {}
	SegmentTree(int N, int *v)
	{
		n = N;
		gcd = new int[n * 4];
		Build(1, 1, n, v);
	}
	void Build(int o, int l, int r, int *v)
	{
		int mid = (l + r) >> 1;
		
		if (l != r) {
			Build(lc, l, mid, v);
			Build(rc, mid + 1, r, v);
			gcd[o] = Gcd(gcd[lc], gcd[rc]);
		} else 
			gcd[o] = v[l];
	}
	
	void modify(int o, int l, int r)
	{
		int mid = (l + r) >> 1;
		
		if (l == r)
			(gcd[o] *= flag) += X;
		else {
			if (P <= mid)
				modify(lc, l, mid);
			else
				modify(rc, mid + 1, r);
			gcd[o] = Gcd(gcd[lc], gcd[rc]);
		}
	}
	
	void query(int o, int l, int r)
	{
		int mid = (l + r) >> 1;
		
		if (L <= l && r <= R)
			X = Gcd(X, gcd[o]);
		else {
			if (L <= mid)
				query(lc, l, mid);
			if (mid < R)
				query(rc, mid + 1, r);
		}
	}
	
	void Modify(int p, int x)
	{
		P = p, X = x, flag = 0;
		modify(1, 1, n);
	}
	
	void Add(int p, int x)
	{
		P = p, X = x, flag = 1;
		modify(1, 1, n);
	}
	
	int Query(int l, int r)
	{
		L = l, R = r, X = 0;
		query(1, 1, n);
		return X;
	}
};
struct SegmentTree2D{
	int rP, cP, rL, rR, cL, cR, m, n, X, *tmp;
	SegmentTree *tree;
	SegmentTree2D() {}
	SegmentTree2D(int M, int N, int **val): m(M), n(N)
	{
		tree = new SegmentTree[m * 4];
		tmp = new int[n * 4];
		Build(1, 1, m, val);
	}
	
	void Build(int o, int l, int r, int **val)
	{
		int mid = (l + r) >> 1;
		if (l != r) {
			Build(lc, l, mid, val);
			Build(rc, mid + 1, r, val);
			REP (i, 1, n)
				tmp[i] = Gcd(tree[lc].Query(i, i), tree[rc].Query(i, i));
			tree[o] = SegmentTree(n, tmp);
		}
		else
			tree[o] = SegmentTree(n, val[l]);
	}
	
	int query(int o, int l, int r)
	{
		int mid = (l + r) >> 1;
		
		if (rL <= l && r <= rR)
			X = Gcd(X, tree[o].Query(cL, cR));
		else {
			if (rL <= mid)
				query(lc, l, mid);
			if (mid < rR)
				query(rc, mid + 1, r);
		}
	}

	void modify(int o, int l, int r)
	{
		int mid = (l + r) >> 1;
		
		if (l == r)
			tree[o].Add(cP, X);
		else {
			if (rP <= mid)
			// There is 'rP', not 'cP'!
				modify(lc, l, mid);
			else modify(rc, mid + 1, r);
			tree[o].Modify(cP, Gcd(tree[lc].Query(cP, cP), tree[rc].Query(cP, cP)));
			// There is 'cP', not 'rP'!
		}
	}
	
	void Modify(int i, int j, int x)
	{
		if (i <= 0 || j <= 0 || i > m || j > n)
			return ;
			
		rP = i, cP = j, X = x;
		modify(1, 1, m);
	}
	
	int Query(int xl, int xr, int yl, int yr)
	{
		rL = xl, rR = xr, cL = yl, cR = yr;
		X = 0;
		query(1, 1, m);
		return X;
	}
} t;

int m, n, x, y, T, **a, **val;
void Init()
{
	val = new int*[m + 100];
	a = new int*[m + 100];
	REP (i, 1, m) {
		a[i] = new int[n + 100];
		val[i] = new int[n + 100];
	}
		
	scanf(ll ll ll, &x, &y, &T);
	REP (i, 1, m)
		REP (j, 1, n)
			scanf (ll, &a[i][j]);
			
	REP (i, 1, m)
		REP (j, 1, n) {
			if (i < x && j < y)
				val[i][j] = a[i][j] - a[i + 1][j] - a[i][j + 1] + a[i + 1][j + 1];
			else if (i < x && j > y)
				val[i][j] = a[i][j] - a[i + 1][j] - a[i][j - 1] + a[i + 1][j - 1];
			else if (i > x && j < y)
				val[i][j] = a[i][j] - a[i - 1][j] - a[i][j + 1] + a[i - 1][j + 1];
			else if (i > x && j > y)
				val[i][j] = a[i][j] - a[i - 1][j] - a[i][j - 1] + a[i - 1][j - 1];
			else if (i == x && j > y)
				val[i][j] = a[i][j] - a[i][j - 1];
			else if (i == x && j < y)
				val[i][j] = a[i][j] - a[i][j + 1];
			else if (i > x && j == y)
				val[i][j] = a[i][j] - a[i - 1][j];
			else if (i < x && j == y)
				val[i][j] = a[i][j] - a[i + 1][j];
			else
				val[i][j] = a[i][j];
		}
//	REP (i, 1, m) {
//		REP (j, 1, n)
//			printf(ll" ", val[i][j]);
//		puts("");
//	}
	t = SegmentTree2D(m, n, val);
}

void Solve()
{
	int flag, x1, x2, y1, y2, c, ans;
	REP (i, 1, T) {
		scanf(ll ll ll ll ll, &flag, &x1, &y1, &x2, &y2);
		if (flag == 0) {
			ans = t.Query(x - x1, x + x2, y - y1, y + y2);
			printf(ll"\n", ans);
		} else {
			scanf(ll, &c);
	        if (x1<=x && y1<=y)
			    t.Modify(x1-1, y1-1,  c); else
	        if (x1> x && y1> y) 
				t.Modify(x1  , y1  ,  c);
			else if (x1<=x && y1> y) 
				t.Modify(x1-1, y1  , -c);
			else if (x1> x && y1<=y) 
				t.Modify(x1  , y1-1, -c);
	
	        if (x2< x && y2< y) 
				t.Modify(x2  , y2  ,  c);
			else if (x2>=x && y2>=y) 
				t.Modify(x2+1, y2+1,  c);
			else if (x2< x && y2>=y) 
				t.Modify(x2  , y2+1, -c); 
			else if (x2>=x && y2< y) 
				t.Modify(x2+1, y2  , -c);
	
	        if (x1<=x && y2>=y) 
				t.Modify(x1-1, y2+1,  c); 
			else if (x1> x && y2< y) 
				t.Modify(x1  , y2  ,  c); 
			else if (x1<=x && y2< y) 
				t.Modify(x1-1, y2  , -c); 
			else if (x1> x && y2>=y) 
				t.Modify(x1  , y2+1, -c);
	
	        if (x2< x && y1> y)
				t.Modify(x2  , y1  ,  c); 
			else if (x2>=x && y1<=y)
				t.Modify(x2+1, y1-1,  c); 
			else if (x2< x && y1<=y)
				t.Modify(x2  , y1-1, -c); 
			else if (x2>=x && y1> y)
				t.Modify(x2+1, y1  , -c);
	
	        if (x1<=x && x2>=x)
	        {
	            if (y1<=y)
					t.Modify(x, y1-1, -c);
				else
					t.Modify(x, y1  ,  c);
	            if (y2>=y)
					t.Modify(x, y2+1, -c);
				else 
					t.Modify(x, y2  ,  c);
	        }
	        if (y1<=y && y2>=y)
	        {
	            if (x1<=x) 
					t.Modify(x1-1, y, -c); 
				else 
					t.Modify(x1  , y,  c);
	            if (x2>=x) 
					t.Modify(x2+1, y, -c); 
				else 
					t.Modify(x2  , y,  c);
	        }
	
	        if (x1<=x && x2>=x && y1<=y && y2>=y) t.Modify(x, y, c);
		}
	}
}

main()
{
	#ifndef ONLINE_JUDGE
		freopen("in.txt", "r", stdin);
		freopen("out.txt", "w", stdout);
	#endif
	scanf(ll ll, &m, &n);
	Init();
	Solve();
}
