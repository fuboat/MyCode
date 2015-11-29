#include<cstdio>
#define MAXH 101
#define MAXW 101
int ans,sum;
int main(){
	int h,w;
	while(scanf("%d%d",&h,&w)==2&&h&&w){
		for(int i=1;i<=h;i++)
			for(int j=1;j<=w;j++){
				char x=getchar();
				while(x==' '||x=='\n')x=getchar();
				if(x=='\\'||x=='/')sum++,ans+=1;
				else if(sum&1)ans+=2;
			}
		printf("%d\n",ans/2);
	}
}
