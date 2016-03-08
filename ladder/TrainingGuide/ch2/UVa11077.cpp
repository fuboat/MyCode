// UVa11077
// Fuboat

// ע������⶯̬�滮��˼��
// Example:
// ��1 ~ 8��ĳ��������ɵ��û�Ϊ (1, 3), (4, 5, 7), (8, 2, 6)(ԭʼ����Ϊ [3, 6, 1, 5, 7, 8, 4, 2]) 
// ���������Ϊ 8 - 3 = 5;
// ������ĳ��������ĳ��ѭ���� 
// Ȼ��ģ��ÿ�����ļ��뼴�� 
// ע�⣬����ѭ���ڵ�ĩβ��û�������
// ��Ϊ�������ѭ���ڵ�ͷ���ǵȼ۵�  
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#define LL unsigned long long
#define CLEAR(a) memset(a, 0, sizeof(a)) 
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
const int MAXN = 21 + 10;
LL f[MAXN][MAXN];
/*Dynamic programming--------------------------------------*/
// f[i][j] ��ʾ����Ϊ i, ѭ������ j ���ķ�����; 
//��֪: f[i][j] = f[i - 1][j - 1] + f[i - 1][j] * (i - 1);
//���ڵ� i ����:[�Լ���Ϊһ��ѭ����][�� i - 1 ������ɵ�ѭ�������������һ������ǰ��, i - 1�ַ�ʽ] 
// ��f[n][n - k] Ϊ����;
void Init(int N)
{
	f[1][1] = 1; 
	REP(i, 2, N)
		REP(j, 1, i)
			f[i][j] = f[i - 1][j - 1] + f[i - 1][j] * (i - 1);
}
int main()
{
	int n, k; 
	Init(21);
	while(scanf("%d%d", &n, &k)){
		if(!n && !k)
			break;
		std::cout << f[n][n - k] << '\n'; 
	}
}
