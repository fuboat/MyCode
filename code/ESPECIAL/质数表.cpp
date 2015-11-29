#include <cstdio>

const int MAXN = 1000000 + 1,MAXM = 100001;
int ok[MAXN],pri[MAXM],num;
void prime(int n){
	for(int i = 2;i <= n;i ++){
		if(!ok[i])pri[++num] = i;
		for(int j = 1;i*pri[j] <= n;j ++){
			ok[i*pri[j]] = 1;
			if(i%pri[j] == 0) break;
		}
	}
}

void print(){
	for(int i = 1;i <= num;i ++)
		printf("%d ",pri[i]);
}

int main(){
	int n;
	scanf("%d",&n);
	prime(n);
	print();
}
