// BZOJ #2584
// Fuboat
/*
这道题做起来真奇怪……
不知道什么原因，离散化后用set存会出问题
由于cmp函数的不断改变，插入过的元素将不一定能找到 
但是每条线段不相交啊……
求拓扑序时只好用原来的线段求，再离散化 
还有，这次线段树写的有点绕……
（set标记真心没用好） 
*/ 
#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
#include <set>
#include <cmath>
#include <stack>
#define REP(i, x, y) for (int i = x, _ = y; i <= _; i ++)
#define rep(i, x, y) for (int i = x, _ = y; i >= _; i --)
#define MSET(a, x) memset(a, x, sizeof(a))
#define CLEAR(a) MSET(a, 0)
#define lc (o << 1)
#define rc (o << 1|1)
template <typename T> bool Chkmin(T &x, T y) { return x > y? x = y, true : false; }
template <typename T> bool Chkmax(T &x, T y) { return x < y? x = y, true : false; } 
const int MAXN = 100000 + 1000, oo = 0x3f3f3f3f;
const double eps = 1e-8;
int n, nowx, cntx, cnty;
struct Line{
	int x1, y1, x2, y2, id;
	Line() {}
	Line(int x1, int y1, int x2, int y2, int id): 
		x1(x1), y1(y1), x2(x2), y2(y2), id(id) {}
	double Gety(int x) const
	{
		return y1 + 1.0 * (y2 - y1) / (x2 - x1) * 1.0 * (x - x1);
	}
	bool operator < (const Line &a) const{
		return Gety(nowx) - a.Gety(nowx) < -eps;
	}
}line[MAXN];

struct Scan{
	int x, flag, id;
	Scan() {}
	Scan(int x, int flag, int id):
		x(x), flag(flag), id(id) {}
	bool operator < (const Scan &a) const {
			return x != a.x? x < a.x : flag < a.flag;
	}
};

struct SegmentTree{
	int minv[MAXN * 8], mv[MAXN * 8];
	void Init()
	{
		MSET(mv, 0x3f); 
		MSET(minv, 0x3f);
	}
	void Update(int o, int x)
	{
		Chkmin(minv[o], x);
		Chkmin(mv[o], x);
	}
	void Pushdown(int o)
	{
		if (mv[o] != oo) {
			Update(lc, mv[o]);
			Update(rc, mv[o]);
			mv[o] = oo;
		}
	}
	void Pushup(int o)
	{
		minv[o] = std::min(minv[lc], minv[rc]);
	}
	void modify(int o, int l, int r, int L, int R, int X)
	{		
		if (L <= l && r <= R) {
			Update(o, X);
			return ;
		}
		
		int mid = (l + r) >> 1;
		Pushdown(o);
		if (L < mid)
			modify(lc, l, mid, L, R, X);
		if (mid < R)
			modify(rc, mid, r, L, R, X);
		Pushup(o);
	}
	
	int query(int o, int l, int r, int L, int R)
	{
		int mid = (l + r) >> 1, minx = oo;
		if (L <= l && r <= R)
			return minv[o];
		
		Pushdown(o);
		// Don't forget this 'pushdown()'!
		
		if (L < mid)
			Chkmin(minx, query(lc, l, mid, L, R));
		if (mid < R)
			Chkmin(minx, query(rc, mid, r, L, R));
			
		return minx;
	}
	
	void Modify(int l, int r, int x)
	{
		modify(1, 1, cntx, l, r, x);
	}
	
	int Query(int l, int r)
	{
		return query(1, 1, cntx, l, r);
	}
} t;

int sx[MAXN * 2], sy[MAXN * 2];
void Discrete()
{
	int cnt = 0;
	
	REP (i, 1, n) {
		sx[cnt ++] = line[i].x1;
		sx[cnt ++] = line[i].x2;
	}
	
	std::sort(sx, sx + cnt);
	cntx = std::unique(sx, sx + cnt) - sx;
}

