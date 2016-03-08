/*
	FROM: YALI TRAINLING
	ID: fuboat
	TASK: 1150
	ALGORITHM: Math
	DATA STRUCTURE: Default
	Mistake:
	1.(line 31) gcd(abs(x1 - x2), (y1 - y2));
	Experience:
*/
#include <cstdio>
#include <cstdlib>
int gcd(int a, int b)
{
	if(b == 0) return a;
	int r = a % b;
	while(r){
		a = b;
		b = r;
		r = a % b;
	}
	return b;
}
int main()
{
	int T;
	scanf("%d", &T);
	while(T --){
		int x1, y1, x2, y2;
		scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
		if(gcd(abs(x1 - x2), abs(y1 - y2)) == 1) puts("no\n");
		else puts("yes\n");
	}
}
