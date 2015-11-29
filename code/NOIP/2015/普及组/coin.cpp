#include <cstdio>
#include <iostream>
using namespace std;
#define LL long long
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define Rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
void Write(LL ans)
{
	if(!ans) printf("0");
	else if(ans < 0){
		ans = -ans;
		putchar('-');
	}else{
		char c[100] = {0};
		int cnt = 0;
		while(ans){
			c[cnt] = ans % 10 + '0';
			ans /= 10;
			cnt ++;
		}
		Rep(i, cnt - 1, 0) putchar(c[i]);
	}
}

void Begin()
{
	freopen("coin.in", "r", stdin);
	freopen("coin.out", "w", stdout);
}

void End()
{
	fclose(stdin);
	fclose(stdout);
}

int main()
{
	//Begin();
	int n;
	LL ans = 0;
	scanf("%d", &n);
	int now = 1, cnt = 0;
	REP(i, 1, n){
		cnt ++;
		ans += now;
		if(cnt == now){
			now ++;
			cnt = 0;
		}
	}
	Write(ans);
	putchar('\n');
	//End();
	return 0;
}
		
