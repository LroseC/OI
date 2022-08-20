#include <cstdio>
#include <cstdlib>

using i32 = int32_t;
using i64 = int64_t;

int main(void)
{
	FILE* out = fopen("graph.out", "r");
	FILE* ans = fopen("graph.ans", "r");
	i32 x, y;
	int line = 0;
	while (~fscanf(out, "%d", &x)) {
		line += 1;
		fscanf(ans, "%d", &y);
		if (x != y) {
			printf("WA on line %d\n", line);
			return -1;
		}
	}
	return 0;
}
