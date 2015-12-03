#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define Rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
#define LL long long
template <typename T> bool chkmin(T &x, T y){return y < x? (x = y, true) : false;}
template <typename T> bool chkmax(T &x, T y){return y > x? (x = y, true) : false;}
const int MAXL = 1000 + 200;

struct node{
	int last, next;
}a[MAXL];

int main()
{
	char s[MAXL] = {0};
	while(scanf("%s", s + 1) != EOF){
		int n;
		scanf("%d", &n);
		int l = strlen(s + 1);
		REP(i, 1, l){
			a[i].last = i - 1;
			a[i].next = i + 1;
		}
		bool ok[MAXL] = {0};
		int now = 2, cnt = 0;
		for(;;){
			if(cnt == n || now == l + 1) break;
			else if(a[now].last == 0 && a[now].next == l + 1){
				ok[now] = 1;
				break;
			}
			if(s[a[now].last] > s[now]){
				ok[a[now].last] = 1;
				a[a[a[now].last].last].next = now;
				a[now].last = a[a[now].last].last;
				cnt ++;
				if(a[now].last == 0) now = a[now].next;
			}
			else now = a[now].next;
		}
		cnt = 0;
		bool first = 1;
		REP(i, 1, l)
		if(cnt == l - n) break;
		else if(!ok[i]){
			if(!first || s[i] != '0'){
				putchar(s[i]);
				first = 0;
			}
			cnt ++;
		}
		if(first) printf("0");
		putchar('\n');
	}
}
