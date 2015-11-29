#include<iostream>
#include<cstdio>
#include<vector>
using namespace std;
struct node{
	int w,next;
}a[400001];
int num,w[400001],pre[400001],ans,maxn;
void push(int x,int y){
	num++;
	a[num].next=pre[x];
	pre[x]=num;
	a[num].w=y;
}
int main(){
	int n;
	scanf("%d",&n);
	for(int i=1;i<n;i++){
		int x,y;
		scanf("%d%d",&x,&y);
		push(x,y);push(y,x);
	}
	for(int i=1;i<=n;i++)
		scanf("%d",&w[i]);
	for(int i=1;i<=n;i++){
		int i0,sum=0,max0=0,max1=0;
		int k=pre[i];
		while(k){
			sum+=w[a[k].w];
			sum%=10007;
			k=a[k].next;
			if(w[a[k].w]>=max0){
				max1=max0;
				max0=w[a[k].w];
			}
		}
		k=pre[i];
		while(k){
			ans+=w[a[k].w]*(sum-w[a[k].w]);
			k=a[k].next;
		}
		maxn=max(maxn,max0*max1);
	}
	printf("%d %d\n",maxn,ans);
}
