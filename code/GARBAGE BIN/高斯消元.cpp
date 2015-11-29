#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
#define MAXN 100 + 10
#define For(i,n) for(int i=1;i<=n;i++)
#define FOR(i,x,y) for(int i=(x);i<=(y);i++)
#define LL long double
using namespace std;
vector<LL>a[MAXN];
LL ans[MAXN];	
LL n;
void ycl(int i){
	FOR(j,i,n)if(a[j][i]){
		swap(a[i],a[j]);
		return ;
	}
}
main(){
	scanf("%d",&n);
	For(i,n){
		LL x;
		a[i].push_back(0);
		For(j,n){
			scanf("%d",&x);
			a[i].push_back(x);
		}
		scanf("%d",&x);
		a[i].push_back(x);
	}
	For(i,n){
		ycl(i);
		FOR(j,i+1,n){
			if(a[j][i]==0)continue;
			LL temp=-a[i][i]/a[j][i];
			FOR(k,i,n+1)
				a[j][k]=a[i][k]+a[j][k]*temp;
		}
	}
	for(int i=n;i>=1;i--){
		LL sum=0;
		for(int j=i+1;j<=n;j++)sum+=ans[j]*a[i][j];
		sum=a[i][n+1]-sum;
		ans[i]=sum/a[i][i];
	}
	For(i,n)cout<<ans[i];
}
	
