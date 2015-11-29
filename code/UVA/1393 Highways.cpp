#include<cstdio>
#define FOR(i,x,y)	for(int i=(x);i<=(y);i++)
#define max(x,y) x>y? x:y
int gcd(int a,int b){
	if(!b)return a;
	return gcd(b,a%b);
}
int GCD[301][301];
int main(){
	int n,m;
	for(int i=1;i<=300;i++)
		for(int j=i;j<=300;j++)
			GCD[i][j]=gcd(i,j);
	while(scanf("%d%d",&n,&m)==2&&n&&m){
		int ans=0;
		FOR(i,1,n-1)
		FOR(j,1,m-1){	
			if(GCD[i][j]>1||GCD[j][i]>1)continue;
			ans+=(n-i)*(m-j)-(max(0,n-i*2))*(max(0,m-j*2));
		
		}
		printf("%d\n",ans*2);
	}
}
		
