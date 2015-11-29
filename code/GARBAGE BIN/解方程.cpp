#include<iostream>
#include<cstdio>
#include<cstring>
#define For(i,x,y) for(int i=(x);i<=(y);i++)
#define H 1
#define LL int
using namespace std;
LL sum=0,a[5][201],HASH[]={10007,14503},n,m,ans[1001];
int cnt[H+1][30000],OK[H+1][30000];
int change(char* x,int num){
	int size=strlen(x),sum=0;
	int ok=0;
	if(x[0]=='-')ok=1;
	else sum=x[0]-'0';
	for(int i=1;i<size;i++)
		sum=(sum*10+x[i]-'0')%num;
	if(ok)sum=-sum;
	return (sum+num)%num;
}
LL qjs(int x,int k){
	LL *t=a[k],sum=0,hash=HASH[k];x=x%hash;
	//if(OK[k][x])return cnt[k][x];
	for(int i=n;i>=1;i--) sum=x*(t[i]+sum)%hash;
	cnt[k][x]=(sum+t[0])%hash;
	//OK[k][x]=1;
	return cnt[k][x];
}
int main(){
	scanf("%d%d",&n,&m);
	For(i,0,n){
		char x[10000]={0};
		scanf("%s",x);
		For(j,0,H)a[j][i]=change(x,HASH[j]);
	}
	For(i,1,m){
		bool ok=0;
		For(j,0,H){
			if(qjs(i,j)){
				ok=1;break;
			}
		}
		if(!ok){
			sum++;
			ans[sum]=i;
		}
	}
	printf("%d\n",sum);
	For(i,1,sum)printf("%d\n",ans[i]);
}
