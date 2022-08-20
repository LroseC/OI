#include <cstdio>
#include <cstdint>
#include <cstdlib>

using i32 = int32_t;
using i64 = int32_t;

int main(void)
{
	system("g++ rand.cpp -o rand");
	system("g++ graph.cpp -O2 -DDEBUG -o main -fsanitize=undefined,address");
	system("g++ std.cpp -O2 -o brute");
	for (int i = 1; i <= 1000; ++i) {
		fprintf(stderr, "Test #%d\n", i);
		system("./rand > test.in");
		system("./main < test.in > test.out");
		system("./brute < test.in > test.ans");
		if (system("diff test.out test.ans")) {
			fprintf(stderr, "WA\n");
			return -1;
		}
		fprintf(stderr, "Accepted.\n");
	}
	return 0;
}
