#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

#define MSET(a, x) memset(a, x, sizeof(a))
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define Rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
#define LL long long
template <typename T> bool chkmin(T &x, T y){return y < x? (x = y, true) : false;}
template <typename T> bool chkmax(T &x, T y){return y > x? (x = y, true) : false;}
const int MAXL = 1000000 + 10000;
char s[MAXL];
int f[MAXL];
int len;
void getFail()
{
	f[0] = f[1] = 0;
	REP(i, 1, len - 1){
		int j = f[i];
		while(j && s[i] != s[j]) j = f[j];
		f[i + 1] = (s[i] == s[j]? j + 1 : 0);
	}
}
int main()
{
	while(scanf("%s", s) && s[0] != '.'){
		len = strlen(s);
		int ans = 0;
		getFail();
		if(len % (len - f[len]) == 0)
			printf("%d\n", len / (len - f[len]));
		else printf("1\n");
	}
	return 0;
}
