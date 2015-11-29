#include<cstdio>
#define LL long long
int main(){
	int n;
	while(scanf("%d",&n)==1&&n){
		if(n==0||n==1){
			printf("1\n");
			continue;
		}
		if(n==2){
			printf("2\n");
			continue;
		}
		LL v(0),e(0);
		for(int i=1;i<=n-3;i++)
			v+=(n-2-i)*i,
			e+=(n-2-i)*i+1;
		v=v*n/4+n,e=e*n/2+n;
		printf("%I64d ",e+2-v+n-1);
	}
}
