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
const int MAXN = 50000 + 1000;
int n, L, R, X, a[MAXN];

int readin(){
	int x=0;bool flag=0;char c=0;
	while(c=getchar()){
		if(c=='-'){
			return -readin();
		}
		if(c>='0'&&c<='9'){
			x=x*10+c-'0';
			flag=1;
		}
		else if(flag)return x;
	}
}

int sumv[MAXN * 2];
inline void build(int o, int l, int r)
{
	if(l == r) sumv[o] = a[l];
	else{
		int mid = (l + r) >> 1;
		build(o << 1, l, mid);
		build(o << 1|1, mid + 1, r);
		sumv[o] = sumv[o << 1] + sumv[o << 1|1];
	}
}
inline void update(int o, int l, int r)
{
	if(l == r) sumv[o] += X;
	else{
		int mid = (l + r) >> 1;
		if(L <= mid) update(o << 1, l, mid);
		else update(o << 1|1, mid + 1, r);
		sumv[o] += X;
	}
}

inline int query(int o, int l, int r)
{
	if(L <= l && r <= R)
		return sumv[o];
	else{
		int mid = (l + r) >> 1, sum(0);
		if(L <= mid) sum += query(o << 1, l, mid);
		if(mid < R) sum += query(o << 1|1, mid + 1, r);
		return sum;
	}
}

int main()
{
	int T;
	char c[100];
	T = readin();
	REP(z, 1, T){
		printf("Case %d:\n", z);
		n = readin();
		REP(i, 1, n)  scanf("%d", &a[i]);
		build(1, 1, n);
		while(scanf("%s", c) && c[0] != 'E'){
			if(c[0] == 'Q'){
				L = readin();
				R = readin();
				printf("%d\n", query(1, 1, n));
			}
			else{
				L = readin();
				X = readin();
				X = c[0] == 'A'? X : -X;
				update(1, 1, n);
			}
		}
	}
}
