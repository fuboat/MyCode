#include<cstdio>
#include<cstring>
#include<iostream>
#include<cmath>
using namespace std;
const int MAXN=4000;
struct BIGNUM {
	int len,s[MAXN];
	BIGNUM ()
	{
		memset(s,0,sizeof(s)); 
		len=1;
	}
	BIGNUM operator =(const char* num)
	{
		len=strlen(num);
		for (int i=0;i<len;++i) s[i]=num[len-i-1]-'0';
		return *this;
	}
	BIGNUM operator =(const int num)
	{
		char a[MAXN];
		sprintf(a,"%d",num);
		*this = a;
		return *this;
	}
	BIGNUM (const int num){*this=num;}
	BIGNUM (const char * num){*this=num;}
	BIGNUM operator *(const BIGNUM & x)
	{
		BIGNUM c;
		c.len=len+x.len;
		for (int i=0;i<len;++i)
		{
			for (int j=0;j<x.len;++j)
			{
				c.s[i+j]+=s[i]*x.s[j];
				c.s[i+j+1]+=c.s[i+j]/10;
				c.s[i+j]%=10;
			}
		}
		if (c.s[c.len-1]==0)--c.len;
		return c;
	}
	BIGNUM operator *=(const BIGNUM & a)
	{
		*this =*this * a;
		return *this;
	}
	bool operator <(const BIGNUM & x) const 
	{
		if (len != x.len) return len<x.len;
		for (int i=len-1;i>=0;--i)
			if (s[i]!= x.s[i]) return s[i]<x.s[i];
		return false;
	}
};
ostream& operator <<(ostream &out,const BIGNUM& x)
{
	for (int i=x.len-1;i>=0;--i)
		cout<<x.s[i];
	return out;
}
istream& operator >>(istream &in,BIGNUM &x)
{
	char num[MAXN];
	in>>num;
	x=num;
	return in;
}
int main(){
	int a,b;
	scanf("%d%d",&a,&b);
	BIGNUM a0=1,b0=1;
	for(int i=1;i<=b;i++)a0*=a;
	for(int i=1;i<=a;i++)b0*=b;
	BIGNUM ans;
	ans.len=max(a0.len,b0.len);
	if(a0<b0){
		printf("-");
		BIGNUM c=a0;
		a0=b0;
		b0=c;
	}
	for(int i=0;i<ans.len;i++){
		if(a0.s[i]<b0.s[i]){
			a0.s[i]+=10;
			a0.s[i+1]-=1;
		}
		ans.s[i]=a0.s[i]-b0.s[i];
	}
	if (ans.s[ans.len-1]==0)--ans.len;
	cout<<ans;
}
