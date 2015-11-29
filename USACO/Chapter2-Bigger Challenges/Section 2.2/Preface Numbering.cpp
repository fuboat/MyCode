/*
	ID: 60303451
	TASK: preface
	LANG: C++
*/
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define Rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
#define LL long long
template <typename T> bool chkmin(T &x, T y){return y < x? (x = y, true) : false;}
template <typename T> bool chkmax(T &x, T y){return y > x? (x = y, true) : false;}
const int MAXN = 3500;
const char to[10][10][10] = {
{"", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"},
{"", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"},
{"", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"},
{"", "M", "MM", "MMM", ""  , "" , ""  , ""   , ""    , ""  }
};
char ans[] = {"IVXLCDM"};
int sum[1000];

int main()
{
	freopen("preface.in", "r", stdin);
	freopen("preface.out", "w", stdout);
	int n;
	scanf("%d", &n);
	REP(i, 1, n){
		int now = i, cnt = 0;
		while(now){
			int t = now % 10;
			REP(j, 0, strlen(to[cnt][t]))
				sum[1 * to[cnt][t][j]] ++;
			cnt ++;
			now /= 10;
		}
	}
	REP(i, 0, strlen(ans) - 1)
		if(sum[1 * ans[i]]){
			putchar(ans[i]);
			printf(" %d\n", sum[1 * ans[i]]);
		}
	return 0;
}
