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

#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define Rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
#define LL long long

template <typename T> bool chkmin(T &x, T y){return y < x? (x = y, true) : false;}
template <typename T> bool chkmax(T &x, T y){return y > x? (x = y, true) : false;}
const int MAXL = 1000000 + 1000;
char P[MAXL], T[MAXL];
int m, n, f[MAXL];
void getFail()
{
	f[0] = 0; f[1] = 0;
	REP(i, 1, m){
		int j = f[i];
		while(j && P[i] != P[j]) j = f[j];
		f[i + 1] = P[i] == P[j]? j + 1 : 0;
	}
}

void find()
{
	int j = 0, cnt = 0;
	REP(i, 0, n - 1){
		while(j && P[j] != T[i]) j = f[j];
		if(P[j] == T[i]) j ++;
		if(j == m) cnt ++, j = f[j];
	}
	printf("%d\n", cnt);
}

int main()
{
	int t;
	scanf("%d", &t);
	while(t --){
		scanf("%s%s", P, T);
		m = strlen(P);
		n = strlen(T);
		getFail();
		find();
	}
}
