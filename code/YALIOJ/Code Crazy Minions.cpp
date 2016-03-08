#include <cstdio>
#include <cstring>
const int MAXL = 1000 + 100;
char s[MAXL];
int main()
{
	int T;
	scanf("%d", &T);
	while(T --){
		scanf("%s", s);
		int ans = 1, len = strlen(s);
		for(int i = 1; i <= len - 1; i ++)
			if(s[i - 1] > s[i]) ans += s[i - 1] + 25 - s[i];
		if(ans <= len * 11) puts("NO");
		else puts("YES");
	}
}
