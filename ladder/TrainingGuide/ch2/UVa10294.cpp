// UVa10294
// Fuboat
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#define LL long long
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
const int MAXN = 50 + 10, MAXT = 10 + 10;
int n, t;
LL ksm[MAXN];
int Gcd(int a, int b)
{
	if(!a)
		std::swap(a, b);
	int r;
	while(b != 0){
		r = a % b;
		a = b;
		b = r;
	}
	return a;
}
void Solve()
{
	LL tot1(0), tot2(0);
	ksm[1] = t;
	REP(i, 2, n)
		ksm[i] = ksm[i - 1] * t;
	REP(i, 1, n)
		tot1 += ksm[Gcd(i, n)];
	if(n & 1)
		tot2 = n * ksm[(n + 1) / 2];
		// ��ת
		// nΪ����������n���Գ���
		// ÿ���Գ��᣺
		// ��������(n = 3)����ֱ�ĶԳ���Ϊ�� 
		/* _______
		  |      |
		  ->*   * <-   //������(n - 1)���ڵ㣬���һ���û�����(n - 1) / 2��ѭ�� 
		    |      |
		    |______|
			  *        //������1���ڵ㣬��1��ѭ�� 
			  		   //�ܼ�(n + 1) / 2��ѭ�� 
		*/
	else
		tot2 = n * (ksm[n / 2] + ksm[n / 2 + 1]) / 2;
	printf("%lld %lld\n", tot1 / n, (tot1 + tot2) / n / 2);
	// 'int' is not enough (...), 'long long' is needed;
}
int main()
{
	while(~scanf("%d%d", &n, &t))
		Solve();
} 
