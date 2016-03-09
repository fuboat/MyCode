#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
template <typename T> bool Chkmax(T &x, T y) { return x < y? x = y, true : false; }
template <typename T> bool Chkmin(T &x, T y) { return y < x? x = y, true : false; }
const int HASHSIZE = 1000, MAXN = 7 + 4, MAXM = MAXN, MAXSIZE = 100000 + 100;
typedef long long LL;
int n, m;
int tot[10];
int a[MAXN][MAXM];

struct Point {
	int x, y;
	Point(int x = -1, int y = -1):
		x(x), y(y) {}
	bool operator == (const Point &p) const
	{
		return p.x == x && p.y == y;
	}
	bool operator != (const Point &p) const
	{
		return !(*this == p);
	}
} pos[10], no;

struct Status {
	bool flag;
	int a[MAXN], bel[3], ok[3], tong[8], to[8];
	// bel[i] = 0: p[i] doesn't belong to any plug (or no p[i]);
	// bel[i] = x: p[i] belongs to the plug numberd x (x > 0);
	// For encode
	Status (int *b, int *ok, int *Bel)
	{
		// Pay attention to the turn!
		for (int i = 0; i < 3; i ++)
			bel[i] = Bel[i];
		for (int i = 0; i < m; i ++)
			tong[a[i] = b[i]] ++;
		flag = 0;
	}
	
	// For decode
	Status (LL v, int N = m)
	{
		flag = v & 1;
		v >>= 1;
		while (N)
			tong[a[-- N] = GetInf(v)] ++;
		for (int i = 2; i >= 0; i --, v >>= 1)
			ok[i] = v & 1;
		for (int i = 2; i >= 0; i --)
			tong[bel[i] = GetInf(v)] ++;
	}
	
	LL Decode ()
	{
		LL val = 0;
		// Pay attention to the turn!
		for (int i = 0; i < 3; i ++)
			AddInf(val, bel[i]);
		for (int i = 0; i < 3; i ++)
			val = val << 1 & ok[i];
		for (int i = 0; i < m; i ++)
			AddInf(val, a[i]);
		
		val = val << 1 | flag;
		return val;
	}
	
	void Update ()
	{
		static int to[8];
		
		int cnt = 0;
		for (int i = 0; i < m; i ++)
			if (tong[i])
				to[tong[i]] = ++ cnt;
				
		for (int i = 0; i < m; i ++)
			a[i] = to[a[i]];
		for (int i = 0; i < 3; i ++)
			bel[i] = to[bel[i]];
	}
	
	inline void AddInf (LL &v, int x)
	{
		v <<= 3;
		v += x;
	}
	
	inline int GetInf (LL &x)
	{
		int tmp = x & 7;
		x >>= 3;
		return tmp;
	}
	
	void Union (int p1, int p2)
	{
		int x = a[p1], y = a[p2];
		if (x > y)
			std::swap(x, y);
		
		if (x == 0) {
			a[p1] = a[p2] = y;
			return ;
		}
		
		for (int i = 0; i < m; i ++)
			tong[i] = 0;
			
		for (int i = 0; i < m; i ++) {
			if (a[i] == y)
				a[i] = x;
			else if (a[i] > y)
				a[i] --;
			tong[a[i]] ++;
		}
		
		for (int i = 0; i < 3; i ++)
			if (bel[i] == y)
				bel[i] = x;
			else if (bel[i] > y)
				bel[i] --;
				
		if (!flag && ok[0] && ok[1] && ok[2] && bel[0] && bel[0] == bel[1] && bel[1] == bel[2])
			flag = true;
	}
	
	void Add (int p)
	{
		for (int i = 0; i < m; i ++)
			tong[i] = 0;
		
		int mx = 0;
		for (int i = 0; i < p; i ++) {
			Chkmax(mx, a[i]);
			tong[a[i]] ++;
		}
		
		a[p] = mx + 1;
		tong[a[p]] ++;
		for (int i = p + 1; i < m; i ++) {
			if (a[i] >= a[p])
				a[i] ++;
			tong[a[i]] ++;
		}
	}
	
