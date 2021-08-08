#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 1e6 + 10;

int n;
char str[N];
int x, y;

int main(void)
{
	scanf("%d", &n);
	scanf("%s", str + 1);

	get_sa();
	get_height();

	SegmentTree::Build(1, 1, n);
