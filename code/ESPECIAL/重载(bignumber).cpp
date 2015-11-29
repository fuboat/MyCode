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
	BIGNUM operator +(const BIGNUM & a)
	{
		BIGNUM c;
		c.len=max(len,a.len)+1;
		for (int i=0,x=0;i<c.len;++i)
		{
			c.s[i]=s[i]+a.s[i]+x;
			x=c.s[i]/10;
			c.s[i]=c.s[i]%10;
		}
		if (c.s[c.len-1]==0)--c.len;
		return c;	
	}
	BIGNUM operator +=(const BIGNUM & a)
	{
		*this =*this+a;
		return *this;
	}
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
	bool operator >(const BIGNUM & x) const { return x<*this;}
	bool operator <=(const BIGNUM & x) const { return !(x<*this);}
	bool operator >=(const BIGNUM & x) const { return !(*this<x);}
	bool operator ==(const BIGNUM & x) const { return !(x<*this||*this<x);}
	bool operator !=(const BIGNUM & x) const { return x<*this||*this<x;}
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
BIGNUM f[5001];
int main(){}