	void Delete (int p)
	{
		if (p == 0)
			return ;
			
		int x = a[p];
		if (tong[x] == 1) {
			memset(tong, 0, sizeof(tong));
			a[p] = 0;
			for (int i = 0; i < 3; i ++)
				if (bel[i] == x)
					bel[i] = 0;
					
			for (int i = 0; i < m; i ++)
				tong[a[i]] ++;
			Update();
		} else
			a[p] = 0;
	}
	
	bool operator == (const Status &s) const
	{
		for (int i = 0; i < m; i ++)
			if (a[i] != s.a[i])
				return false;
		
		for (int i = 0; i < 3; i ++)
			if (bel[i] != s.bel[i])
				return false;
		
		for (int i = 0; i < 3; i ++)
			if (ok[i] != s.ok[i])
				return false;
		
		if (flag != s.flag)
			return false;
			
		return true;
	}
};

struct HashTable {
	int tot;
	int head[HASHSIZE], next[MAXSIZE], val[MAXSIZE];
	LL hash[MAXSIZE];
	// Add Status in the hash table
	void Add(Status &sta, int w)
	{
		LL x = sta.Decode();
		int mod = x % HASHSIZE;
		
		for (int i = head[mod]; i; i = next[i])
			if (x == hash[i]) {
				val[i] += w;
				return ;
			}
		
		hash[++ tot] = x;
		next[tot] = head[mod];
		head[mod] = tot;
		val[tot] = w;
	}
	int Query(Status &sta)
	{
		int x = sta.Decode(), mod = x % HASHSIZE;
		for (int i = head[mod]; i; i = next[i])
			if (x == hash[i])
				return val[i];
		return 0;
	}
} dp[MAXN][MAXM];

bool TestForStatus(LL a)
{
	Status s(a);
	Status s0(0);
	return s == s0;
}

void Update(int x, int y, Status s, int k, int w)
{
	int s1 = s.a[y], s2 = s.a[y + 1];
	
	if (y == m) {
		x ++;
		y = 0;
		for (int i = m; i > 0; i --)
			s.a[i] = s.a[i - 1];
		s.a[0] = 0;
	} else {
		if (k == 4) {
			s.Delete(y);
			s.Delete(y + 1);
		} else {
			if (k < 3 && ((tot[k] && pos[k] != Point(x, y)) || s.ok[k]))
				return ;
			
			if (!s1 && !s2)
				s.Add(y);
			
			s.Union(y, y + 1);
			
			if (k < 3) {
				s.bel[k] = s.a[y];
				s.ok[k] = true;
			}
		}
	}
		
	dp[x][y].Add(s, w);
}

void Work(int x, int y, const Status &s, int w)
{
	if (y == m - 1)
		Update(x, y + 1, s, 0, w);
	else if (a[x][y + 1] == 5)
		for (int i = 0; i < 5; i ++)	
			Update(x, y + 1, s, i, w);
	else
		Update(x, y + 1, s, a[x][y + 1], w);
}

void Solve()
{
	int ans = 0;
	for (int i = 0; i < n; i ++)
		for (int j = 0; j < m; j ++)
			for (int k = 0; k < HASHSIZE; k ++)
				for (int o = dp[i][j].head[k]; o; o = dp[i][j].next[o]) {
					Work(i, j, Status(dp[i][j].hash[o]), dp[i][j].val[o]);
					if (i == n - 1 && j == m - 1 && (dp[i][j].hash[o] & 1))
						ans += dp[i][j].val[o];
				}
	printf("%d\n", ans);			
}

void Init()
{
	static int change[300];
	change['.'] = 3;
	change['S'] = 0;
	change['X'] = 1;
	change['E'] = 2;
	change['?'] = 5;
	change['#'] = 4;
	
	char c[10];
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; i ++) {
		scanf("%s", c);
		for (int j = 0; j < m; j ++) {
			c[j] = change[c[j]];
			a[i][j] = c[j];
			pos[c[j]] = Point(i, j);
			tot[c[j]] ++;
		}
	}
	
	int a[10] = {0};
	Update(-1, m, Status(0), 0, 1);
}

int main()
{
	if (fopen("map.in", "r") != NULL) {
		freopen("map.in", "r", stdin);
		freopen("map.out", "w", stdout);
	}
	
	Init();
	Solve();
	
	fclose(stdin);
	fclose(stdout);
	
	return 0;
}
