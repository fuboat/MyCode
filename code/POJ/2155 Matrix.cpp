#include <cstdio>
#include <cstring>
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
const int MAXN = 1000;
bool a[MAXN * 2 + 100][MAXN * 2 + 100];
int XL, YL, XR, YR, X, Y, now, n, ans;

void udy(int o, int l, int r)
{
	if(YL <= l && r <= YR)
		a[now][o] ^= 1;
	else{
		int mid = (l + r) >> 1;
		if(YL <= mid) udy(o << 1, l, mid);
		if(mid < YR) udy(o << 1|1, mid + 1, r);
	}
}

void udx(int o, int l, int r)
{
	if(XL <= l && r <= XR){
		now = o;
		udy(1, 1, n);
	}
	else{
		int mid = (l + r) >> 1;
		if(XL <= mid) udx(o << 1, l, mid);
		if(mid < XR) udx(o << 1|1, mid + 1, r);
	}
}

void qdy(int o, int l, int r)
{
	ans ^= a[now][o];
	if(l != r){
		int mid = (l + r) >> 1;
		if(Y <= mid) qdy(o << 1, l, mid);
		else qdy(o << 1|1, mid + 1, r);
	}
}

void qdx(int o, int l, int r)
{
	now = o;
	qdy(1, 1, n);
	if(l != r){
		int mid = (l + r) >> 1;
		if(X <= mid) qdx(o << 1, l, mid);
		else qdx(o << 1|1, mid + 1, r);
	}
}

int main()
{
	int T, s;
	scanf("%d", &T);
	while(T --){
		memset(a, 0, sizeof(a));
		scanf("%d%d", &n, &s);
		REP(i, 1, s){
			char c = getchar();
			while(c == ' ' || c == '\n') c = getchar();
			if(c == 'C'){
				scanf("%d%d%d%d", &XL, &YL, &XR, &YR);
				udx(1, 1, n);
			}else{
				scanf("%d%d", &X, &Y);
				ans = 0;
				qdx(1, 1, n);
				printf("%d\n", ans);
			}
		}
		if(T)putchar('\n');
	}
	return 0;
}
