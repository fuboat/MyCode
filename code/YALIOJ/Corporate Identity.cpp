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
int f[MAXL];
int L[MAXM];
int m;
char s[MAXM][MAXL];

void getFail(char* P, int *f, int L)
{
	f[0] = 0; f[1] = 0;
	REP(i, 1, L - 1){
		int j = f[i];
		while(j && P[i] != P[j]) j = f[j];
		f[i + 1] = P[i] == P[j]? j + 1 : 0;
	}
}
int maxi;
bool find(char* T, char* P, int *f, int L)
{
	int j = 0;
	REP(i, 0, 60 - 1){
		while(j && P[j] != T[i]) j = f[j];
		if(P[j] == T[i]) j ++;
		if(j == L) return 1;
	}
	return 0;
}

void Init()
{
	scanf("%d", &m);
	REP(i, 0, m - 1){
		scanf("%s", s[i]);
		
}
bool Check(int pos, int L)
{
	getFail(s[0] + pos, f, L);
	REP(i, 1, m - 1)
		if(!find(s[i], s[0] + pos, f, L))
			return 0;
	return 1;
}
void Solve()
{
	int ans, maxx = 0;
	REP(k, 0, 60 - 1){
		int l = 3, r = 60 - k, tmp = 0;
		while(l <= r){
			int mid = (l + r) >> 1;
			if(Check(k, mid)){
				l = mid + 1;
				tmp = mid;
			}else r = mid - 1;
		}
		if(!tmp) continue;
		if(tmp > maxx){
			ans = k;
			maxx = tmp;
		}else if(tmp == maxx && strcmp(s[0] + k, s[0] + ans) < 0)
			ans = k;
	}
	if(!maxx) puts("no significant commonalities");
	else{
		REP(i, 0, maxx - 1) putchar(s[0][ans + i]);
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
