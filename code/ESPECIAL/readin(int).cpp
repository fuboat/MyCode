#include<cstdio>
int readin(){
	int x = 0;bool flag = 0;char c = 0;
	while(c = getchar()){
		if(c == '-'){
			return -readin();
		}
		if(c >= '0' && c <= '9'){
			x = x * 10 + c - '0';
			flag = 1;
		}
		else if(flag) return x;
	}
}
int main(){
	int n = readin();
}
