#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int n, m;
int s[1000000];
short int w[1000000][30];
bool ok[1000000];
short int deep[1000000];
void bfs()
{
	int head = 0,tail = n - 1;
	for(int i = 1; i < n; i ++)
	{
		s[i] = i;
		w[i][1] = i;//盗版高精度，w[1]表示最高位，w[deep]表示最低位。 
		deep[i] = 1;
	}
	for(;;)
	{
		head ++;
		for(int i = 0; i < n; i ++)
		if(!ok[(s[head] * 10 + i) % m])
		{
			ok[(s[head] * 10 + i) % m] = 1;
			s[++ tail] = (s[head] * 10 + i) % m; //高精度取模 
			for(int k = 1; k <= deep[head]; k ++)
				w[tail][k] = w[head][k];
			deep[tail] = deep[head] + 1;
			w[tail][deep[tail]] = i;	
			if(!s[tail])//s[tail] == 0时，整除m 
			{
				for(int j = 1;j <= deep[tail];j ++)
					printf("%d", w[tail][j]);
				return;
			}
			
		}
	}
}
int main()
{
	scanf("%d%d", &n, &m);
	bfs();
}
