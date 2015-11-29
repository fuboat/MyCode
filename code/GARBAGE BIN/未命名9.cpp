#include<cstdio>
#include<cmath>
int sum,n,n0;
bool ok[10001];
int gcd(int a,int b){
	if(!b)return a;
	return gcd(b,a%b);
}
void s(int x){
	for(int i=x;i<=n0;i+=x)
		ok[i]=1;
}
int main(){
	scanf("%d",&n);
	n0=n;
	//int temp=sqrt(n+0.5);
	for(int i=1;i<=n;i++){
		/*if(n%i==0)s(i);
		while(n%i==0)n/=i;*/
		if(gcd(n,i)!=1)ok[i]=1;
	}
	//if(n!=1)s(n);
	for(int i=1;i<=n0;i++)
		if(!ok[i])sum++;
	printf("%d\n",sum);
}
