#include<cstdio>
int l[20],d1[100],d2[100];
int n,a[20],sum;
void print(){
	printf("%d",a[1]);
	for(int i=2;i<=n;i++)
		printf(" %d",a[i]);
	putchar('\n');
	sum++;
}
void find(int k){
	if(k==n+1)
		if(sum<3)print();
		else sum++;
	for(int i=1;i<=n;i++){
		if(!l[i]&&!d1[i+k]&&!d2[i-k+20]){
			a[k]=i;
			l[i]=1;
			d1[i+k]=1;
			d2[i-k+20]=1; 
			find(k+1);
			l[i]=0;
			d1[i+k]=0;
			d2[i-k+20]=0; 
		}
	}
}
int main(){
	scanf("%d",&n);
	find(1);	
	printf("%d\n",sum);
}
