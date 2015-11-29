#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#define INF 999999999
#define MAXN 1000000
#define MAX(a,b,c,d) max(max(a,b),max(c,d))
#define For(i,x,y) for(int i=(x);i<=(y);i++)
using namespace std;
int tot,a[4],pr[1000000],q[2][2],sum,n,ys(),gz();
bool flag[1000001];
void cnt(int);
int main(){
	For(i, 2, MAXN){
        if(!flag[i]) pr[tot ++] = i;
        for(int j = 0;i * pr[j] <= MAXN;j ++){
            flag[i * pr[j]] = true;
            if (i % pr[j] == 0)
                break;
        }
    }
	scanf("%d", &n);
	while(n--){
		scanf("%d%d%d%d", &a[0], &a[1], &a[2], &a[3]);
		printf("%d\n", divide());
	}
}
int divide(){
	sum = 1;
	for(int i = 0; pr[i] <= sqrt(MAX(a[1],a[2],a[3],a[4])) && sum; i ++)
		cnt(pr[i]);
	int temp[4];
	For(i, 0, 3) temp[i] = a[i];
	sort(temp, temp+4);
	For(i, 0, 3) cnt(temp[i]);
	return sum;
}
int cal(){
	int begin = max(q[0][0], q[1][0]);
	int end = min(q[0][1], q[1][1]);
	if(end < begin)return 0;
	else return end - begin + 1;
}
void cnt(int x){
	if(x == 1)return;
	int n[4] = {0};
	For(i, 0, 3) while(a[i] % x == 0) a[i] /= x,n[i] ++;
	if((n[0] || n[1] || n[2] || n[3])){
		if(n[0] > n[1])
			 q[0][0] = q[0][1] = n[1];
		else q[0][0] = n[0],q[0][1] = INF;
		if(n[2] == n[3])
			 q[1][0] = 0, q[1][1]=n[2];
		else q[1][0] = q[1][1] = n[3];
		sum *= cal();
	}
}
