/*
	ID: 60303451
	TASK: concom
	LANG: C++11
*/
#include <cstdio>
long long s[111][111];
bool ok[111][111];
int main()
{
	freopen("concom.in", "r", stdin);
	freopen("concom.out", "w", stdout);
	int n, l, r, x;
	scanf("%d", &n);
	for(int i = 1; i <= n; i ++){
		scanf("%d%d%d", &l, &r, &x);
		s[l][r] += x;
	}
	for(int i = 1; i <= 100; i ++)
	{
		bool flag;
		do{
			flag = 0;
			for(int j = 1; j <= 100; j ++)
				if(i != j && !ok[i][j] && s[i][j] > 50){
					flag = 1;
					ok[i][j] = 1;
					for(int k = 1; k <= 100; k ++){
						s[i][k] += s[j][k];
						if(s[i][k] > 100) s[i][k] = 100; //This is important!
					}
				}
		}while(flag);
	}
	for(int i = 1; i <= 100; i ++)
		for(int j = 1; j <= 100; j ++)
			if(i != j && ok[i][j])
				printf("%d %d\n", i, j);
}
