/*
	ID: fuboat
	TASK: fact4
	LANG: C++
*/
#include <cstdio>
int main()
{
	freopen("fact4.in", "r", stdin);
	freopen("fact4.out", "w", stdout);
	int n, ans = 1, cnt = 0;
	scanf("%d", &n);
	for(int i = 1; i * 5 <= n; i ++){
		int x = i * 5;
		do{
			cnt ++;
			x /= 5;
		}while(x % 5 == 0);
	}
	for(int i = 1; i <= n; i ++){
		int x = i;
		while(cnt && x % 2 == 0){
			x /= 2;
			cnt --;
		}
		while(x % 5 == 0) x /= 5;
		(ans *= x) %= 10;
	}
	printf("%d\n", ans);
}
