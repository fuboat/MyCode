/*
	FROM: NOIP 2000
	ID: fuboat
	ALGORITHM: default
	DATA STRUCTURE: default
*/
#include <cstdio>
#define Rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
char c[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};
int main()
{
	int n, m;
	while(scanf("%d%d", &n, &m) == 2){
		printf("%d=", n);
		int tmp[50] = {0};
		int cnt = 1;
		while(n){
			int &now = tmp[cnt];
			now = n % m;
			n /= m;
			while(now < 0){
				now -= m;
				n ++;
			}
			cnt ++;
		}
		Rep(i, cnt - 1, 1)
			putchar(c[tmp[i]]);
		printf("(base%d)\n", m);
	}
}
