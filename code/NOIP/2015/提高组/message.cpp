#include <cstdio>
#include <cstdlib>
#include <cstring>
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
const int MAXN = 200000, oo = 0x7fffffff;

int n, ans = oo;
int pre[MAXN + 100];
int h[MAXN + 100];
int t[MAXN + 100];
int vis[MAXN + 100];
bool d[MAXN + 100];
bool ok[MAXN + 100];

int Readint()
{
    int x = 0;
    char c = 0;
    bool flag = 0;
    while(c = getchar()){
        if('0' <= c && c <= '9'){
            x = x * 10 + c - '0';
            flag = 1;
        }
        else if(flag) return x;
    }
    return x;
}

void Begin()
{
	freopen("message.in", "r", stdin);
	freopen("message.out", "w", stdout);
	return;
}

int min(int x, int y)
{
    return x < y? x : y;
}

void Init()
{
    int x;
    n = Readint();
    REP(i, 1, n){
        x = Readint();
        pre[i] = x;
        d[x] = 1;
    }
    return;
}

void Bfs(int x)
{
    int head = 0, tail = 1;
    h[1] = x;
    vis[x] = true;
    do{
        head ++;
        int from = h[head], to = pre[from];
        if(!ok[to]){
            vis[to] = x;
            t[to] = t[from] + 1;
            tail ++;
            h[tail] = to;
            ok[to] = 1;
        }
		else if(vis[to] == x){
            ans = min(ans, t[from] - t[to] + 1); 
            return;
		}
    }while(head < tail);
    return;
}

void Work()
{
    REP(i, 1, n)
        if(!vis[i] && d[i])
            Bfs(i);
    printf("%d\n", ans);
    return;
}

void End()
{
	fclose(stdin);
	fclose(stdout);
	return;
}

int main()
{
	//Begin();
	Init();
	Work();
	//End();
	return 0;
}
