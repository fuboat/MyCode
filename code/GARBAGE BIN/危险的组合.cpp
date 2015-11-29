#include<iostream>
#include<cstdio>
using namespace std;
int n;
int main(){
	for(n=3;n<=20;n++)
	printf("%d ",(1<<(n-4))*(n-1));
}
