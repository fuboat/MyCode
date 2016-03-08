/*
	FROM: UvaLive
	PRO: 3983
	ID: fuboat
	ALGORITHM: Dynamic Programming
	DATA STRUCTURE: The monotonous queue
	MISTAKE:
	1. line(57) Too few "%d";
	2. line(71) For prority_queue,there is only 'push',not 'push_back';
	3. line(48) For a monotonous queue, when you push a element, it should be 's[++ tail] = x', not 's[tail ++] = x';
*/
#include <iostream>
#include <cstdio>
#include <queue>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define Rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
#define LL long long
template <typename T> bool chkmin(T &x, T y){return y < x? (x = y, true) : false;}
template <typename T> bool chkmax(T &x, T y){return y > x? (x = y, true) : false;}
const int MAXC = 100, MAXN = 100000;
int Far[MAXN + 10], dis[MAXN + 10] , s[MAXN + 10], sum[MAXN + 10], C, n;
struct node{
	int x, y;
}a[MAXN + 10];

struct sta{
	int w, num;
	sta(){}
	sta(int w, int num):
		w(w), num(num){}
	bool operator < (const sta &a) const{
		if(a.w != w) return w > a.w;
		return num > a.num;
	}
};

struct mono_queue{
	sta s[MAXN + 10];
	int head, tail;
	mono_queue(int head = 0, int tail = 1): head(head), tail(tail){}
	void init(){head = 0, tail = 1;}
	void push(sta x){
		while(head <= tail && s[tail].w >= x.w) tail --;
		s[++ tail] = x;
	}
	sta top(){return s[head];}
	void pop(){head ++;}
}d;

void init()
{
	int w;
	scanf("%d%d", &C, &n);
		REP(i, 1, n){
			scanf("%d%d%d",  &a[i].x, &a[i].y, &w);
			dis[i] = dis[i - 1] + abs(a[i].x - a[i - 1].x) + abs(a[i].y - a[i - 1].y);
			sum[i] = sum[i - 1] + w;
			Far[i] = abs(a[i].x) + abs(a[i].y);
		}
}

int solve()
{
	int now;
	d.init();
	//priority_queue<sta>d;
	d.push(sta(0, 0));
	REP(i, 1, n){
		while(sum[i] - sum[d.top().num] > C) d.pop();
		now = d.top().w + dis[i] + Far[i];
		d.push(sta(now - dis[i + 1] + Far[i + 1], i));
	}
	return now;
}

int main()
{
	int T;
	scanf("%d", &T);
	while(T --){
		init();
		printf("%d\n", solve());
		if(T) putchar('\n');
	}
	return 0;
}
