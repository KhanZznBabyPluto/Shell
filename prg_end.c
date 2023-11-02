#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <time.h>

int main() {
	int c;
	while (read(0, &c, sizeof(int))) {
		c++;
		fprintf(stderr, "%d\n", c);
	}
	return 0;
}
