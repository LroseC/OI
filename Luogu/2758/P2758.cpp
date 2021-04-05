#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
#define reg register
#define ll long long
#define ull unsigned long long


char str1[2010],str2[2010];
int f[2010][2010],ans;


int main()
{
	scanf("%s%s",str1 + 1,str2 + 1);
	reg int n = strlen(str1 + 1);
	reg int m = strlen(str2 + 1);
	for (reg int i = 1; i <= n; ++i)
		f[i][0] = i;
		for (reg int j = 1; j <= m; ++j){
			f[i][j] = min(f[i - 1][j],f[i][j - 1]);
			if (str1[i] != str2[j])
				++f[i][j];
		}

	printf("%d\n",f[n][m]);
	return 0;
}
