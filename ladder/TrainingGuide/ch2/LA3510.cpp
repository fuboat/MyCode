// LA3510
// Fuboat
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <cstring>
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
const int MAXN = 2000 + 1000;
char S[14][10] = {"id", "rot", "sym", "bhsym", "bvsym", "div", "mix", "id-", "rot-", "sym-", "bhsym-", "bvsym-", "div-", "mix-"}; 
struct Pos{
	int x, y;
	Pos(){} 
	Pos(int x, int y):
		x(x), y(y){} 
};
int n;
Pos s[16][MAXN][MAXN], f[MAXN][MAXN]; 
int ans[MAXN][MAXN];
Pos Id(int i, int j) { return Pos(i, j); }
Pos Rot(int i, int j) { return Pos(n - j - 1, i); }
Pos Sym(int i, int j) { return Pos(i, n - j - 1); }
Pos Bhsym(int i, int j) { return i >= n / 2? Sym(i, j) : Id(i, j); }
Pos Bvsym(int i, int j) { return i >= n / 2? Pos(n / 2 + n - i - 1, j) : Id(i, j); } 
Pos Div(int i, int j) { return (i & 1)? Pos(i / 2 + n / 2, j) : Pos(i / 2, j); }
Pos fMix(int i, int j) // 为了代码编写方便,该函数请反过来用; 
{
	// 这个操作写起来有点绕,小心; 
	int x, y;
	if(j % 2 == 1) x = i | 1;
	else x = (i | 1) - 1;
	y = j / 2 + (i & 1) * n / 2;
	return Pos(x, y);
}
void Init()
{
	Pos a;
	REP(i, 0, n - 1)
		REP(j, 0, n - 1) {
			f[i][j] = Pos(i, j); 
			s[0][i][j] = Id(i, j);
			s[1][i][j] = Rot(i, j);
			s[2][i][j] = Sym(i, j);
			s[3][i][j] = Bhsym(i, j);
			s[4][i][j] = Bvsym(i, j);
			s[5][i][j] = Div(i, j);
			a = fMix(i, j);
			s[6][a.x][a.y] = Pos(i, j);
		}
		
	REP(k, 0, 6)
		REP(i, 0, n - 1)
			REP(j, 0, n - 1) {
				a = s[k][i][j];
		 		s[k + 7][a.x][a.y] = Pos(i, j);
		 	}
}
void Update(int x)
{
	static Pos tmp[MAXN][MAXN];
	Pos a;
	REP(i, 0, n - 1)
		REP(j, 0, n - 1) {
			a = f[i][j];
			tmp[i][j] = s[x][a.x][a.y];
		}

	REP(i, 0, n - 1)
		REP(j, 0, n - 1)
			f[i][j] = tmp[i][j];
}

int vis[MAXN][MAXN]; 
int Find(int i, int j)
{
	int cnt(0);
	Pos p, old(i, j);
	while(!vis[i][j]) {
		vis[i][j] = true;
		p = f[i][j];
		i = p.x;
		j = p.y;
		cnt ++;
	}
	return cnt;
}
int Gcd(int a, int b)
{
	int r;
	while(b){
		r = a % b;
		a = b;
		b = r;
	}
	return a;
}
void Solve()
{
	static char ss[MAXN];
	memset(vis, 0, sizeof(vis)); 
	std::vector<int> ans, action;
	int tot(1); 
	int tmp, cnt(0), pos, len(0);
	
	do{
		scanf("%s", ss);
		REP(i, 0, 13)
			if(strcmp(ss, S[i]) == 0){
				action.push_back(i);
				break; 
		}
	}while(getchar() != '\n');
	// 注意!!!命令从右往左执行(你又犯傻)!!!
	
	rep(i, action.size() - 1, 0)
		Update(action[i]);
	REP(i, 0, n - 1)
		REP(j, 0, n - 1)
			if(!vis[i][j])
				ans.push_back(Find(i, j));
	REP(i, 0, ans.size() - 1)
		tot = 1LL * tot * ans[i] / Gcd(tot, ans[i]);
	printf("%d\n", tot);
}
int main()
{
	int T;
	scanf("%d", &T);
	while(T --) {
		scanf("%d", &n);
		Init();
		Solve();
		if(T)
			puts("");
	}
}
