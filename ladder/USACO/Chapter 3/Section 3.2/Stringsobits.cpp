/*
	ID: fuboat
	TASK: kimbits
	LANG: C++
*/
#include <cstdio>
#include <iostream>
using std::cin;
#define int unsigned int
int f[50][50];
main()
{
	freopen("kimbits.in", "r", stdin);
	freopen("kimbits.out", "w", stdout);
	for(int i = 0; i <= 33; i ++) f[i][0] = f[0][i] = 1;
	for(int i = 1; i <= 33; i ++){
		for(int j = 1; j <= i; j ++)
		f[i][j] = f[i - 1][j] + f[i - 1][j - 1];
		for(int j = i + 1; j <= 32; j ++)
		f[i][j] = f[i][i];
	}
	int n, l, k;
	scanf("%u%u%u", &n, &l, &k);
	for(int i = n; i > 0; i --){
		if(f[i - 1][l] < k){
			k -= f[i - 1][l];
			l --;
			putchar('1');
		}else putchar('0');
	}
	puts("");
}
