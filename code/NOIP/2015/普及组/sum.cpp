#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define Rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
#define LL long long 
#define LD long double
const int oo = 0x7fffffff, MAXN = 100000, MOD = 10007;
struct sta{
	sta(){}
	sta(int P, int W):P(P), W(W){}
	int P, W;
};
vector<sta>f[MAXN + 100][2];
int a[MAXN + 100];
int n, m, ans;

void Write(LL ans)
{
	if(!ans) printf("0");
	else if(ans < 0){
		ans = -ans;
		putchar('-');
	}else{
		char c[100] = {0};
		int cnt = 0;
		while(ans){
			c[cnt] = ans % 10 + '0';
			ans /= 10;
			cnt ++;
		}
		Rep(i, cnt - 1, 0) putchar(c[i]);
	}
}

void Begin()
{
	freopen("sum.in", "r", stdin);
	freopen("sum.out", "w", stdout);
}

void Init()
{
	scanf("%d%d", &n, &m);
	REP(i, 1, n) scanf("%d", &a[i]);
	REP(i, 1, n){
		int c;
		scanf("%d", &c);
		f[c][i & 1].push_back(sta(i, a[i]));
	}
}

void Solve()
{
	REP(i, 1, m) REP(j, 0, 1){
		int siz = f[i][j].size();
		LL sum = 0;
		REP(k, 0, siz - 1){
			int pos = f[i][j][k].P, w = f[i][j][k].W;
			sum += pos;
			ans += 1LL * pos * w * (siz - 1);
			ans %= MOD;
		}
		REP(k, 0, siz - 1){
			int pos = f[i][j][k].P, w = f[i][j][k].W;
			ans += 1LL *(sum - pos)* w;
			ans %= MOD;
		}
	}
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
	Solve();
	Write(ans);
	putchar('\n');
	//End();
	return 0;
}
