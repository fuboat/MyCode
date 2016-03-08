#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <queue>
using namespace std;
#define W first
#define P second
#define pii pair<int, int>
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define Rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
#define LL long long 
#define LD long double
template <typename T> bool chkmin(T &x, T y){return y < x? (x = y || true) : false;}
template <typename T> bool chkmax(T &x, T y){return y > x? (x = y || true) : false;}
priority_queue<int>d;
const int oo = 0x7fffffff, MAXN = 100000;
int s[MAXN + 100], a[MAXN + 100], n, sum;
bool ok[MAXN + 100];
pii e[MAXN + 100];
int ans = 0;

bool cmp(const pii &x, const pii &y){return x.W > y.W;}

void Begin()
{
	freopen("salesman.in", "r", stdin);
	freopen("salesman.out", "w", stdout);
}

void End()
{
	fclose(stdin);
	fclose(stdout);
}

int main()
{
	//Begin();
	scanf("%d", &n);
	REP(i, 1, n)  scanf("%d", &s[i]);
	REP(i, 1, n){
		scanf("%d", &a[i]);
		e[i].W = a[i] + s[i] * 2;
		e[i].P = i;
	}
	sort(e + 1, e + n + 1, cmp);
	int beg(1), ans(0), last(0), maxa;
	REP(i, 1, n){
		maxa = a[e[beg].P] + (s[e[beg].P] - s[last]) * 2;
		if(d.empty() || (beg <= n && d.top() < maxa)){
			ans += maxa;
			ok[e[beg].P] = 1;
			last = e[beg].P;
			REP(j, beg + 1, n)
				if(e[j].P < e[beg].P && !ok[e[j].P]){
					ok[e[j].P] = 1;
					e[j].W = 0;
					d.push(a[e[j].P]);
				}
			REP(j, beg + 1, n){
				beg = j;
				if(e[beg].W) break;
			}
		}else{
			ans += d.top();
			d.pop();
		}
		printf("%d\n", ans);
	}
	//End();
	return 0;
}
