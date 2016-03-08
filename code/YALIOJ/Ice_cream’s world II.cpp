#include <cstdio>
#include <iostream>
#include <cstring>
#define LL long long
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
template <typename T> bool Chkmin(T &x, T y){ return y < x? (x = y, true) : false; }
template <typename T> bool Chkmax(T &x, T y){ return y > x? (x = y, true) : false; }
const int MAXN = 2000 + 100, MAXM = 20000 + 10000;
const LL INF = 1LL << 55;
struct Edge {
    int u, v, num;
    LL w;
    Edge() {}
    Edge(int u, int v, LL w, int num): u(u), v(v), w(w), num(num) { }
}E[MAXM];
void Readin(int &x)
{
	x = 0;
	bool flag = false;
	char c = 0;
	while(c = getchar()){
		if('0' <= c && c <= '9'){
			(x *= 10) += c - '0';
			flag = true;
		}else if(flag) break;
	}
}
int tote, n, m;
LL tot;
int ans;

LL zhuliu()
{
	int u, v;
	LL w;
	const int rt = n + 1;
    static int pre[MAXN], id[MAXN], vis[MAXN];
    static LL in[MAXN];
	id[rt] = rt;
	
	for(int i = 1; i <= tote; i ++)
		if(E[i].u == E[i].v)
			std::swap(E[i --], E[tote --]);

    LL res = 0;
    while(true){
        memset(pre, 0, sizeof(pre));
        REP(i, 1, n) in[i] = INF;
        REP(i, 1, tote){
        	u = E[i].u, v = E[i].v, w = E[i].w;
            if(u != v && Chkmin(in[v], w)){
                pre[v] = u;
                if(u == rt)
					ans = i - m;
            }
    	}

		in[rt] = 0;
		// Don't forget;
		// 'rt' is root, 'in[]' is meaningless for it;
        REP(i, 1, n) if(!pre[i]) return INF;   
        REP(i, 1, n){
			res += in[i];
			vis[i] = id[i] = 0;
		}
		
        int totc = 0;
        vis[rt] = -1;
        for(int i = 1; i <= n; i ++){
            int u;
            for(u = i; vis[u] == 0; u = pre[u])
                vis[u] = i;
            if(vis[u] == i){
                id[u] = ++ totc;
                for(int v = pre[u]; v != u; v = pre[v]){
                    id[v] = totc;
                }
            }
        }
        
        if(totc == 0)
            break;
        for(int i = 1; i <= n; ++i)
            if (id[i] == 0)
                id[i] = ++totc;

        n = totc;
        for(int i = 1; i <= tote; ++i){
            int oriv = E[i].v;
            E[i].u = id[E[i].u];
            E[i].v = id[E[i].v];
            if(u != v) E[i].w -= in[oriv];
            else std::swap(E[i --], E[tote --]);
        }
    }

    return res;
}
void Init()
{
	tot = 0;
	tote = m;
	int x, y, w;
	REP(i, 1, tote){
		Readin(x);
		Readin(y);
		Readin(w);
		E[i] = Edge(x + 1, y + 1, w, i);
		tot += w;
	}
	tot ++;
}
void Solve()
{
	int minx = 0;
	REP(i, 1, n)
		E[tote + i] = Edge(n + 1, i, tot, tote + i);
	tote += n;
	minx = zhuliu();
	if(minx >= 2LL * tot) puts("impossible");
	else printf("%I64d %d\n", minx - tot, ans - 1);
}
int main()
{
	while(scanf("%d%d", &n, &m) == 2){
		Init();
		Solve();
		puts("");
	}
}
