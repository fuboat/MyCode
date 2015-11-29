#include<iostream>
#include<cstdio>
#include<vector>
#define MAXN 200001
#define MAXK 51
using namespace std;
int ok[MAXN];
int w[MAXN],c[MAXN],sum[MAXK];
int size;
long long ans(0);
int main(){
	int n,k,p;
	scanf("%d%d%d",&n,&k,&p);
	ok[size++]=1;
	for(int i=1;i<=n;i++){
		scanf("%d%d",&c[i],&w[i]);
		if(w[i]<=p)ok[size++]=i;
	}
	ok[size]=n+1;
	int end=0;
	while(end<size){
		int temp[MAXK]={0};
		for(int i=ok[end];i<ok[end+1];i++)
			temp[c[i]]++;
		if(temp[c[ok[end]]])ans+=temp[c[ok[end]]]-1; 
		for(int i=0;i<k;i++){
			ans+=temp[i]*sum[i];
			sum[i]+=temp[i];
		}
		end++;
	}
	printf("%d",ans);
	return 0;
}
