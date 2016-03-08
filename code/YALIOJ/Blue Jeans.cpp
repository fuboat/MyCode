#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <cstring>
#define DEBUG(...) fprintf(stderr, __VA_ARGS__)
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
bool Chkmax(int &x, int y){ return y > x? x = y, true : false; }
using std::max;
using std::min;
const int MAXM = 20 + 10, MAXL = 60 + 20;
int f[MAXL], L[MAXL];
int m;
char s[MAXM][MAXL];

void getFail(char* P, int *f, int m)
{
	f[0] = 0; f[1] = 0;
	REP(i, 1, m){
		int j = f[i];
		while(j && P[i] != P[j]) j = f[j];
		f[i + 1] = P[i] == P[j]? j + 1 : 0;
	}
}
int find(char* T, char* P, int *f, int m, int n)
{
	int maxa = 0, j = 0;
	REP(i, 0, n - 1){
		while(j && P[j] != T[i]) j = f[j];
		if(P[j] == T[i]){
			j ++;
			Chkmax(maxa, j);
		}
		if(j == m) j = f[j];
	}
	return maxa;
}

void Init()
{
	scanf("%d", &m);
	REP(i, 0, m - 1){
		scanf("%s", s[i]);
		L[i] = strlen(s[i]);
	}
}
void Solve()
{
	int ans = 0, maxx = 0;
	REP(k, 0, L[0] - 1){
		char *S = s[0] + k;
		int mini = 0x7fffffff;
		getFail(S, f, L[0] - k);
		REP(i, 1, m - 1)
			mini = min(mini, find(s[i],S, f, L[0] - k, L[i]));
		if(mini < 3) continue;
		if(Chkmax(maxx, mini) || (maxx == mini && strcmp(s[0] + k, s[0] + ans) < 0))
			ans = k;
	}
	if(!maxx) puts("no significant commonalities");
	else{
		char *S = s[0] + ans;
		REP(i, 0, maxx - 1) putchar(S[i]);
		puts("");
	}
}
int main()
{
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	int T;
	scanf("%d", &T);
	while(T --){
		Init();
		Solve();
	}
}