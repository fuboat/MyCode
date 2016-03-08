#include <cstdio>
#include <queue>
#include <cstring>
#define MSET(a, x) memset(a, x, sizeof(a))
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
using namespace std;
const int MAXN = 1000 + 100, MAXS = 26, MAXl = 60 + 1, MAXT = MAXN * MAXl;
int tot[MAXN];
struct Trie{
	int ch[MAXT][MAXS];
	int val[MAXT];
	int f[MAXT];
	int last[MAXT];
	int sz;
	int idx(char c){ return c - 'A'; }
	void Init(){ MSET(ch, 0); MSET(val, 0); MSET(f, 0); MSET(last, 0); MSET(tot, 0); sz = 0; }
	void Update(int u){ if(u){ tot[val[u]] ++; Update(last[u]); } }
	void Insert(char *s, int v)
	{
		int u = 0, len = strlen(s);
		REP(i, 0, len - 1){
			int c = idx(s[i]);
			if(!ch[u][c]) ch[u][c] = ++ sz;
			u = ch[u][c];
		}
		val[u] = v;
	}
	void Find(char *T)
	{
		int L = strlen(T), j = 0;
		REP(i, 0, L - 1){
			if(T[i] < 'A' || T[i] > 'Z'){ j = 0; continue; }
			int c = idx(T[i]);
			while(j && !ch[j][c]) j = f[j];
			j = ch[j][c];
			if(val[j]) Update(j);
			else if(last[j]) Update(last[j]);
		}
	}
	void getFail()
	{
		queue<int> h;
		f[0] = 0;
		REP(c, 0, MAXS - 1){
			int u = ch[0][c];
			if(u){last[u] = f[u] = 0; h.push(u);}
		}
		while(!h.empty()){
			int r = h.front(); h.pop();
			REP(c, 0, MAXS - 1){
				int u = ch[r][c];
				if(!u) continue;
				h.push(u);
				int v = f[r];
				while(v && !ch[v][c]) v = f[v];
				f[u] = ch[v][c];
				last[u] = val[f[u]]? f[u] : last[f[u]];
			}
		}
	}
}t;
char T[2000000 + 100];
char s[MAXN][MAXl];
int main()
{
	int n;
	while(scanf("%d", &n) == 1 && n){
		t.Init();
		REP(i, 1, n){
			scanf("%s", s[i]);
			t.Insert(s[i], i);
		}
		t.getFail();
		scanf("%s", T);
		t.Find(T);
		REP(i, 1, n) if(tot[i])
			printf("%s: %d\n", s[i], tot[i]);
	}
}
