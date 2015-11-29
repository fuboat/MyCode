#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
using namespace std;
struct symbol{int x,len;char s[20];};
int a[]={4,2,5,6,1,4,5,6,7,2,3,4,8,9,3,1,2,6,8,9,2,6,3,2,5,7};
bool cmp(symbol a,symbol b){
	if(a.x>b.x)return 1;
	if(a.x<b.x)return 0;
	if(a.len>b.len)return 1;
	if(a.len<b.len)return 0;
	for(int i=0;i<a.len;i++)
		if(a.s[i]>b.s[i])return 1;
		else if(a.s[i]<b.s[i])return 0;
	return 0;
}
symbol t[50000+1];
int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		t[i].x=0;
		scanf("%s",t[i].s);
		int w=strlen(t[i].s);
		t[i].len=w;
		for(int j=0;j<w;j++)
		{	
			int z=t[i].s[j]-'a';
			t[i].x+=a[z];
		}
	}
	sort(t+1,t+n+1,cmp);
	for(int i=1;i<=m;i++)
		printf("%s %d\n",t[i].s,t[i].x);
	return 0;
}
