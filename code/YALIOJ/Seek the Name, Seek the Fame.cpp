#ifdef WIN32
	#define ll "%I64d"
#else
	#define ll "%lld"
#endif
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
const int MAXL = 400000 + 10000;
char s[MAXL];
int f[MAXL], ans[MAXL], len;
void getFail()
{
	f[0] = f[1] = 0;
	REP(i, 1, len - 1){
		int j = f[i];
		while(j && s[i] != s[j]) j = f[j];
		f[i + 1] = s[i] == s[j]? j + 1 : 0;
	}
}
int main()
{
	while(scanf("%s", s) != EOF){
		len = strlen(s);
		getFail();
		int i = len, cnt = 0;
		while(f[i]){
			ans[++ cnt] = f[i];
			i = f[i];
		}
		Rep(i, cnt, 1) printf("%d ", ans[i]);
		printf("%d\n", len);
	}
}
