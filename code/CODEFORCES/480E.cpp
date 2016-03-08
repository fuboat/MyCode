// codeforces #480E
// Fuboat
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define rep(i, x, y) for(int i = x, _ = y; i >= _; i --) 
int min(int x, int y) { return x < y? x : y; }
int max(int x, int y) { return x > y? x : y; }
bool Chkmin(int &x, int y) { return y < x? x = y, true : false; }
bool Chkmax(int &x, int y) { return y > x? x = y, true : false; }
const int MAXN = 4000, oo = 0x3f3f3f3f;
bool c[MAXN][MAXN];
int Up[MAXN][MAXN], Down[MAXN][MAXN], Ans[MAXN * 4];
int n, m, k, X;

struct Sta{
	int x, pos;
	Sta(){}
	Sta(int x, int pos):
		x(x), pos(pos){}
	bool operator < (const Sta &a) const {
		if(x != a.x)
			return x < a.x;
		return pos < a.pos;
		// Remember, if (x == a.x && pos < a.pos), *this < a == true!
	}
};

struct SpecialQueue{
	int head, tail;
	Sta q[MAXN];
	inline void Init()
	{
		head = tail = 0;
	}
	inline void push(Sta a)
	{
		while(head <= tail) {
			if(a < q[tail])
				tail --;
			else break;
		}
		q[++ tail] = a;
	}
	inline Sta top()
	{
		if(head > tail)
			puts("error!");
		return q[head];
	}
	bool empty()
	{ return head > tail; }
	inline void pop() { head ++; }
}UpQueue, DownQueue;

void Update(int x, int y)
{
	if(c[x][y])
		return ;
	
	for(int i = x; i > 0 && !c[i][y]; i --)
		Down[i][y] = x - i;
	
	for(int i = x; i <= n && !c[i][y]; i ++)
		Up[i][y] = i - x;

	c[x][y] = true;
}

void Maintain(int o)
{
	Chkmax(Ans[o], Ans[o << 1]);
	Chkmax(Ans[o], Ans[o << 1|1]);
}

void Work(int o, int l, int r)
{	
	if(X && (X < l || X > r))
		return ;
	
	int mid = (l + r) >> 1, L = 1, R = 1, UpTmp, DownTmp, ans = 0;
	
	UpQueue.Init();
	DownQueue.Init();
	
	do{
		UpQueue.push(Sta(Up[mid][R], R));
		DownQueue.push(Sta(Down[mid][R], R));
		
		UpTmp = min(UpQueue.top().x, mid - l + 1);
		DownTmp = min(DownQueue.top().x, r - mid + 1);
		
		while(UpTmp + DownTmp - 1 < R - L + 1) {
			L = min(UpQueue.top().pos, DownQueue.top().pos) + 1;
				
			if(UpQueue.top().pos < L)
				UpQueue.pop();
			if(DownQueue.top().pos < L)
				DownQueue.pop();
			
			if(UpQueue.empty() || DownQueue.empty())
				break;

			UpTmp = min(UpQueue.top().x, mid - l + 1);
			DownTmp = min(DownQueue.top().x, r - mid + 1);
		}
		Chkmax(ans, min(UpTmp + DownTmp - 1, R - L + 1));
	} while(++ R <= m);

	Ans[o] = ans;
	if(l == r)
		return;
	
	Work(o << 1, l, mid);
	Work(o << 1|1, mid + 1, r);
	Maintain(o);
}

char s[MAXN]; 
void Init()
{
	scanf("%d%d%d", &n, &m, &k);
	
	REP(i, 1, n) { 
		scanf("%s", s + 1);
		REP(j, 1, m)
			if(s[j] == 'X')
				c[i][j] = true;
	}
	
	REP(j, 1, m) {
		REP(i, 1, n)
			Up[i][j] = c[i][j]? 0 : Up[i - 1][j] + 1;
		rep(i, n, 1)
			Down[i][j] = c[i][j]? 0 : Down[i + 1][j] + 1;
	}
	// Init quickly!
	// n^3 is too slow!
}

void Solve()
{
	int x, y;

	X = 0;
	Work(1, 1, n);
	REP(i, 1, k) {
		Readin(x);
		Readin(y);
		X = x;
		Update(x, y);
		Work(1, 1, n);
		printf("%d\n", Ans[1]); 
	}
}

int main()
{
	Init();
	Solve();
}
