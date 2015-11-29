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
#include <vector>
#include <map>
#include <set>
#include <queue>
using namespace std;
const int MAXM = 100000;
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define Rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
#define LL long long
#define LD long double
#define pii pair<int, int>
template <typename T> bool chkmin(T &x, T y){return y < x? x = y , true : false;}
template <typename T> bool chkmax(T &x, T y){return y > x? x = y , true : false;}
int f[MAXM + 100];

int main(){
	memset(f, 0x7f, sizeof(f));
	int m;
	scanf("%d", &m);
	f[0] = 0;
	REP(i, 1, m)
		REP(j, 1, m){
			int tmp;
			if((tmp = j * j * j * j) > i) break;
			chkmin(f[i], f[i - tmp] + 1);
		}
	printf("%d\n", f[m]);
}
