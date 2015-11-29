#include<cstdio>
#include<cstring>
#define MAXL 10
char a[MAXL],b[MAXL];
void work(int l1,int r1,int l2,int r2){
	if(l1>r1)return;
	if(l1==r1){
		putchar(a[l1]);
		return;
	}
	char k=b[r2];
	int mid=strchr(a,k)-a;
	putchar(k);
	work(l1,mid-1,l2,l2+mid-l1-1);
	work(mid+1,r1,l2+mid-l1,r2-1);
}
int main(){
	scanf("%s%s",a,b);
	int len=strlen(a);
	work(0,len-1,0,len-1);
}
