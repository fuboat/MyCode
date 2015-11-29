#ifdef WIN32
	#define ll "%I64d"
#else
	#define ll "%lld"
#endif

#include <iostream>
#include <cstdio>
#include <map>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define Rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
#define LL long long
#define LD long double
#define pii pair<int, int>
template <typename T> bool chkmin(T &x, T y){return y < x? (x = y, true) : false;}
template <typename T> bool chkmax(T &x, T y){return y > x? (x = y, true) : false;}

const int MAXN = 100, MAXK = 100;

int sol[MAXK + 100];
int a[MAXN + 10], tmp[MAXN + 10], the[MAXN + 10], ans[MAXN + 10], k;
int xx[MAXN + 10];

int main()
{
	char c;
	int cnt = 0;
	c = getchar();
	while(c != ' '){
		cnt ++;
		a[cnt] = c - '0';
		c = getchar();
	}
	scanf("%d", &k);
	REP(i, 1, cnt >> 1) swap(a[i], a[cnt - i + 1]);
	tmp[1] = the[1] = a[1];
	REP(i, 1, k) xx[i] = a[i];
	REP(i, 1, k){
		int j;
		for(j = 1; j <= 10; j ++){
			int now[MAXN + 100] = {0};
			REP(w, 1, i) REP(c, 1, i)
				if(w + c - 1 > i) break;
				else now[w + c - 1] += tmp[w] * the[c];
			REP(w, 1, i - 1) now[w + 1] += now[w] / 10, now[w] %= 10;
			now[i] %= 10; 
			if(now[i] == a[i]){
				REP(w, 1, k) the[w] = xx[w];
				REP(z, 1, j - 1){
					int now[MAXN + 100] = {0};
					REP(w, 1, k)  REP(c, 1, k)
					if(w + c - 1 > k) break;
					else now[w + c - 1] += xx[w] * the[c];
					REP(w, 1, k - 1) now[w + 1] += now[w] / 10, now[w] %= 10;
					now[k] %= 10;
					REP(w, 1, k) xx[w] = now[w];
				}
				REP(w, 1, i + 1)  the[w] = xx[w];
				REP(w, 1, i + 1)  tmp[w] = a[w];
				sol[i] = j;
				break;
			}
			REP(w, 1, i) tmp[w] = now[w];
		}
		if(j == 11){
			printf("-1\n");
			system("pause");
			return 0;
		}
	}
	ans[1] = 1; int len = 1;
	REP(j, 1, k){
		REP(i, 1, len)	
			ans[i] *= sol[j];
		REP(i, 1, len){
			ans[i + 1] += ans[i] / 10;
			ans[i] %= 10;
		}
		if(ans[len + 1]) len ++;
	}
	Rep(i, len, 1) printf("%d", ans[i]);
	putchar('\n');
	system("pause");
	return 0;
}
