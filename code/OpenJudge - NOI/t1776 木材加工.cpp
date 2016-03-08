#include <cstdio>
const int MAXN = 10000 + 100;
int n, k, l[MAXN];
void Init()
{
	scanf("%d%d", &n, &k);
	for(int i = 1; i <= n; i ++)
		scanf("%d", &l[i]);
}
bool Check(int M)
{
	int cnt = 0;
	for(int i = 1; i <= n; i ++)
		if((cnt += l[i] / M) >= k) return 1;
	return 0;
}
void Solve()
{
	int l = 0, r = 10001;
	while(l + 1 < r){
		int mid = (l + r) >> 1;
		if(Check(mid)) l = mid;
		else r = mid;
	}
	printf("%d\n", l);
}
int main()
{
	Init();
	Solve();
}
