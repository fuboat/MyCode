#include <cstdio>
#include <cstdlib>

int Print(int x){
	switch (x){
		case 1: putchar('I');break;
		case 0: putchar('B');break;
		case -1: putchar('F');break;
	}
	return x;
}

int dfs(int tot)
{
	if(tot == 1){
		int now;
		scanf("%1d", &now);
		if(now) putchar('I');
		else putchar('B');
		return now;
	}
	int x = dfs(tot >> 1);
	if(x == dfs(tot >> 1))
	return Print(x);
	return Print(-1);
}

int main()
{
	int l;
	scanf("%d", &l);
	dfs(1 << l);
	putchar('\n');
}
