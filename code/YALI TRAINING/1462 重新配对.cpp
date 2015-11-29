/*
	ID: fuboat
	FROM: YALI TRAINING
	PLACE: YALI
	TASK: 1462
*/
/*
	算法：二分
	数据结构：普通数组
*/
#include <cstdio>
#include <algorithm>
const int MAXA = 100, MAXN = 100000;
int n, girl[MAXN + 10], boy[MAXN + 10];
int main()
{
	scanf("%d", &n);
	REP(i, 1, n)
		scanf("%d%d", &
