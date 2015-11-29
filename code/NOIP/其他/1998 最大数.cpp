#include<cstdio>
#include<algorithm>
#define MAX_N 20 + 1
#define LL long long
LL a[MAX_N];
LL len(LL x){
	LL temp=0;
	while(x){
		x/=10;
		temp++;
	}
	return temp;
}
int cmp(const LL &x,const LL &y){
	int lenx=len(x),leny=len(y),x0=x,y0=y;
	for(int i=1;i<=lenx;i++)
		y0*=10;
	y0+=x;
	for(int i=1;i<=leny;i++)
		x0*=10;
	x0+=y;
	if(x0>y0)return 1;
	return 0;
}
int main(){
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	std::sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i++)
		printf("%d",a[i]);
	putchar('\n');
}
