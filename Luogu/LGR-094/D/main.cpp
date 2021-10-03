#include <cstdio>

using namespace std;

const int N = 5010;

int n;
bool is_chain = 1;
int chain[N], chaincnt;
int degree[N];

int main(void)
{
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &degree[i]);
		if (degree[i] != 1 && degree[i] != 2) is_chain = 0;
		if (degree[i] == 1)
			chain[++chaincnt] = i;
	}
	if (chaincnt != 2) is_chain = 0;
	
	if (n == 1) {
		printf("! 0\n");
		fflush(stdout);
	}
	else if (is_chain) {
		printf("dis %d %d\n", chain[1], chain[2]);
		fflush(stdout);
		int tmp; scanf("%d", &tmp);
		printf("! %d\n", tmp);
		fflush(stdout);
	}
	return 0;
}