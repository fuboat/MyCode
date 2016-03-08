/*
	ID: 60303451
	TASK: prefix
	LANG: C++
*/
#include <cstdio>
#include <iostream>
#include <cstring>
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define Rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
using namespace std;
template<typename T> bool chkmax(T &x, T y){return y > x? x = y, true:false;}
template<typename T> bool chkmin(T &x, T y){return y < x? x = y, true:false;}
const int MAXP = 200 + 10, MAXl = 10 + 3, MAXL = 200000 + 1000;
char str[MAXP][MAXl], s[MAXL];
int lenstr[MAXP];
int cnt, len;
bool ok[MAXL];

void Init(){
	cnt = 0, len = 0;
	scanf("%s", str[++ cnt]);
	while(str[cnt][0] != '.'){
		lenstr[cnt] = strlen(str[cnt]);
		scanf("%s", str[++ cnt]);
	}
	-- cnt;
	while(scanf("%s", s + len) != EOF)
		len = strlen(s);
}

bool match(char *s, char *t, int lent)
{
	REP(i, 0, lent - 1)
		if(s[i] != t[i]) return false;
	return true;
}

void Solve()
{
	REP(i, 0, len - 1){
		if(i && !ok[i - 1]) continue;
		REP(j, 1, cnt){
			int e = i + lenstr[j] - 1;
			if(e < len && !ok[e] && match(s + i, str[j], lenstr[j]))
				ok[e] = true;
		}
	}
	Rep(i, len - 1, 0)
		if(ok[i]){
			printf("%d\n", i + 1);
			return;
		}
	printf("0\n");
}

void Begin(), End();
int main()
{
	Begin();
	Init();
	Solve();
	End();
}

void Begin()
{
	freopen("prefix.in", "r", stdin);
	freopen("prefix.out", "w", stdout);
}

void End()
{
	fclose(stdin);
	fclose(stdout);
}
