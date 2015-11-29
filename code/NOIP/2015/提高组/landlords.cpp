#include <cstdio>
#include <cstring>
#include <cstdlib>
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define Rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
const int oo = 0x7ffffff;
template <typename T> bool chkmin(T &x, T y){return y < x? (x = y, true) : false;}
template <typename T> bool chkmax(T &x, T y){return y > x? (x = y, true) : false;}
int cnt[20];
int f[24][15][9][7];
bool vis[24][15][9][7];
int ch[20] = {16, 14, 15, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
int ans = oo;

void Begin()
{
    freopen("landlords.in", "r", stdin);
    freopen("landlords.out", "w",stdout);
    return;
}

void End()
{
    fclose(stdin);
    fclose(stdout);
}

int work(int s1, int s2, int s3, int s4)
{
	int &now = f[s1][s2][s3][s4];
	if(vis[s1][s2][s3][s4] || !(s1 || s2 || s3 || s4)) return now;
	vis[s1][s2][s3][s4] = 1;
	now = oo;
	if(s4){
		chkmin(now, work(s1, s2, s3, s4 - 1) + 1);
		if(s1 > 1) chkmin(now, work(s1 - 2, s2, s3, s4 - 1) + 1);
		if(s2 > 1)
			chkmin(now, work(s1, s2 - 2, s3, s4 - 1) + 1);
	}
	if(s3){
		chkmin(now, work(s1, s2, s3 - 1, s4) + 1);
		if(s1) chkmin(now, work(s1 - 1, s2, s3 - 1, s4) + 1);
		if(s2) chkmin(now, work(s1, s2 - 1, s3 - 1, s4) + 1);
	}
	if(s2) chkmin(now, work(s1, s2 - 1, s3, s4) + 1);
	if(s1) chkmin(now, work(s1 - 1, s2, s3, s4) + 1);
	return now;
}

void dp(int now)
{
	int s[5] = {0};
	REP(i, 3, 16)
		s[cnt[i]] ++;
	chkmin(ans, work(s[1], s[2], s[3], s[4]) + now);
}

void dfs(int f1, int now)
{
	if(f1 == 0) Rep(beg, 10, 3){
		bool flag = 1;
		int ed = 14;
		REP(i, beg, 14){
			if(cnt[i] > 0)
				cnt[i] --;
			else{
				ed = i - 1;
				break;
			}
			if(i - beg >= 4)
				dfs(f1, now + 1);
		}
		REP(i, beg, ed)
			cnt[i] ++;
	}
	else if(f1 == 1) Rep(beg, 12, 3){
		bool flag = 1;
		int ed = 14;
		REP(i, beg, 14){
			if(cnt[i] >= 2)
				cnt[i] -= 2;
			else{
				ed = i - 1;
				break;
			}
			if(i - beg >= 2) dfs(f1, now + 1);
		}
		REP(i, beg, ed)
			cnt[i] += 2;
	}
	else if(f1 == 2) Rep(beg, 13, 3){
		bool flag = 1;
		int ed = 14;
		REP(i, beg, 14){
			if(cnt[i] >= 3)
				cnt[i] -= 3;
			else{
				ed = i - 1;
				break;
			}
			if(i - beg >= 1) dfs(f1, now + 1);
		}
		REP(i, beg, ed)
			cnt[i] += 3;
	}
	if(f1 == 3) dp(now);
	else dfs(f1 + 1, now);
}				
				
				

int main(){
    //Begin();
    int T, n;
    scanf("%d%d", &T, &n);
    while(T --){
        memset(cnt, 0, sizeof(cnt));
        REP(i, 1, n){
            int x, c;
            scanf("%d %d", &x ,&c);
            cnt[ch[x]] ++;
        }
        dfs(0, 0);
        printf("%d\n", ans);
        ans = oo;
    }
    //End();
    return 0;
}
