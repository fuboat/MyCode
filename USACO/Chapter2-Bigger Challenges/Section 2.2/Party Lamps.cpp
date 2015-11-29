/* 
	ID: 60303451
	TASK: lamps
	LANG: C++
*/
#include <cstdio>
#include <cstring>
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
const int MAXN = 100 + 10;
int n, c, sta[MAXN], num;
char ans[MAXN][MAXN];
int ok[MAXN];

void Init()
{
	scanf("%d%d", &n, &c);
	REP(i, 1, n) sta[i] = -1;
	int x;
	while(scanf("%d", &x) && x != -1)
		sta[x] = 1;
	while(scanf("%d", &x) && x != -1)
		sta[x] = 0;
}

void change(bool now[], int i)
{
	REP(j, 1, n){
		int cnt = 0;
		if(i & 1 << 0) cnt ++; 
		if((i & 1 << 1) && (j & 1))  cnt ++;
		if((i & 1 << 2) && !(j & 1)) cnt ++;
		if((i & 1 << 3) && (j - 1) % 3 == 0) cnt ++;
		if(cnt & 1) now[j] = !now[j];
	}
}

int bitcount(int i){return i == 0? 0 : bitcount(i >> 1) + (i & 1);}

void Solve()
{
	REP(i, 0, (1 << 4) - 1){
		bool now[MAXN], flag = 1;
		REP(j, 1, n) now[j] = true;
		change(now, i);
		int cnt = bitcount(i);
		if(cnt % 2 == c % 2 && c >= cnt){
			REP(i, 1, n)
				if(sta[i] != -1 && sta[i] != now[i]){flag = 0; break;}
			if(!flag) continue;
			num ++;
			REP(i, 0, n - 1) ans[num][i] = now[i + 1] + '0';
		}
	}
}

void print_ans()
{
	while(true){
		bool first = 1;
		int now = 0;
		REP(i, 1, num)
			if(ok[i]) continue;
			else if(first){now = i; first = 0;}
			else if(strcmp(ans[i], ans[now]) < 0) now = i;
		if(now == 0) break;
		printf("%s\n", ans[now]);
		ok[now] = 1;
	}
}

int main()
{
	freopen("lamps.in", "r", stdin);
	freopen("lamps.out", "w", stdout);
	Init();
	Solve();
	if(!num) printf("IMPOSSIBLE\n");
	else print_ans();
	return 0;
}
