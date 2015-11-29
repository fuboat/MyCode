/*
	ID: 60303451
	TASK: runround
	LANG: C++
*/
#define INT unsigned int
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

bool ok(INT n)
{
	int sta = 0, now = 0;
	char num[20] = {0};
	bool cnt[10] = {0};
	sprintf(num, "%d", n);
	int len = strlen(num);
	REP(i, 0, len - 1)
		if(cnt[num[i] - '0']) return 0;
		else cnt[num[i] - '0'] = 1;
	while(!(sta & (1 << now))){
		sta |= 1 << now;
		now += num[now] - '0';
		now %= len;
	}
	if(sta != (1 << len) - 1 || now != 0) return false;
	return true;
}

int main()
{
	freopen("runround.in", "r", stdin);
	freopen("runround.out", "w", stdout);
	INT n;
	scanf("%d", &n);
	while(!ok(++ n));
	printf("%d\n", n);
}
