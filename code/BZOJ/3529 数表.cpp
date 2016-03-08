// BZOJ #3529
// Fuboat
// Math
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
#define MSET(a, x) memset(a, x, sizeof(a))
#define CLEAR(a) MSET(a, 0)
template <typename T> bool Chkmax(T &x, T y) { return y > x? x = y, true : false; } 
template <typename T> bool Chkmin(T &x, T y) { return y < x? x = y, true : false; }
const int MAXN = 100000 + 1000;
const long long MOD = 1LL << 31;
int totque;
int mu[MAXN], premu[MAXN], spresum[MAXN], ans[MAXN], divsum[MAXN];
struct Fenwick{
	int n;
	int sumv[MAXN];
	Fenwick():
		n(MAXN - 1000){}
	void Init(int N = MAXN - 1000) { n = N; }
	void Add(int p, int x)
	{
		while (p <= n) {
			sumv[p] += x;
			p += p & -p;
		}
	}
	int Query(int p)
	{
		int tot = 0;
		while (p > 0) {
			tot += sumv[p];
			p -= p & -p;
		}
		return tot;
	}
	inline int Query(int l, int r)
	{
		return Query(r) - Query(l - 1);
	}
} t;
struct Que{
	int val, m, n, num, flag;
	Que() {}
	Que(int val, int m, int n, int num, int flag):
		val(val), m(m), n(n), num(num), flag(flag){} 
	bool operator < (const Que &a) const {
		if (val != a.val)
			return val < a.val;
		return flag < a.flag; 
	}
	inline void Get(int &VAL, int &M, int &N, int &NUM, int &FLAG) {
		VAL = val;
		M = m;
		N = n;
		NUM = num;
		FLAG = flag;
	}
} que[MAXN * 2];
void GetPreSum(int *a, int *b, int N)
{
	REP (i, 1, N)
		b[i] = b[i - 1] + a[i];
}
void GetMuAndDivsum(int N)
{
	static int pri[MAXN];
	static bool vis[MAXN];
	int totpri = 0, now;
	
	mu[1] = 1;
	REP (i, 1, N)
		REP (j, 1, N / i)
			divsum[i * j] += i;
			
	REP (i, 2, N) {
		if (!vis[i]) {
			pri[++ totpri] = i;
			mu[i] = -1;
		}
		REP (j, 1, totpri) {
			if (i * pri[j] > N)
				break;
				
			now = i * pri[j];
			vis[now] = true;
			
			if (i % pri[j] == 0) {
				mu[now] = 0;
				break;
			} else
				mu[now] = -mu[i];
		}
	}
}
int T;
void Init(int N = MAXN - 1000)
{
	int m, n, a;
	
	GetMuAndDivsum(N);
	REP (i, 1, N)
		que[++ totque] = Que(divsum[i], 0, 0, i, 0);
}
int Work(int N, int M)
{
	int last, n, m;
	int tot = 0;
	
	if (N > M)
		std::swap(N, M);
	
	for (int i = 1; i <= N; i = last + 1) {
		n = N / i, m = M / i;
		last = std::min(M / m, N / n);
		tot += n * m * t.Query(i, last);
	}
	return tot;
}
void Solve(int N = MAXN - 1000)
{
	int val, n, m, num, flag;
	std::sort(que + 1, que + totque + 1);
	
	t.Init(N);
	REP (i, 1, totque) {
		que[i].Get(val, m, n, num, flag);
		
		if (flag)
			ans[num] = (unsigned int)Work(m, n) % MOD;
			// If the number is 'int' and smaller than '0', the way it 'mod MOD' is unexpected.
			// We should change it into 'unsigned int'.
			
		else {
			REP (j, 1, N / num)
				t.Add(num * j, divsum[num] * mu[j]);
				// There is 'n', not other var!
		}
	}
	
	REP (i, 1, T)
		printf("%d\n", ans[i]);
}
int main()
{
	int N = 0, a, m, n;
	
	scanf("%d", &T);
	REP (i, 1, T) {
		scanf("%d%d%d", &m, &n, &a);
		que[++ totque] = Que(a, m, n, i, 1);
		Chkmax(N, m);
		Chkmax(N, n);
	}
	
	Init(N);
	Solve(N);
}
