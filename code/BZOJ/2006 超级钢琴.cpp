#include <cstdio> 
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <queue>
#define LL long long
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
template<typename T> bool Chkmax(T &x, T y) { return y > x? x = y, true : false; }
template<typename T> bool Chkmin(T &x, T y) { return y < x? x = y, true : false; }
const int MAXN = 1 << 20, MAXD = 21, oo = 0x3f3f3f3f;
int n, k, L, R;
struct rmq{
	LL maxv[MAXN][MAXD], posv[MAXN][MAXD];
	void Init(int *a, int N)
	{
		int d = log(N) / log(2), u;
		REP(i, 1, N) {
			maxv[i][0] = a[i];
			posv[i][0] = i;
		}

		REP(j, 1, d)
			REP(i, 1, N) {
				u = i + (1 << j - 1);
				maxv[i][j] = maxv[i][j - 1];
				posv[i][j] = posv[i][j - 1];
				if(posv[u][j - 1] && Chkmax(maxv[i][j], maxv[u][j - 1]))
					posv[i][j] = posv[u][j - 1];
			}
	}
	
	LL Query(int l, int r)
	{
		int d = log(r - l + 1) / log(2);
		r = r - (1 << d) + 1;
		if(maxv[l][d] > maxv[r][d])
			return posv[l][d];
		return posv[r][d];
	}
}Q;

int sumv[MAXN];
struct Node{
	int p, l, r, k, dis;
	LL val;
	Node(){}
	Node(int p, int l, int r): p(p), l(l), r(r), dis(0)
	{
		k = Q.Query(l, r);
		val = sumv[k] - sumv[p - 1];
	}
	bool operator < (const Node a) const {
		return val < a.val;
	}
};
std::priority_queue<Node> q;
void Insert(int p, int l, int r)
{
	if(r > n)
		r = n;
	if(l < p)
		l = p;
	if(l > r)
		return ;
	q.push(Node(p, l, r));
}

int a[MAXN];
void Init()
{
	scanf("%d%d%d%d", &n, &k, &L, &R);
	REP(i, 1, n) {
		scanf("%d", &a[i]);
		sumv[i] = sumv[i - 1] + a[i];
	}
	Q.Init(sumv, n);
	REP(i, 1, n)
		Insert(i, i + L - 1, i + R - 1);
}

void Solve()
{
	int pos, p, l, r;
	LL ans = 0;
	Node now;
	
	REP(i, 1, k) {
		now = q.top();
		q.pop();
		l = now.l;
		r = now.r;
		pos = now.k;
		p = now.p;
		ans += now.val;
		Insert(p, l, pos - 1);
		Insert(p, pos + 1, r);
	}
	printf("%lld\n", ans);
}

int main()
{
	Init();
	Solve();
}
