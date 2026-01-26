#include <vector>
#include <cstdio>
#include <cstdlib>


int main(int argc, char* argv[]) {
	if (argc != 2) {
		fprintf(stderr, "Usage: %s <size>\n", argv[0]);
		exit(1);
	}

	std::vector<int> v1{20, 30, 12, 3, 45, 11, 1, 0};

	for (std::vector<int>::iterator it{v1.begin()}; it != v1.end(); ++it) {
		printf("%d\n", *it);
	}

	exit(0);
}

