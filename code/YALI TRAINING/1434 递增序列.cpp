#include<iostream>
#include<cstdio>
#include<cstring> 
#define LEN 500
using namespace std;
char s[LEN];
int a[LEN],ans[LEN][LEN];
int maxx,true_len,cmp_len;
int l[LEN][LEN],last[LEN][LEN];
void solve(int b,int e){
	int next=last[b][e];
	if(next){
		solve(next,b-1);
		putchar(',');
	}
	for(int i=b;i<=e;i++)
		printf("%d",a[i]);
}
bool cmp(int b,int t){
	cmp_len=l[t][b-1];
	while(!a[t])t++;
	if(cmp_len<true_len)return 1;
	if(cmp_len>true_len)return 0;
	while(!a[b])b++;
	for(int i=0;i<true_len;i++)
		if(a[b+i]>a[t+i])return 1;
		else if(a[b+i]<a[t+i])return 0;
	return 0;
}
int main(){
	scanf("%s",s);
	int len=strlen(s);
	for(int i=0;i<len;i++)
		a[i+1]=s[i]-'0';
	for(int i=1;i<=len;i++)
		ans[1][i]=1;
	for(int i=1;i<=len;i++)
		for(int j=i;j<=len;j++){
			l[i][j]=j-i+1;
			int i0=i;
			while(!a[i0]){
				l[i][j]--;
				i0++;
				if(!l[i][j])break;
			}
		}
	for(int i=2;i<=len;i++)
		for(int j=i;j<=len;j++){
			if(!l[i][j])continue;
			true_len=l[i][j];
			for(int k=i-1;k>=1;k--)
				if(k<=0)break;
				else if(ans[k][i-1]&&cmp(i,k)&&ans[k][i-1]>ans[i][j])
					ans[i][j]=ans[k][i-1],last[i][j]=k;
			if(ans[i][j])ans[i][j]++;
		}
	int ANS=0;
	for(int i=1;i<=len;i++)
		if(ans[i][len]>=maxx)
			maxx=ans[i][len],ANS=i;
	printf("%d\n",ans[ANS][len]);
	solve(ANS,len);
} 
				
