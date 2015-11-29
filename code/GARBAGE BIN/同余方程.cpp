#include<iostream>
#include<cstdio>
using namespace std;
void gcd(int a,int b,int &d,int& x,int& y){
	if(!b){x=1,y=0,d=a;return;}
	gcd(b,a%b,d,y,x);y-=x*(a/b);
}
int main(){
	int a,b,x,y;
	scanf("%d%d",&a,&b);
	int GCD;
	gcd(a,-b,GCD,x,y);
	if(x<0)x+=GCD;
	printf("%d\n",b-x);
}
