#include<cstdio>
#define MAX_N 100 + 10
#define MAX_M 20 + 1
#define MAX_A 20000 + 100
#define int unsigned long long
#define d(x) d[x+10000]
unsigned long long d[MAX_A],a[MAX_N],sum[MAX_N][MAX_M],maxn;
int max(int x,int y){
	if(x>y)return x;
	return y;
}
int Read(){
	int x=0,s=1;bool flag=0;char c=0;
	while(c=getchar()){
		if(c=='-')s=-1;
		if(c>='0'&&c<='9'){
			x=x*10+c-'0';
			flag=1;
		}
		else if(flag)return s*x;
	}
}
main(){
	int n=Read(),m=Read();
	for(int i=1;i<=n;i++){
		a[i]=Read();
		for(int j=i-1;j>=1;j--){
			if(a[j]<=a[i]&&d(a[j])==j){
				for(int k=1;k<=m-1&&sum[j][k];k++)
					sum[i][k+1]+=sum[j][k];
			}
		}
		maxn+=sum[i][m];
		sum[i][1]=1;
		d(a[i])=i;
	}
	printf("%lld",maxn);
}
		
	
