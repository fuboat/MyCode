#include <cstdio>
int gcd(int a, int b)
{
	if(!b) return a;
	while(a % b != 0){
		int r = b;
		b = a % b;
		a = r;
	}
	return b;
}
int main()
{
	int n, cnt = 0;
	scanf("%d", &n);
	for(int i = 1; i <= n; i ++)
		if(gcd(i, n) == 1) cnt ++;
	printf("%d\n", cnt);
}
