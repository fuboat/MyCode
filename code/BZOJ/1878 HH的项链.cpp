#include <cstdio>
#include <iostream>
#include <algorithm>
using std::pair;
using std::sort;
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
const int MAXN = 50000;//�������� 
const int MAXA = 1000000;//��� 
const int MAXM = 200000;//ѯ�ʴ��� 
int a[MAXN + 1];     //��¼ÿ�����ǵı�� 
int ans[MAXM + 1], n, m;
struct que{		   	 //��¼ÿ��ѯ��
	int L, R, P;
	bool operator < (const que &a) const{
		return R < a.R;
	}
};
que q[MAXM];

struct fenwick{
	int f[MAXN + 1]; //��¼ǰ׺�� 
	int p[MAXA + 1]; //ÿ�����������ֵ�λ�� 
	void add(int pos, int d)
	{
		for(int x = pos; x <= n; x += x & -x)
			f[x] += d;
	}
	
	void update(int pos, int x)
	{
		if(p[x]) add(p[x], -1);
		p[x] = pos;
		add(p[x], 1);
	}
	
	int query(int r)
	{
		int d = 0;
		for(int x = r; x > 0; x -= x & -x)
			d += f[x];
		return d;
	}
};
fenwick f;

void init()
{
	scanf("%d", &n); 
	REP(i, 1, n)
		scanf("%d", &a[i]);
	scanf("%d", &m);
	REP(i, 1, m){
		scanf("%d%d", &q[i].L, &q[i].R);
		q[i].P = i;
	}
	sort(q + 1, q + m + 1);
}
	
void solve()
{
	int now = 1;
	REP(i, 1, n){
		f.update(i, a[i]);
		while(i == q[now].R){
			ans[q[now].P] = f.query(i) - f.query(q[i].L - 1);
			now ++;
		}
	}
}
	
void print()
{
	REP(i, 1, m)
		printf("%d\n", ans[i]);
}
	
int main()
{
	init();
	solve();
	print();
}
