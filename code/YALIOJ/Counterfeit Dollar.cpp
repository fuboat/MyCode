#include<cstdio>
#include<cstring>
bool bug[1000];
int check[4][1000],debug[4];
int main(){
	int n;
	scanf("%d",&n);
	while(n--){
		int sum=0;
		for(int w=1;w<=3;w++){
			char x[12],y[12],z[12];
			scanf("%s%s%s",&x,&y,&z);
			int lenx=strlen(x),leny=strlen(y);
			if(z[0]=='e'){
				for(int i=0;i<lenx;i++)
					bug[x[i]]=1;
				for(int i=0;i<leny;i++)
					bug[y[i]]=1;
			}
			else if(z[0]=='u'){
				debug[w]=1;
				for(int i=0;i<lenx;i++)
					check[w][x[i]]=2;
				for(int i=0;i<leny;i++)
					check[w][y[i]]=1;
			}
			else if(z[0]=='d'){
				debug[w]=1;
				for(int i=0;i<lenx;i++)
					check[w][x[i]]=1;
				for(int i=0;i<leny;i++)
					check[w][y[i]]=2;
			}
		}
		for(int i='A';i<='L';i++){
			int flag=0;
			if(bug[i])continue;
			for(int j=1;j<=3;j++)
				if(debug[j])
					if(!check[j][i]){flag=0;break;}
					else if(flag&&flag!=check[j][i]){
						flag=0;
						break;
					}
					else flag=check[j][i];
			if(flag){
				putchar(i);
				if(flag==1)printf(" is the counterfeit coin and it is light.\n");
				else printf(" is the counterfeit coin and it is heavy.\n");
				break;
			}
		}
		memset(bug,0,sizeof(bug));
		memset(debug,0,sizeof(debug));
		memset(check,0,sizeof(check));
	}
}
