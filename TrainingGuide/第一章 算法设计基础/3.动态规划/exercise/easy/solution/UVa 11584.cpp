/*
	FROM: UVa
	TASK: 11584
	ID: fuboat
	ALGORITHM: Dynamic Programming
	DATA STRUCTURE: Vector
	MISTAKE:
	1.(line 37) When 'i == j', we shouldn't do 'd[j].push_back(i)';
	2.(line 28) Don't forget clean the vector;
	EXPERIENCE: (Sorry, there is nothing)
*/
#include <cstdio>
#include <vector>
#include <cstring>
using std::vector;
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
template <typename T> bool chkmin(T &x, T y){return y < x? (x = y, true) : false;}
template <typename T> bool chkmax(T &x, T y){return y > x? (x = y, true) : false;}

const int MAXL = 1000, oo = 0x7fffffff;
char s[MAXL + 10];
bool f[MAXL + 10][MAXL + 10];
int g[MAXL + 10], L;
vector<int>d[MAXL + 10];

void Init()
{
	REP(i, 1, L) d[i].clear();
	scanf("%s", s + 1);
	L = strlen(s + 1);
	REP(k, 0, L - 1)
		REP(i, 1, L - k){
			int j = i + k;
			f[i][j] = 0;
			if(s[i] == s[j] && (f[i + 1][j - 1] || i + 1 >= j - 1)){
				f[i][j] = 1;
				if(i != j) d[j].push_back(i);
			}
		}
}

void Solve()
{
	REP(i, 1, L){
		int &ans = g[i];
		ans = g[i - 1] + 1;
		REP(j, 0, d[i].size() - 1)
			chkmin(ans, g[d[i][j] - 1] + 1);
	}
	printf("%d\n", g[L]);
}

int main()
{
	int n;
	scanf("%d", &n);
	while(n --){
		Init();
		Solve();
	}
}
