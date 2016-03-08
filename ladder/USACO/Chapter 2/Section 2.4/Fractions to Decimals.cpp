/*
	FROM: USACO
	TASK: fracdec
	ID: fuboat
	LANG: C++
	MISTAKE:
	EXPERIENCE:
*/
#include <cstdio>
#include <iostream>
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
bool s[1000000];
int ans[100000], sum;
int d[100000];
//When dividing, the remainder is a number in 0~9(if the remainder is 0, there is exact remainder);
inline void hh()
{
	(sum += 1) %= 76;
	if(!sum) puts("");
}
int main()
{
	freopen("fracdec.in", "r", stdin);
	freopen("fracdec.out", "w", stdout);
	int x, y;
	int cnt = 0;
	scanf("%d%d", &x, &y);
	ans[0] = x / y;
	x %= y;
	x *= 10;
	int now = x / y;
	while(x && !s[x]){
		cnt ++;
		s[x] = 1;
		ans[cnt] = now;
		d[cnt] = x;
		x %= y;
		x *= 10;
		now = x / y;
	}
	printf("%d", ans[0]);
	do{
		hh();
		ans[0] /= 10;
	}while(ans[0]);
	putchar('.'), hh();
	if(cnt){
		if(x){
			int tmp;
			REP(i, 1, cnt) if(ans[i] == now && d[i] == x){tmp = i - 1; break;}
			REP(i, 1, tmp)
				printf("%d", ans[i]), hh();
			putchar('('), hh();
			REP(i, tmp + 1, cnt)
				printf("%d", ans[i]), hh();
			putchar(')'), hh();
		}
		else REP(i, 1, cnt) printf("%d", ans[i]), hh();
	}else putchar('0'), hh();
	if(sum)puts("");
}

