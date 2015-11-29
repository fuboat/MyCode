#include<cstdio>
#include<map>
#define MAXN 1000001
int oka[MAXN],oki[MAXN],maxm[MAXN],minm[MAXN],numa[MAXN],numi[MAXN];
int ans[MAXN][2],heada,headi,taila,taili;
void popa(){
	oka[numa[heada]]=0;
	heada++;
}
void popi(){
	oki[numi[headi]]=0;
	headi++;
}
void pusha(int i,int x){
	for(taila;taila>=heada;taila--)
		if(maxm[taila]>x)break;
		else oka[numa[taila]]=0;
	taila++;
	oka[i]=1;
	numa[taila]=i;
	maxm[taila]=x;
}
void pushi(int i,int x){
	for(taili;taili>=headi;taili--)
		if(minm[taili]<x)break;
		else oki[numi[taili]]=0;
	taili++;
	oki[i]=1;
	numi[taili]=i;
	minm[taili]=x;
}
int main(){
	int x,n,l,num=0;
	scanf("%d%d",&n,&l);
	for(int i=1;i<l;i++){
		scanf("%d",&x);
		pusha(i,x);
		pushi(i,x);
	}
	for(int i=l;i<=n;i++){
		num++;
		scanf("%d",&x);
		pusha(i,x);
		pushi(i,x);
		if(oka[i-l])popa();
		if(oki[i-l])popi();
		ans[num][0]=minm[headi];
		ans[num][1]=maxm[heada];
	}
	for(int i=1;i<=num;i++)
		printf("%d ",ans[i][0]);
	putchar('\n');
	for(int i=1;i<=num;i++)
		printf("%d ",ans[i][1]);
}
