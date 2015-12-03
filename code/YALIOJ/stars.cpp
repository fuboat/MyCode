#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;
const int MAXN = 15000 + 100, MAXX = 32000 + 1000;
int n, ans[MAXN], s[MAXN], cnt;

#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
int chkmax(int &x, int y){return y > x? x = y, true:false;}
int a[MAXX], otn[MAXX];
bool ok[MAXX];

int readin(){
	int x=0;bool flag=0;char c=0;
	while(c=getchar()){
		if(c=='-')
			return -readin();
		else if(c>='0'&&c<='9'){
			x=x*10+c-'0';
			flag=1;
		}
		else if(flag)return x;
	}
	return 0;
}

inline void add(int pos)
{
	while(pos <= cnt){
		s[pos] ++;
		pos += pos & -pos;
	}
	return ;
}
	
inline int sum(int pos)
{
	int sum = 0;
	while(pos > 0){
		sum += s[pos];
		pos -= pos & -pos;
	}
	return sum;
}

int main()
{
	int x, y, maxx = 0;
	while(scanf("%d", &n) != EOF){
		memset(s, 0, sizeof(s));
		memset(ok, 0, sizeof(ok));
		memset(ans, 0, sizeof(ans));
		cnt = 0;
		REP(i, 1, n){
			x = readin(); y = readin();
			ok[x] = 1;
			chkmax(maxx, a[i] = x);
		}
		REP(i, 0, maxx)
			if(ok[i]) otn[i] = ++cnt;
		REP(i, 1, n){
			int pos = otn[a[i]];
			ans[sum(pos)] ++;
			add(pos);
		}
		REP(i, 0, n - 1)
			printf("%d\n", ans[i]);
	}
	return 0;
}