std::vector<Scan> scan;
std::vector<int> G[MAXN];
std::set<Line> s;
int in[MAXN], order[MAXN], rank[MAXN],dir[MAXN];

void GetDAG()
{
	int flag, id, x1, x2, cnt = 0;
	std::set<Line>::iterator p1, p2;
	
	scan.clear(); 
	s.clear();
	REP (i, 1, n) {
		G[i].clear();
		in[i] = 0;
		x1 = line[i].x1;
		x2 = line[i].x2;
			
		scan.push_back(Scan(x1, 1, i));
		scan.push_back(Scan(x1, 2, i));
		scan.push_back(Scan(x2, 2, i));
		scan.push_back(Scan(x2, 3, i));
	}
	
	std::sort(scan.begin(), scan.end());
	
	for (int i = 0; i < scan.size(); i ++) {
		flag = scan[i].flag;
		id = scan[i].id;
		nowx = scan[i].x;
		switch (flag) {
			case 1:
				s.insert(line[id]);
				break;
			case 2:
				p1 = p2 = s.find(line[id]);
				p2 ++;
				if (p1 != s.begin()) {
					p1 --;
					G[id].push_back(p1->id);
					in[p1->id] ++;
				}
				if (p2 != s.end()) {
					G[p2->id].push_back(id);
					in[id] ++;
				}
				break;
			case 3:
				s.erase(line[id]);
				break;
		}
	}
}

void TopSort()
{
	int u, v, cnt = 0;
	std::stack<int> st;
	
	REP (i, 1, n)
		if (in[i] == 0)
			st.push(i);
	
	while (!st.empty()) {
		u = st.top();
		st.pop();
		order[++ cnt] = u;
		rank[u] = cnt;
		for (int i = 0; i < G[u].size(); i ++) {
			in[v = G[u][i]] --;
			if (!in[v])
				st.push(v);
		}
	}
}

int put[MAXN];
void Task1()
{
	int ans = oo, x1, x2, y1, y2, tmp, u, j = 0;
	
	do {
		j = (j + 1) % 4;
		Discrete();
		GetDAG();
		TopSort();
		t.Init();
		
		tmp = n + 1;

		for (int i = n; i >= 1; i --) {
			u = put[i];
			x1 = std::lower_bound(sx, sx + cntx, line[u].x1) - sx + 1;
			x2 = std::lower_bound(sx, sx + cntx, line[u].x2) - sx + 1;
			if (dir[u] == j && t.Query(x1, x2) < rank[u])
				tmp = i;
			t.Modify(x1, x2, rank[u]);
		}
		
		Chkmin(ans, tmp);
		
		// Rotate
		REP (i, 1, n) {
			x1 = -line[i].y1, x2 = -line[i].y2;
			y1 =  line[i].x1, y2 =  line[i].x2;
			
			if (x1 > x2) { 
				std::swap(x1, x2);
				std::swap(y1, y2); 
			}
				 
			line[i] = Line(x1, y1, x2, y2, line[i].id);
		}
	} while (j);
	
	printf("%d\n", ans);
}

void Task2()
{
	Discrete();
	GetDAG();
	TopSort();
	
	REP (i, 1, n)
		printf("%d %d\n", order[i], 1);
}

void Solve()
{
	Task1();
	Task2();
}

void Init()
{
	int x1, y1, x2, y2, id, d;
	
	scanf("%d", &n);
	REP (i, 1, n) {
		scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
		if (x1 > x2) {
			std::swap(x1, x2);
			std::swap(y1, y2);
		}
		line[i] = Line(x1, y1, x2, y2, i);
	}
	
	REP (i, 1, n) {
		scanf("%d %d", &id, &d);
		put[i] = id;
		dir[id] = d;
	}
}

int main()
{
	#ifndef ONLINE_JUDGE
		freopen("2584.in", "r", stdin);
		freopen("2584.out", "w", stdout);
	#endif
	
	Init();
	Solve();
	
	#ifndef ONLINE_JUDGE
		fclose(stdin);
		fclose(stdout);
	#endif
	
	return 0;
}
