// UVa11077
// Fuboat

// 注意这道题动态规划的思想
// Example:
// 设1 ~ 8的某个排列组成的置换为 (1, 3), (4, 5, 7), (8, 2, 6)(原始数列为 [3, 6, 1, 5, 7, 8, 4, 2]) 
// 则所需次数为 8 - 3 = 5;
// 想象有某个数加入某个循环节 
// 然后模拟每个数的加入即可 
// 注意，加入循环节的末尾是没有意义的
// 因为它与加入循环节的头部是等价的  
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
// f[i][j] 表示长度为 i, 循环节有 j 个的方案数; 
//易知: f[i][j] = f[i - 1][j - 1] + f[i - 1][j] * (i - 1);
//对于第 i 个数:[自己作为一个循环节][在 i - 1 个数组成的循环节中任意插在一个数的前面, i - 1种方式] 
// 且f[n][n - k] 为所求;
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
