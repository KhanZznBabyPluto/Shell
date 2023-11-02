#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <time.h>

int main() {
	int s;
	srand(time(NULL));
	for (int i = 0; i < 5; i++) {
		s = rand() % 100;
		fprintf(stderr, "\n%d -> ", s);
		write(1, &s, sizeof(int));
		sleep(1);
	}
	return 0;
}
