#include<cstdio>
#define MAXN 100 + 10
#define INF 999999999
#define in(c,x,y) (x<=c&&c<=y)
int a[MAXN][3],f[MAXN][MAXN][3],ans[MAXN];
int min(int x,int y){
	if(x<y)return x;
	return y;
}
int max(int x,int y){
	if(x>y)return x;
	return y;
}
int Read(){
	int x=0;char c=0;bool flag=0;
	while(c=getchar()){
		if('0'<=c&&'9'>=c)x=x*10+c-'0',flag=1;
		else if(flag)return x;
	}
}
int ok(int x,int X,int y,int Y){
	int a1,a2=a1=INF,b2,b1=b2=-INF;
	for(int i=0;i<3;i++){
		if(i!=X)a1=min(a1,a[x][i]),b1=max(b1,a[x][i]);
		if(i!=Y)a2=min(a2,a[y][i]),b2=max(b2,a[y][i]);
	}
	if(a1<=a2&&b1<=b2)return 1;
	return 0;
}

int main(){
	int n=Read(),m=Read();
	for(int i=1;i<=n;i++){
		a[i][0]=Read(),a[i][1]=Read(),a[i][2]=Read();
	}
	for(int k=1;k<=n;k++)
		for(int i=k;i<=n;i++)
			for(int u=0;u<3;u++){
				for(int j=k;j<i;j++)
					for(int d=0;d<3;d++)
						if(ok(i,u,j,d))
							f[k][i][u]=max(f[k][i][u],f[k][j][d]);
				f[k][i][u]+=a[i][u];
		}
	for(int k=1;k<=n;k++)
		for(int i=k;i<=n;i++){
			f[k][i][0]=max(max(f[k][i][0],f[k][i-1][0]),max(f[k][i-1][1],f[k][i-1][2]));
			f[k][i][1]=max(max(f[k][i][1],f[k][i-1][0]),max(f[k][i-1][1],f[k][i-1][2]));
			f[k][i][2]=max(max(f[k][i][2],f[k][i-1][0]),max(f[k][i-1][1],f[k][i-1][2]));
			//std::cout<<f[k][i][0]<<' '<<f[k][i][1]<<' '<<f[k][i][2]<<std::endl;
		}
	for(int i=1;i<=n;i++)
		ans[i]=max(max(f[1][i][0],f[1][i][1]),max(f[1][i][2],ans[i]));
	for(int k=2;k<=m;k++)
		for(int i=n;i>=k;i--)
			for(int j=k-1;j<i;j++)
				ans[i]=max(ans[i],ans[j]+max(f[j+1][i][0],max(f[j+1][i][1],f[j+1][i][2])));
	printf("%d\n",ans[n]);
	return 0;
}

		
