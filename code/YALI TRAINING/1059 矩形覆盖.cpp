/*
	FROM: YALI TRAINING
	TASK: 1059
	DATE: 11.25
	ID: fuboat
	ALGORITHM: depth-first search
	MISTAKES:
	1. (On line 38) 'REP(i, 1, n)' is true, not 'REP(i, 1, k)';
*/
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
inline bool chkmin(int &x, int y){return y < x? (x = y, true) : false;}
inline bool chkmax(int &x, int y){return y > x? (x = y, true) : false;}
using namespace std;
const int MAXN = 50, MAXK = 4, MAXX = 500, MAXY = 500, oo = 0x7fffffff;
bool ok[MAXY + 10];
int num[MAXN + 10], ans = oo, n, k;
struct node{
	int x, y;
	bool operator < (const node &a) const{
		if(y != a.y) return y < a.y;
		return x < a.x;
	}
}s[MAXN + 10];

void update()
{
	int maxx[MAXK + 2] = {0}, minx[MAXK + 2], maxy[MAXK + 2] = {0}, miny[MAXK + 2], sum = 0;
	bool ok[MAXK + 2] = {0};
	REP(i, 1, k) minx[i] = miny[i] = oo;
	REP(i, 1, n){
		ok[num[i]] = 1;
		chkmax(maxx[num[i]], s[i].x);
		chkmax(maxy[num[i]], s[i].y);
		chkmin(minx[num[i]], s[i].x);
		chkmin(miny[num[i]], s[i].y);
	}
	REP(i, 1, k) if(ok[i])
		sum += (maxx[i] - minx[i]) * (maxy[i] - miny[i]);
	chkmin(ans, sum);
}

void dfs(int has)
{
	if(has == k){
		update();
		return ;
	}
	REP(i, 1, n){
		int tmp[MAXN + 10] = {0}, cnt = 0, now = num[i];
		REP(j, 1, n)
			if(num[j] == now && s[j].x < s[i].x){
				num[j] ++;
				tmp[++ cnt] = j;
			}
		dfs(has + 1);
		REP(j, 1, cnt) num[tmp[j]] = now;
		cnt = 0;
		REP(j, 1, n)
			if(num[j] == now && s[j].y < s[i].y){
				num[j] ++;
				tmp[++ cnt] = j;
			}
		dfs(has + 1);
		REP(j, 1, cnt) num[tmp[j]] = now;
	}
}

int main()
{
	int maxx = 0, maxy = 0, minx = oo, miny = oo;
	scanf("%d%d", &n, &k);
	REP(i, 1, n){
		scanf("%d%d", &s[i].x, &s[i].y);
		chkmax(maxx, s[i].x); chkmax(maxy, s[i].y);
		chkmin(minx, s[i].x); chkmin(miny, s[i].y);
		num[i] = 1;
	}
	//sort(s + 1, s + n + 1);	// Will be faster when calculate?
	dfs(1);
	printf("%d\n", ans);
	return 0;
}
