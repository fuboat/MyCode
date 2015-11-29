#include<cstdio>
int main(){
	int n,k;
	while(scanf("%d%d",&k,&n)==2){
		int ans=0;
		int begin=1;
		for(int i=n;i>=1;i--){
			int temp=n/i;
			if(temp==begin)continue;
			if(temp>k){
				ans+=(n%begin+n%k)*(k-begin+1)/2;
				break;
			}
			ans+=(n%begin+n%(temp-1))*(temp-begin+1)/2;
			begin=temp;
		}
		if(k>n)ans+=n*(k-n);
		printf("%d\n",ans);
		ans=0;
		for(int i=1;i<=k;i++)
			ans+=n%i;
		printf("%d\n",ans);
	}
}
		
		
