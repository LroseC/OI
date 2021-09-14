#include <bits/stdc++.h>

const int M = 21;
const int N = 1e5 + 10;

int n , m;
int a[N];
int num[M];
int sum[N][M];
int f[(1 << M)];

int main () {
	scanf("%d %d" , &n , &m);
	for(int i = 1 ;i <= n ; ++ i) scanf("%d" , a + i);
	for (int i = 1; i <= n; ++i) --a[i];
	for(int i = 1 ; i <= n; ++ i) {
		num[a[i]] ++;
		for(int j = 0 ; j < m ; ++ j) sum[i][j] = sum[i - 1][j];
		sum[i][a[i]] ++;
	}
	memset(f , 0x3f , sizeof(f)); f[0] = 0;
	for(int i = 1 ; i < (1 << m) ; i ++) {
		int lenth = 0;
		for(int j = 0 ; j < m ; ++ j) if(i & (1 << j)) lenth += num[j];
		for(int j = 0 ; j < m ; ++ j) {
			if(i & (1 << j)) {
				f[i] = std::min(f[i] , 
				f[i ^ (1 << j)] + num[j] - sum[lenth][j] + sum[lenth - num[j]][j]);
			}
		}		
	}
	printf("%d\n" , f[(1 << m) - 1]);
	return 0;
}
