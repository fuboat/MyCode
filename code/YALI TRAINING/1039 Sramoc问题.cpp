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
		w[i][1] = i;//����߾��ȣ�w[1]��ʾ���λ��w[deep]��ʾ���λ�� 
		deep[i] = 1;
	}
	for(;;)
	{
		head ++;
		for(int i = 0; i < n; i ++)
		if(!ok[(s[head] * 10 + i) % m])
		{
			ok[(s[head] * 10 + i) % m] = 1;
			s[++ tail] = (s[head] * 10 + i) % m; //�߾���ȡģ 
			for(int k = 1; k <= deep[head]; k ++)
				w[tail][k] = w[head][k];
			deep[tail] = deep[head] + 1;
			w[tail][deep[tail]] = i;	
			if(!s[tail])//s[tail] == 0ʱ������m 
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
