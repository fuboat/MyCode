/*
	ID: 60303451
	TASK: zerosum
	LANG: C++
*/
#include <cstdio>
int n, ans;
int sta[100];

void print()
{
	putchar('1');
	for(int i = 2; i <= n; i ++){
		char c;
		switch(sta[i]){
			case 1: c = '+';break;
			case -1: c = '-';break;
			case 0: c = ' ';break;
		}
		putchar(c);
		putchar(i + '0');
	}
	putchar('\n');
}

void dfs(int x, int now, int sum)
{
	if(x > n && sum + now == 0){
		ans ++;
		print();
	}
	else if(x <= n){
		sta[x] = 0;
		dfs(x + 1, now * 10 + (now < 0 ? (-x): x), sum);
		sta[x] = 1;
		dfs(x + 1, x, sum + now);
		sta[x] = -1;
		dfs(x + 1, -x, sum + now);
	}
}

int main()
{
	freopen("zerosum.in", "r", stdin);
	freopen("zerosum.out", "w", stdout);
	scanf("%d", &n);
	sta[1] = 1;
	dfs(2, 1, 0);
}
