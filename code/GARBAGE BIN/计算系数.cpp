#include<iostream>
#include<cstdio>
#define For(i,x,y) for(int i=x;i<=y;i++)
#define MOD 10007
#define LL unsigned long long
using namespace std;
LL c[2001];
LL ksm(LL x,LL b){
	if(b==0)return 1;
	LL t=ksm(x,b/2);
	if(b%2==0)return t*t%MOD;
	else return t*t%MOD*x%MOD;
}
main(){
	LL x,y,n,b,e;
	scanf("%d%d%d%d%d",&x,&y,&n,&b,&e);
	x%=MOD;y%=MOD;
	x=ksm(x,b);
	y=ksm(y,e);
	c[0]=1;
	For(i,1,b) c[i]=c[i-1]*(n-i+1)*ksm(i,MOD-2)%MOD;
	printf("%d\n"x*y%MOD*c[b]%MOD);
}
