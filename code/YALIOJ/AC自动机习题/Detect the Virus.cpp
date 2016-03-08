#include <cstdio>
#include <cstring>
#include <queue>
using std::queue;
#define MSET(a, x) memset(a, x, sizeof(a))
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
#define LL long long
char ss[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
int tt[300];
char T[3000];
int a[3000];
int n, m;
const int MAXNODE = 50000 + 1000, MAXS = 300, MAXN = 10000 + 1000;
struct Trie{
	int ch[MAXNODE][MAXS], val[MAXNODE], f[MAXNODE], last[MAXNODE], sz, ans;
	bool vis[MAXNODE];
	void Init(){ MSET(ch, 0); MSET(val, 0); MSET(f, 0); MSET(last, 0); sz = 1; }
	void Clear(){ MSET(vis, 0); ans = 0; }
	void Insert(int len)
	{
		int u = 0, c;
		REP(i, 0, len - 1){
			if(!ch[u][c = a[i]]) ch[u][c] = ++ sz;
			u = ch[u][c];
		}
		val[u] ++;
	}
	void Update(int j)
	{
		if(vis[j]) return ;
		while(j = last[j] && !vis[j]){ ans += (vis[j] = 1); }
	}
	void Find(int L)
	{
		int j = 0;
		REP(i, 0, L - 1)
			if(val[j = ch[j][a[i]]]) Update(j);
			else Update(last[j]);
	}
	void getFail()
	{
		int u, r, v;
		queue<int> h;
		REP(c, 0, MAXS - 1){ if(u = ch[0][c]) h.push(u); }
		while(!h.empty()){
			r = h.front(); h.pop();
			REP(c, 0, MAXS - 1){
				u = ch[r][c]; v = f[r];
				if(!u){ ch[r][c] = ch[f[r]][c]; continue; }
				h.push(u);
				while(v && !ch[v][c]) v = f[v];
				f[u] = ch[v][c];
				last[u] = val[f[u]]? f[u] : last[f[u]];
			}
		}
	}
}t;
struct Base64{
	bool bit[100000];
	void Init(){  REP(i, 0, 64 - 1) tt[ss[i]] = i; }
	int Bit(char *T)
	{
		MSET(bit, 0);
		int len = strlen(T), cnt = len * 6 / 8, x;
		REP(i, 0, len - 1){
			if(T[i] == '='){
				cnt -= i == len - 1? 1 : 2;
				break;
			}
			x = tt[T[i]];
			rep(j, 5, 0){ bit[i * 6 + j] = (x & 1); x >>= 1; }
		}
		return cnt * 8;
	}
	int Change()
	{
		int x = 0, len = Bit(T);
		REP(i, 0, len - 1){
			x <<= 1; x |= bit[i];
			if(!((i + 1) % 8)){ a[i / 8] = x; x = 0; }
		}
		return len / 8;
	}

}base64;

void Init()
{
	t.Init();
	REP(i, 1, n){
		scanf("%s", T);
		t.Insert(base64.Change());
	}
	t.getFail();
}

void Solve()
{
	scanf("%d", &m);
	REP(i, 1, m){
		scanf("%s", T);
		t.Clear();
		t.Find(base64.Change());
		printf("%d\n", t.ans);
	}
	puts("");
}
int main()
{
	base64.Init();
	while(scanf("%d", &n) == 1){ Init(); Solve(); }
}
