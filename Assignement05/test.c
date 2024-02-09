#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(void) {
	char buf[64];
	bzero(buf, 64);
	int fd = open("/dev/fortytwo", O_RDWR);

	printf("TESTING BIG READ\n");

	printf("return value : %ld from read(fd, buf, 64)\n", read(fd, buf, 64));
	printf("buffer read  : %s\n", buf);

	bzero(buf, 64);

	printf("\nTESTING MULTIPLES SMALL READ\n");
	fd = open("/dev/fortytwo", O_RDWR);
	printf("return value : %ld from read(fd, buf, 1)\n", read(fd, buf, 1));
	printf("buffer read  : %s\n", buf);
	bzero(buf, 64);

	printf("return value : %ld from read(fd, buf, 3)\n", read(fd, buf, 3));
	printf("buffer read  : %s\n", buf);
	bzero(buf, 64);

	printf("return value : %ld from read(fd, buf, 64)\n", read(fd, buf, 64));
	printf("buffer read  : %s\n", buf);
	bzero(buf, 64);

	printf("\nTESTING WRITE\n");
	fd = open("/dev/fortytwo", O_RDWR);
	printf("return value : % ld from write(fd, \"tnaton\", 6)\n", write(fd, "tnaton", 6));
	printf("return value : %ld from write(fd, \"tnato\", 5)\n", write(fd, "tnato", 5));
	printf("return value : %ld from write(fd, \"tnaton\", 5)\n", write(fd, "tnaton", 5));
	printf("return value : %ld from write(fd, \"tnaton\\n\", 6)\n", write(fd, "tnaton\n", 6));
}
