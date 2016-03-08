//PROB: LA4413
//ID: Fuboat
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <map>
using namespace std;
#define LL unsigned long long
#define CLEAR(a) memset(a, 0, sizeof(a))
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
const int MAXL = 40000 + 10000, MAXS = 27;
int m, len;
const int T = 123;
LL H[MAXL], X[MAXL];
inline LL HASH(int pos, int L){ return H[pos] - H[pos + L] * X[L]; }
int cnt[MAXL];
struct sta{
	LL hash;
	int pos;
}a[MAXL];
bool cmp(sta a, sta b)
{
	if(a.hash != b.hash) return a.hash < b.hash;
	return a.pos < b.pos;
}
int Check(int L)
{
	int ans = -1, maxx = 0;
	REP(i, 0, len - L) a[i].hash = HASH(i, L), a[i].pos = i;
	sort(a, a + len - L + 1, cmp);
	int head = 0, tail = len - L;
	REP(i, 0, tail - 1)
		if(a[i].hash != a[i + 1].hash){
			if(i - head + 1 >= m && ans < a[i].pos)
				ans = a[i].pos;
			head = i + 1;
		}
	if(tail - head + 1 >= m && ans < a[tail].pos)
		ans = a[tail].pos;
	return ans;
}
char s[MAXL];
int main()
{
	X[0] = 1;
	REP(i, 1, MAXL - 1){
		X[i] = X[i - 1] * T;
	}
	while(~scanf("%d", &m) && m){
		len = 0;
		bool flag = 0;
		char c;
		while(c = getchar()){
			if('a' <= c && c <= 'z'){ s[len ++] = c; flag = 1; }
			else if(flag) break;
		}
		s[len] = H[len] = 0;
		rep(i, len - 1, 0) H[i] = H[i + 1] * T + s[i] - 'a';
		int l = 0, r = len + 1;
		int ans = -1, maxx = 0;
		while(l + 1 < r){
			int mid = (l + r) >> 1, tmp;
			if((tmp = Check(mid)) != -1){
				l = mid;
				ans = tmp;
			}
			else r = mid;
		}
		if(l != 0) printf("%d %d\n", l, ans);
		else puts("none");
	}
}
