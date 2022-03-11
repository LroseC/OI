#include <cstdio>
#include <cstdlib>

using namespace std;

const int T = 25, SubtaskCnt = 4;
const char name[] = "test";
const int Subtask[] = {5, 10, 15, 25};
const int Score[] = {20, 20, 20, 40};
const int n[] = {10, 100, 1, 13};
const int m[] = {1, 2, 3, 4};
const int TimeLimit = 2, MemoryLimit = 512;

int main(void)
{
	system("g++ std.cpp -o std -O2");
	system("g++ rand.cpp -o rand -O2");
	fprintf(stderr, "compile end.\n\n");
	for (int i = 1, sub = 0; i <= T; ++i) {
		FILE* tmp = fopen(".tmp.tmp", "w");

		fprintf(stderr, "case %02d: begin.\n", i);

		char rd[1024], std[1024];
		if (i > Subtask[sub]) ++sub;
		fprintf(tmp, "%d\n", n[sub]);
		fclose(tmp);
		sprintf(rd, "./rand > %s%02d.in < .tmp.tmp", name, i);
		if (system(rd)) {
			fprintf(stderr, "\ncase%02d: rand.cpp error.\n", i);
			return -1;
		}
		fprintf(stderr, "case %02d: input file finished.\n", i);

		sprintf(std, "./std < %s%02d.in > %s%02d.out", name, i, name, i);
		if (system(std)) {
			fprintf(stderr, "\ncase%02d: std.cpp error.\n", i);
			return -1;
		}
		fprintf(stderr, "case %02d: output file finished.\n", i);

		fprintf(stderr, "\n");
	}

	char cfg[1024];
	sprintf(cfg, "problem.conf", name);
	FILE* config = fopen(cfg, "w");
	fprintf(config, "use_builtin_judger on\nuse_builtin_checker ncmp\n");
	fprintf(config, "n_tests %d\n", T);
	fprintf(config, "n_ex_tests 0\nn_sample_tests 0\n");
	fprintf(config, "n_subtasks %d\n", SubtaskCnt);
	for (int i = 0; i < SubtaskCnt; ++i) {
		fprintf(config, "subtask_end_%d %d\n", i + 1, Subtask[i]);
		fprintf(config, "subtask_score_%d %d\n", i + 1, Score[i]);
	}
	fprintf(config, "input_pre %s\n", name);
	fprintf(config, "input_suf in\n");
	fprintf(config, "output_pre %s\n", name);
	fprintf(config, "output_suf out\n");
	fprintf(config, "time_limit %d\n", TimeLimit);
	fprintf(config, "memory_limit %d\n", MemoryLimit);

	remove(".tmp.tmp");
	remove("std");
	remove("rand");
	return 0;
}
