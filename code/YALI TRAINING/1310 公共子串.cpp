#include <cstdio>
#include <iostream>
using std::max;
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
const int MAXL = 4000;
int ans = 0;
char a[MAXL + 1], b[MAXL + 1];
int f[MAXL + 1][MAXL + 1];
int main()
{
	a[0] = b[0] = ' ';
	scanf("%s%s", a + 1, b + 1);
	int lena = strlen(a), lenb = strlen(b);
	REP(i, 1, lena - 1)
		REP(j, 1, lenb - 1)
			if(a[i] == b[j]){
				f[i][j] = f[i - 1][j - 1] + 1;
				ans = max(ans, f[i][j]);
			}
	printf("%d\n", ans);
	system("pause");
	return 0;
}		
