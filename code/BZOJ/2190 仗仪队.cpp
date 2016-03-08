// BZOJ #2190
// Fuboat
#include <cstdio>
#include <iostream>
#include <cstring>
const int MAXN = 40000 + 1000;
int pri[MAXN], phi[MAXN], totprime;
bool vis[MAXN];
void GetPhi(int n)
{
    int now;
     
    for(int i = 2; i <= n; i ++) {
        if(!vis[i]) {
            phi[i] = i - 1;
            pri[++ totprime] = i;
        }
         
        for(int j = 1; i * pri[j] <= n; j ++) {
            now = i * pri[j];
            vis[now] = true;
            if(i % pri[j] == 0) {
                phi[now] = phi[i] * pri[j];
                break;
            } else
                phi[now] = phi[i] * (pri[j] - 1);
        }
    }
}
 
int main()
{
    int n, tot = 0;
    scanf("%d", &n);
    GetPhi(n);
    for(int i = 1; i < n; i ++)
        tot += phi[i];
    printf("%d\n", tot * 2 + 3);
}
