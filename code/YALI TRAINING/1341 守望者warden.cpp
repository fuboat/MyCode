#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#define LL long long
#define CLEAR(a) memset(a, 0, sizeof(a))
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
using namespace std;
/*Public-----------------------------------------------*/
const int MAXN = 10 + 5, MOD = 7777777;
/*Matrix-----------------------------------------------*/
struct Matrix{
	LL s[MAXN][MAXN];
	int r, c;
	Matrix(){ CLEAR(s); }
	Matrix(int r, int c): r(r), c(c){ CLEAR(s); }
	Matrix(int k)
	// Init the recursion formula(递推式) similar to Fibonacci sequence;
	// 'k' means f[n] = f[n - 1] + f[n - 2] + ... + f[n - k] in this formula;
	{
		CLEAR(s);
		r = c = k;
		REP(i, 0, r - 2) s[i][i + 1] = 1;
		REP(i, 0, r - 1) s[r - 1][i] = 1;
	}
	Matrix(const LL *f, int k)
	{
		CLEAR(s);
		r = k, c = 1;
		REP(i, 0, k - 1)
			s[i][0] = f[i];
	}
	Matrix operator * (const Matrix &a) const
	{
		Matrix tmp(r, c);
		REP(i, 0, r - 1) REP(j, 0, a.c - 1) REP(k, 0, c - 1)
			(tmp.s[i][j] +=  s[i][k] * a.s[k][j]) %= MOD;
		return tmp;
	}
	Matrix operator *= (const Matrix &a){ *this = *this * a;return *this; }
};
Matrix Pow(const Matrix &a, int k)
{
	static Matrix New;
	vector<bool> c;
	New = a;
	int cnt(0);
	while(k){
		c.push_back(k & 1);
		k >>= 1;
	}
		rep(i, c.size() - 2, 0){
		New *= New;
		if(c[i])
	 		New *= a;
	}
	return New;
}
Matrix start, ans;
// 'ans'为递推矩阵;
// 'start'为初始矩阵;
/*Program----------------------------------------------*/
int n, k;
LL f[MAXN];
void Init()
{
	ans = Matrix(n);
	f[0] = 1;
	REP(i, 0, n - 1) REP(j, i + 1, n - 1)
		(f[j] += f[i]) %= MOD;
	start = Matrix(f, n);
}
void Solve()
{
	ans = Pow(ans, k) * start;
	printf("%d\n", int(ans.s[0][0]));
}       
int main()
{
	while(scanf("%d%d", &n, &k) == 2 && n && k){
		Init();
		Solve();
	}
}
