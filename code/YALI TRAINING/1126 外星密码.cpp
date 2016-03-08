// YALITRAINGING1126
// Fuboat
#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
const int MAXN = 30000;
bool Number(char c){ return '0' <= c && c <= '9'; }
char ans[MAXN], s[MAXN];
int len;
int Update(int p, int &L)
{
	int t = 1, from = L + 1, to;
	if(Number(s[p])){
		t = s[p] - '0';
		p ++;
		if(Number(s[p])){
			(t *= 10) += s[p] - '0';
			p ++;
		}
	}
	do{
		if(s[p] == '[')
			p = Update(p + 1, L);
		else ans[++ L] = s[p];
	}while(s[++ p] != ']');
	to = L;
	REP(i, 1, t - 1)
		REP(j, from, to)
			ans[++ L] = ans[j];
	return p;
}
int main()
{
	int L = -1;
	scanf("%s", s + 1);
	s[0] = '[';
	len = strlen(s);
	s[len ++] = ']';
	Update(1, L);
	printf("%s", ans);
}
