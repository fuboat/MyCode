/*
	FROM: NOI
	TASK: 2004
	ID: fuboat
	ALGORITHM: Default
	DATA STRUCTURE: Segment tree
	MISTAKE:
	1. If stev[o] == 1, there is no need to maintain, or the program will be slower and wrong;
	2. If a person who leaves the company at once after he joined(his initial salary is too little), he is not one of the people who leaved the company(because he has never work here);
*/
#include <cstdio>
int readin(){
	int x = 0;bool flag = 0;char c = 0;
	while(c = getchar()){
		if(c == '-'){
			return -readin();
		}
		if(c >= '0' && c <= '9'){
			x = x * 10 + c - '0';
			flag = 1;
		}
		else if(flag) return x;
	}
}
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
const int MAXN = 100000 + 1000, oo = 0x7fffffff, MAXA = 300000 + 1000, MAXV = 1000000 + 1000;
int a[MAXN], X, P, ans, out;
struct segment{
	int sumv[MAXV];
	bool setv[MAXV];
	
	void maintain(int o, int l, int r)
	{
		int lc = o << 1, rc = o << 1|1, mid = l + (r - l) / 2;
		if(setv[o]) return ;
		if(r < P){ //r < P!!!
			setv[o] = 1;
			sumv[o] = 0;
		}else{
			maintain(lc, l, mid);
			if(mid + 1 < P) maintain(rc, mid + 1, r); //mid + 1 < P!!!
			sumv[o] = sumv[lc] + sumv[rc];
		}
		//printf("maintain(o = %d, l = %d, r = %d, sum = %d\n", o, l, r, sumv[o]);
	}
	
	void update(int o, int l, int r)
	{
		int lc = o << 1, rc = o << 1|1, mid = l + (r - l) / 2;
		if(l == r){
			sumv[o] ++;
			setv[o] = 0;
		}else{
			if(setv[o]){
				setv[lc] = setv[rc] = 1;
				sumv[lc] = sumv[rc] = 0;
				setv[o] = 0;
			}
			if(X <= mid) update(lc, l, mid);
			else update(rc, mid + 1, r);
			sumv[o] = sumv[lc] + sumv[rc];
		}
		//printf("update(o = %d, l = %d, r = %d, sum = %d\n", o, l, r, sumv[o]);
	}
	
	void query(int o, int l, int r, int p)
	{
		int lc = o << 1, rc = o << 1|1, mid = l + (r - l) / 2;
		if(l == r) ans = l;
		else if(sumv[lc] >= p && !setv[lc])
			query(lc, l, mid, p);
		else query(rc, mid + 1, r, p - sumv[lc]);
		//printf("query(o = %d, l = %d, r = %d, sum = %d\n", o, l, r, sumv[o]);
	}
}t;

int main()
{
	int n, L = -100000, R = 200000, cnt = 0;
	n = readin(); P = readin();
	REP(i, 1, n){
		char c = getchar();
		while(c == ' ' || c == '\n') c = getchar();
		X = readin();
		switch(c){
		case 'I': 
			if(X >= P) cnt ++, t.update(1, L, R); break; //X >= P!!!
		case 'A':
			L += X, R += X; break;
		case 'S':
			L -= X, R -= X; t.maintain(1, L, R); break;
		case 'F':
			if(t.sumv[1] >= X)
				t.query(1, L, R, t.sumv[1] - X + 1), printf("%d\n", ans); 
			else printf("-1\n");
			break;
		}
	}
	printf("%d\n", cnt - t.sumv[1]);
}

