// UVa12103
// Fuboat
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#define CLEAR(a) memset(a, 0, sizeof(a))
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define rep for(int i = 0; i < 26; i ++)
const int MAXL = 30;
char s[MAXL];
int f[MAXL], vis[MAXL], sumv[MAXL];
int tot;
void Init()
{
	REP(i, 0, 25)
		f[i] = s[i] - 'A';
}
int Find(int x)
{
	int cnt(0);
	while(vis[x] != tot){
		vis[x] = tot;
		x = f[x];
		cnt ++;
	}
	return cnt;
}
void Solve()
{
	tot = 0;
	bool flag = true;
	CLEAR(vis);
	CLEAR(sumv);
	REP(i, 0, 25)
		if(!vis[i]){
			tot ++;
			sumv[Find(i)] ++;
		}
	for(int i = 2; i < 26; i += 2)
		if(sumv[i] & 1){
			flag = false;
			break;
		}
	puts(flag? "Yes" : "No");
}
int main()
{
	int T;
	scanf("%d", &T);
	while(T --){
		scanf("%s", s);
		Init();
		Solve();
	}
}
