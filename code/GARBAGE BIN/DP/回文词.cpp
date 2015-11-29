#include<cstdio>
#define MAXN 5000 + 100
int min(int x,int y){
	if(x<y)return x;
	return y;
}
int f[MAXN][MAXN];
char s[MAXN];
int main(){
	int n;
	scanf("%d",&n);
	getchar();
	gets(s+1);
	for(int k=1;k<=n-1;k++)
		for(int l=1;l+k<=n;l++){
			int r=l+k;
			if(s[l]==s[r])f[l][r]=f[l+1][r-1];
			else f[l][r]=min(f[l+1][r]+1,f[l][r-1]+1);
		}
	printf("%d\n",f[1][n]);
}
