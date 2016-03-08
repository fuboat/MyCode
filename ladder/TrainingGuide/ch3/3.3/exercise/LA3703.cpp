/*
	FROM: UVaLive
	TASK: 3703
	ID: fuboat
	DATASTRUCTURE: AC-Trie
	ALGORITHM: Default
*/
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <map>
using namespace std;

#define MSET(a, x) memset(a, x, sizeof(a))
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define Rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
#define LL long long
template <typename T> bool chkmin(T &x, T y){return y < x? (x = y, true) : false;}
template <typename T> bool chkmax(T &x, T y){return y > x? (x = y, true) : false;}

const int MAXNODE = 2000000, MAXS = 11, MAXL = 50;
map<string, int>P;
map<int ,string>fP;
char s1[100], s2[100];

struct Trie{
	char tmp[50];
	int ch[MAXNODE][MAXS];
	int val[MAXNODE];
	int ss[MAXNODE];
	bool ok[MAXNODE];
	int sz;
	int cnt;
	inline void clear()
	{
		MSET(ch, 0); MSET(val, 0); MSET(ss, 0); MSET(tmp, 0); MSET(ok, 0);
		sz = 1; cnt = 0;
	}
	inline int idx(char c){ return c - '0'; }
	void update(int o, int x)
	{
		if(ss[o] == -1) return;
		if(ss[o] == 0) ss[o] = x;
		else if(ss[o] != x) ss[o] = -1;
	}
	void insert(int len, int v)
	{
		int u = 0;
		REP(i, 0, len - 1){
			int c = idx(s1[i]);
			if(!ch[u][c]) ch[u][c] = ++ sz;
			u = ch[u][c];
			if(val[u]) return ;
		}
		val[u] = v;
		u = 0;
		update(0, v);
		REP(i, 0, len - 1){
			int c = idx(s1[i]);
			u = ch[u][c];
			update(u, v);
		}
	}
	void BF_insert(int v)
	{
		int len1 = strlen(s1), len2 = strlen(s2);
		insert(len1, v);
		if(strcmp(s1, s2) == 0){
			return ;
		}
		else if(len1 == 1){
			int l = s1[0], r = s2[0];
			REP(i, l, r){
				s1[0] = i;
				insert(1, v);
			}
			return ;
		}
		while(s1[len1 - 1] == '0' &&  s2[len2 - 1] == '9' && len1 > 1) len1 --, len2 --;
		int pos = len1 - len2, kk = 0;
		while(s1[pos] == s2[kk]) pos ++, kk ++;
		int end = len1;
		while(end > 1 && s1[end - 1] == '0') end --;
		char sd = s1[len1 - 1];
		for(int i = pos, j = kk; i < end; i ++, j ++){
			int l = s1[i] + 1, r = '9';
			if(i == pos) r = s2[j] - 1;
			if(i == end - 1) l --;
			char tmp = s1[i];
			REP(z, l, r){
				s1[i] = z;
				insert(i + 1, v);
			}
			s1[i] = l - 1;
		}
		s1[pos] = s2[kk];
		if(pos + 1 != len1) for(int i = pos + 1, j = kk + 1; i < len1; i ++, j ++){
			int l = '0', r = s2[j] - 1;
			if(i == len1 - 1) r ++;
			if(r != '9') REP(z, l, r){
				s1[i] = z;
				insert(i + 1, v);
			}else insert(i, v);
			s1[i] = s2[j];
		}else{
			int l = sd, r = s2[len2 - 1];
			REP(z, l, r){
				s1[pos] = z;
				insert(len1, v);
			}
		}
		for(int i = pos, j = kk; i < len1; i ++, j ++)
			s1[i] = s2[j];
		insert(len1, v);
	}
	
	void dfs(int u, int d)
	{
		REP(i, 0, 9)
		if(ch[u][i]) dfs(ch[u][i], d + 1);
		if(ss[u] != -1){
			if(val[u]){
				ok[u] = 1;
				return ;
			}
			else{
				bool flag = 1;
				REP(i, 0, 9) if(!ch[u][i] || !ok[ch[u][i]]) flag = 0;
				if(flag && u != 0) val[u] = val[ch[u][0]];
			}
			if(val[u]){
				ok[u] = 1;
				return;
			}
		}
	}
	
	void maintain(int u, int d)
	{
		int v, w;
		string now;
		if(val[u]){
			now = fP[w = val[u]];
			if(ss[u] != -1){
				if(now != "invalid") cnt ++;
				return ;
			}else{
				REP(i, 0, 9)
				if(val[v = ch[u][i]] == 0){
					if(v == 0) v = ch[u][i] = ++ sz;
					update(v, val[v] = w);
				}
			}
		}
		REP(i, 0, 9) if(v = ch[u][i])
			maintain(v, d + 1);
	}
	
	void print(int u, int d)
	{
		int v, w;
		string now;
		if(val[u]){
			now = fP[w = val[u]];
			if(ss[u] != -1){
				if(now != "invalid"){
					REP(i, 0, d - 1) putchar(tmp[i]);
					putchar(' ');
					printf("%s\n", now.c_str());
				}
				return ;
			}else{
				REP(i, 0, 9)
				if(val[v = ch[u][i]] == 0){
					if(v == 0) v = ch[u][i] = ++ sz;
					val[v] = w;
					update(v, w);
				}
			}
		}
		
		REP(i, 0, 9) if(v = ch[u][i]){
			tmp[d] = i + '0';
			print(v, d + 1);
		}
	}
}t;
int n;
string word;

int main()
{
	bool flag = 0;
	while(scanf("%d", &n) == 1 && n){
		if(flag) puts("");
		else flag = true;
		P.clear();
		fP.clear();
		t.clear();
		int sum = 0;
		REP(i, 1, n){
			scanf("%s%s%s", s1, s2, s2);
			cin >> word;
			if(!P.count(word)){
				sum ++;
				P[word] = sum;
				fP[sum] = word;
			}
			t.BF_insert(P[word]);
		}
		t.dfs(0, 0);
		t.maintain(0, 0);
		printf("%d\n", t.cnt);
		t.print(0, 0);
	}
}
