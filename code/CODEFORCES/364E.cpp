// Codeforces #364E
// Fuboat
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#define CLEAR(a) memset(a, 0, sizeof(a)) 
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++) 
#define rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
bool Chkmax(int &x, int y) { return y > x? x = y, true : false; }
bool Chkmin(int &x, int y) { return y < x? x = y, true : false; }

const int MAXN = 3000 + 100, MAXK = 6 + 1;
int n, m, k;
long long ans;
int a[MAXN][MAXN], UpDown[MAXN][MAXN], LeftRight[MAXN][MAXN], sumv[MAXN][MAXN];

inline int GetSum(int xl, int xr, int yl, int yr)
{ return sumv[xr][yr] - sumv[xr][yl - 1] - sumv[xl - 1][yr] + sumv[xl - 1][yl - 1]; }

void Init()
{
	char c;
	
	scanf("%d%d%d", &n, &m, &k);
	REP(i, 1, n)
		REP(j, 1, m) {
			c = getchar();
			while(c != '0' && c != '1')
				c = getchar();
			a[i][j] = c - '0';
		}

	REP(i, 1, n)
		REP(j, 1, m) {
			LeftRight[i][j] = LeftRight[i][j - 1] +         a[i][j];
			   UpDown[i][j] =    UpDown[i - 1][j] +         a[i][j];
			     sumv[i][j] =      sumv[i - 1][j] + LeftRight[i][j];
			// 别管我……我有强迫症…… 
		}
}

int sum1[MAXK], sum2[MAXK], tot1[MAXK], tot2[MAXK];
void WorkUpDown(int xl, int xr, int yl, int yr)
{
	int M = (xl + xr) >> 1, sum, tot = 0;
	REP(L, yl, yr) {
		REP(i, 0, k)
			sum1[i] = sum2[i] = 0;

		rep(R, yr, L) {
			REP(i, 0, k) {
				while(M - sum1[i] >= xl && GetSum(M - sum1[i], M, L, R) <= i)
					sum1[i] ++;
				while(M + 1 + sum2[i] <= xr && GetSum(M + 1, M + 1 + sum2[i], L, R) <= i)
				                                    //There is 'M + 1', not 'M;
					sum2[i] ++;

				tot1[i] = sum1[i];
				tot2[i] = sum2[i];
				if(i) {
					tot1[i] -= sum1[i - 1];
					tot2[i] -= sum2[i - 1];
				}
			}
			
			REP(i, 0, k) {
				ans += tot1[i] * tot2[k - i];
				tot += tot1[i] * tot2[k - i];
			}
		}
	}
	//printf("WorkUpDown(%d, %d, %d, %d):  %d\n", xl, xr, yl, yr, tot);
}

void WorkLeftRight(int xl, int xr, int yl, int yr)
{
	int M = (yl + yr) >> 1, i, tot = 0;
	REP(L, xl, xr) {
		REP(i, 0, k)
			sum1[i] = sum2[i] = 0;

		rep(R, xr, L) {
			REP(i, 0, k) {
				while(M - sum1[i] >= yl && GetSum(L, R, M - sum1[i], M) <= i)
					sum1[i] ++;
				while(M + 1 + sum2[i] <= yr && GetSum(L, R, M + 1, M + 1 + sum2[i]) <= i)
				                                           //There is 'M + 1', not 'M;
					sum2[i] ++;
				
				tot1[i] = sum1[i];
				tot2[i] = sum2[i];
				if(i) {
					tot1[i] -= sum1[i - 1];
					tot2[i] -= sum2[i - 1];
				}
			}

			REP(i, 0, k) {
				ans += tot1[i] * tot2[k - i];
				tot += tot1[i] * tot2[k - i];
			}
		}
	}
	//printf("WorkLeftRight(%d, %d, %d, %d):  %d\n", xl, xr, yl, yr, tot);
}

void Work(int xl, int xr, int yl, int yr)
{
	if(xl == xr && yl == yr) {
		ans += (a[xl][yl] == k);
		return ;
	}
	
	if(xr - xl >= yr - yl) {
		Work(xl, (xl + xr) >> 1, yl, yr);
		Work(((xl+ xr) >> 1) + 1, xr, yl, yr);
		WorkUpDown(xl, xr, yl, yr);
	} else {
		Work(xl, xr, yl, (yl + yr) >> 1);
		Work(xl, xr, ((yl + yr) >> 1) + 1, yr);
		WorkLeftRight(xl, xr, yl, yr);
	}
}

int main()
{
	Init();
	Work(1, n, 1, m);
	printf("%I64d\n", ans);
}

