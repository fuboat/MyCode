#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#define FOR(i,x,y) for(int i=x;i<=y;i++)
#define For(i,x,y) for(int i=x;i>=y;i--)
#define max_n 500 + 1
using namespace std;
vector<int>l[501],r[501];
int Read(){
	int x=0;bool flag=0;char c=0;
	while(c=getchar()){
		if(c>='0'&&c<='9')x=x*10+c-'0',flag=1;
		else if(flag) return x;
	}
}
int print(int* x){
	int num=1;
	while(x[num])printf("%d ",x[num++]);
	putchar('\n');
}
int a[max_n],f[max_n],sum[max_n];
int main(){
	memset(f,0x7f,sizeof(f));
	int n=Read(),m=Read();
	FOR(i,1,n)a[i]=Read();
	sort(a+1,a+n+1);
	print(a);
	FOR(i,1,n){
		sum[i]=sum[i-1]+a[i];
		f[i]=sum[i];
		l[i].push_back(1);
		r[i].push_back(i);
	}
	FOR(i,2,m)For(j,n,m){
		int temp;
		For(k,j-1,m-1)
			if(f[j]>=max(f[k],sum[j]-sum[k]))
				temp=k,f[j]=max(f[k],sum[j]-sum[k]);
		l[j]=l[temp];l[j].push_back(temp+1);
		r[j]=r[temp];r[j].push_back(j);
	}
	FOR(i,0,m-1)printf("%d %d\n",l[n][i],r[n][i]);
}
