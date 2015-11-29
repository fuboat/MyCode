#include<iostream>
#include<cstdio>
#include<cstring> 
#include<cmath>
using namespace std;
int primes[10000],flag[100000],totPrimes;
void eratosthenes_sieve(int n)
{
    totPrimes = 0;
    memset(flag, 0, sizeof(flag));

    int sqrtn = sqrt(n + 0.5);
    for (int i = 2; i <= sqrtn; i++) {
        if (!flag[i]) {
            primes[totPrimes++] = i;
            for (int j = i * i; j <= n; j += i) {
                flag[j] = true;
            }
        }
    }
    for (int i = sqrtn + 1; i <= n; i++) {
        if (!flag[i])
            primes[++totPrimes] = i;
    }
}
int main(){
	eratosthenes_sieve(30000);
	for(int i=1;i<=totPrimes;i++)
	printf("%d ",primes[i]);
}
