/*
	FROM: Uva
	ALGORITHM: Dynamic Programming
	DATA STRUCTURE: Default
	MISTAKE:
	1. (line 31, 32) For dp(l, r), when chkmax(f[l][r], sum - dp(i, r)), don't forget to check if i == l, so do chkmax(f[l][r], sum - dp(l, i));
	EXPERIENCE:
	1. (line 34) For a correct dynamic programming, if you put 'vis[l][r]' to the end of the dp fuction, the fuction can also work. it is a way to check.(I find the mistake No.1 in this way);
*/
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXN = 100;
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define Rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
#define LL long long
template <typename T> bool chkmin(T &x, T y){return y < x? (x = y, true) : false;}
template <typename T> bool chkmax(T &x, T y){return y > x? (x = y, true) : false;}
int a[MAXN + 10], f[MAXN + 10][MAXN + 10], s[MAXN + 10];
bool vis[MAXN + 10][MAXN + 10];

int dp(int l, int r)
{
	if(vis[l][r]) return f[l][r];
	//f[l][r] = 0;
	int sum = s[r] - s[l - 1], maxx = sum;
	REP(i, l, r){
		if(i != l) chkmax(maxx, sum - dp(i, r));
		if(i != r) chkmax(maxx, sum - dp(l, i));
	}
	vis[l][r] = 1;
	return f[l][r] = maxx;
}

int main(){
	int n;
	while(scanf("%d", &n) && n){
		memset(vis, 0, sizeof(vis));
		REP(i, 1, n){
			scanf("%d", &a[i]);
			s[i] = s[i - 1] + a[i];
		}
		printf("%d\n", dp(1, n) * 2 - s[n]);
	}
}
