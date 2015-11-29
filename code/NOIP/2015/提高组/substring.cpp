#include <cstdio>
#define REP(i, x, y)  for(int i = x, _ = y ; i <= _; i ++)
#define LL int
const int MAXN = 1000, MAXM = 200, MAXK = 200, MOD = 1000000007;
int k, m, n;
char a[MAXN + 2], b[MAXM + 2];
LL tmp[2][MAXM + 2][MAXK + 2], f[MAXM + 2][MAXK + 2];

void Begin()
{
	freopen("substring.in", "r", stdin);
	freopen("substring.out", "w", stdout);
}

void Init()
{
	scanf("%d%d%d", &n, &m, &k);
	getchar();
	gets(a + 1);
	gets(b + 1);
	f[0][0] = 1;
}

void Work()
{
	bool ok = 0;
	REP(i, 1, n){
		ok = !ok;
		REP(j, 1, m) REP(w, 1, k){
			LL &now = f[j][w], &to = tmp[ok][j][w];
			now = (now + to) % MOD;
			to = 0;
		}
		REP(j, 1, m) if(a[i] == b[j])
			REP(w, 1, k){
				LL &now = tmp[ok][j][w], *to = tmp[!ok][j - 1];
				now = (0LL + now + to[w] + to[w - 1] + f[j - 1][w - 1]) % MOD;
			}
	}
	int ans = (0LL + f[m][k] + tmp[ok][m][k] + tmp[!ok][m][k]) % MOD;
	printf("%d\n", ans);
}

void End()
{
	fclose(stdin);
	fclose(stdout);
}

int main()
{
	//Begin();
	Init();
	Work();
	//End();
}
