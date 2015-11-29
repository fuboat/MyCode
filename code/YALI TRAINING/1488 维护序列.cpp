/*
	name:fuboat
	date:2015.11.22
	task:1488
	place:Yali, Changsha
*/

/*
	mistake:
	1.  Scanf(int) without '&'.
	2.  Code is not sample enough; some code is useless or able to be simplify.
	3.  Too many "%d" to scanf(int) correctly.
	4.  Use Wrong function(update) in a function(qurey).
	5.  Wrong formula: When flag = 0, not "addv = addv + X * (r - l + 1)", but "addv += X".
	6.  When adding, we should update the mark of sqr;  when sqring, we should update the mark of add and sqring.
	7.  When qureying, ans += addv * (r - l + 1) * sqr, don't forget the "* sqr"!(this costs me 2 hours!)
*/
#ifdef WIN32
	#define ll "%I64d"
#else
	#define ll "%lld"
#endif
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using std::min;
using std::max;

#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define Rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
#define LL long long
#define LD long double
#define pii pair<int, int>
#define TT LL

TT readin(){
	TT x=0;bool flag=0;char c=0;
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

template <typename T> bool chkmin(T &x, T y){return y < x? (x = y, true) : false;}
template <typename T> bool chkmax(T &x, T y){return y > x? (x = y, true) : false;}
const int MAXN = 100000, MAXM = 100000, MAXA = 1000000000, oo = 0x7fffffff;
bool flag;
TT a[MAXN + 100], sumv[MAXN * 3], addv[MAXN * 3], sqrv[MAXN * 3];
TT X, P, ans, sqr, add;
int L, R;
void maintain(int o, int l, int r)
{
	if(l == r) sumv[o] = a[l];
	else  sumv[o] = sumv[o << 1] + sumv[o << 1|1];
	sumv[o] = 1LL * sqrv[o] * sumv[o] % P + addv[o] * (r - l + 1) % P;
	//printf("maintain(%d, %d, %d) addv = %d, sqrv = %d, sumv = %d;\n", o, l, r, addv[o], sqrv[o], sumv[o]);
}

void ycl(int o, int l, int r)
{
	sqrv[o] = 1;
	int mid = (l + r) >> 1;
	if(l == r) sumv[o] = a[l];
	else{
		ycl(o << 1, l, mid);
		ycl(o << 1 | 1, mid + 1, r);
	}
	maintain(o, l, r);
	return ;
}

void super(int o, int l, int r)
{
	sqrv[o] = 1LL * sqrv[o] * sqr % P;
	if(!sqrv[o]) sqrv[o] = P;
	addv[o] = 1LL * addv[o] * sqr % P;
	addv[o] += add;
	//printf("super(%d, %d, %d) addv = %d, sqrv = %d, sumv = %d;\n", o, l, r, addv[o], sqrv[o], sumv[o]);
}

void update(int o, int l, int r)
{
	int mid = (l + r) >> 1;
	if(L <= l && r <= R){
		TT &ADD = addv[o], &SQR = sqrv[o];
		if(flag){
			ADD = 1LL * ADD * X % P;
			SQR = 1LL * SQR * X % P;
			if(!SQR) SQR = P;
		}
		else  ADD = (ADD % P + 1LL * X % P) % P;
	}else if(L <= mid || mid < R){
		TT tmps = sqr, tmpa = add;
		sqr = sqr * sqrv[o] % P;
		if(!sqrv[o]) sqrv[o] = P;
		add += addv[o];
		super(o << 1, l, mid);
		super(o << 1|1, mid + 1, r);
		sqr = tmps;
		add = tmpa;
		sqrv[o] = 1;
		addv[o] = 0;
		if(L <= mid) update(o << 1, l, mid);
		else maintain(o << 1, l, mid);
		if(mid < R) update(o << 1|1, mid + 1, r);
		else maintain(o << 1|1, mid + 1, r);
	}
	maintain(o, l, r);
	return ;
}

void query(int o, int l, int r)
{
	if(L <= l && r <= R)
		ans = (ans + 1LL * sqr * sumv[o] % P) % P;
	else{
		int mid = (l + r) >> 1;
		ans += (min(r, R) - max(L, l) + 1) * addv[o] % P * sqr;
		TT tmp = sqr;
		sqr = 1LL * sqr * sqrv[o] % P;
		if(L <= mid) query(o << 1, l, mid);
		if(mid < R) query(o << 1|1, mid + 1, r);
		sqr = tmp;
	}
	return ;
}

int main()
{
	//freopen("in.cpp", "r", stdin);
	//freopen("out.cpp", "w", stdout);
	
	int n, m, x;
	n = readin(), P = readin();
	//P = oo;
	REP(i, 1, n)  a[i] = readin();
	ycl(1, 1, n);
	m = readin();
	REP(i, 1, m){
		x = readin();
		L = readin();
		R = readin();
		if(x == 3){
			ans = 0;  sqr = 1;
			query(1, 1, n);
			printf(ll"\n", ans);
		}else{
			X = readin();
			flag = !(x - 1);
			sqr = 1;
			//putchar('\n');
			//printf("now, flag = %d, L = %d, R = %d, X = %d;\n", flag, L, R, X);
			//putchar('\n');
			update(1, 1, n);
		}
	}
	return 0;
}
