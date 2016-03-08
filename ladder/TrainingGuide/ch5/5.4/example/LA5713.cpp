// LA5713
// ×îÐ¡Æ¿¾±Â·
// Fuboat 
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
#include <cmath>
#define CLEAR(a) memset(a, 0, sizeof(a))
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
template <typename T> bool Chkmin(T &x, T y){ return y < x? (x = y, true) : false; }
template <typename T> bool Chkmax(T &x, T y){ return y > x? (x = y, true) : false; }
const int MAXN = 2000 + 100, MAXM = MAXN * MAXN * 2, MAXD = 23;
/*Public---------------------------------------------------*/
int far[MAXN][MAXN];
/*Union Set------------------------------------------------*/
struct Union_set{
	int pa[MAXN];
	int Find(int x){ return x == pa[x]? x : pa[x] = Find(pa[x]); }
	void Init(int N){ REP(i, 1, N) pa[i] = i; }
	bool Union(int x, int y)
	{
		x = Find(x);
		y = Find(y);
		return x == y? false : (pa[x] = y, true);
	}
}t;

struct RMQ{
	int maxv[MAXN][MAXD];
	int pa[MAXN][MAXD];
	void Init(int *a, int *fa, int N)
	{
		int d = log(N) / log(2), p;
		REP(i, 1, N){
			maxv[i][0] = a[i];
			pa[i][0] = fa[i];
		}
		REP(j, 1, d) REP(i, 1, N)
			if(p = pa[i][j - 1]){
			pa[i][j] = pa[p][j - 1];
			maxv[i][j] = std::max(maxv[i][j - 1], maxv[p][j - 1]);
		}
	}
	
	int Max(int &u, int d){
		int ans = maxv[u][d];
		u = pa[u][d];
		return ans; 
	}
	int Fa(int u, int d){ return pa[u][d]; }
};
namespace LCA{
	RMQ r;
	int tote;
	int head[MAXN], fa[MAXN], dis[MAXN], deep[MAXN];
	int next[MAXM], val[MAXM], to[MAXM];
	
	void Init(int N)
	{
		REP(i, 1, N)
			fa[i] = dis[i] = deep[i] = head[i] = 0;
		fa[1] = deep[1] = 1;
		tote = 0;
	}
	
	void AddEdge(int u, int v, int w)
	{
		to[++ tote] = v;
		val[tote] = w;
		next[tote] = head[u];
		head[u] = tote;
	}
	
	void Dfs(int u)
	{
		int v, w;
		for(int i = head[u]; i; i = next[i]){
			v = to[i];
			w = val[i];
			if(!fa[v]){
				fa[v] = u;
				deep[v] = deep[u] + 1;
				dis[v] = w;
				Dfs(v);
			}
		}
	}
	
	void Exec(int N)
	{
		// Don't forget 'fa[1] = 1'!
		Dfs(1);
		r.Init(dis, fa, N);
	}
	
	int Query(int a, int b)
	{
		int maxx = 0, h, cnt = 0, d;
		if(deep[a] < deep[b]) std::swap(a, b);
		
		h = deep[a] - deep[b];
		d = log(deep[a]) / log(2);
		while(h){
			if(h & 1)
				Chkmax(maxx, r.Max(a, cnt));
			h >>= 1;
			cnt ++;
			// Don't forget 'cnt ++';
		}
				
		if(a == b) return maxx;
		
		rep(i, d, 0)
			if(r.Fa(a, i) && r.Fa(a, i) != r.Fa(b, i)){
				Chkmax(maxx, r.Max(a, i));
				Chkmax(maxx, r.Max(b, i));
			}
		Chkmax(maxx, dis[a]);
		Chkmax(maxx, dis[b]);
		return maxx;
	}
}

namespace Kruskal
{
	struct Edge{
		int u, v, w;
		Edge(){}
		Edge(int u, int v, int w): u(u), v(v), w(w){}
		bool operator < (const Edge &a) const{ return w < a.w; }
	}s[MAXM];
	double Exec(int N, int M)
	{
		int u, v, w;
		double tot = 0;
		t.Init(N);
		LCA::Init(N);
		std::sort(s + 1, s + M + 1);
		REP(i, 1, M){
			u = s[i].u;
			v = s[i].v;
			w = s[i].w;
			if(t.Union(u, v)){
				LCA::AddEdge(u, v, w);
				LCA::AddEdge(v, u, w);
				tot += sqrt(1.0 * w);
			}
		}
		LCA::Exec(N);
		return tot;
	}
}
/*Main program---------------------------*/
int n;
int P[MAXN][2], size[MAXN];
int Far(int a, int b)
{
	int x2 = P[a][0] - P[b][0];
	int y2 = P[a][1] - P[b][1];
	x2 *= x2;
	y2 *= y2;
	return x2 + y2;
}
int tote;
void Init()
{
	CLEAR(far);
	CLEAR(size);
	using namespace Kruskal;
	tote = 0;
	int x, y, p;
	REP(i, 1, n){
		scanf("%d%d%d", &x, &y, &p);
		P[i][0] = x;
		P[i][1] = y;
		size[i] = p;
	}
	REP(i, 1, n) REP(j, i + 1, n)
		s[++ tote] = Edge(i, j, Far(i, j));
}
void Solve()
{
	using namespace Kruskal;
	double ans = -1, tot = Exec(n, tote);
	REP(i, 1, n) REP(j, i + 1, n){
		double L;
		L = LCA::Query(i, j);
		Chkmax(ans, 1.0 * (size[i] + size[j]) / (tot - sqrt(L)));
	}
	printf("%.2lf\n", ans);
}
main()
{
	int T;
	scanf("%d", &T);
	while(T --){
		scanf("%d", &n);
		Init();
		Solve();
	}
}
