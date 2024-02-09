#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <pthread.h>

#define PATH "/sys/kernel/debug/fortytwo/"
#define ID_PATH      PATH "id"
#define JIFFIES_PATH PATH "jiffies"
#define FOO_PATH     PATH "foo"

void *ft_read(void *arg)
{
	(void)arg;

	char buf[64];
	for (int i = 0; i < 5000; i++) {
		int fd = open(FOO_PATH, O_RDONLY);
		read(fd, buf, 64);
		if (strcmp(buf, "1234") && strcmp(buf, "4321")) {
			printf("ERROR INVALID STRING /!\\\n");
		}
	}
	return NULL;
}

int main(void)
{
	char buf[64];
	bzero(buf, 64);
	int fd = open(ID_PATH, O_RDWR);

	printf("TESTING BIG READ FOR ID\n");

	printf("return value : %ld from read(fd, buf, 64)\n", read(fd, buf, 64));
	printf("buffer read  : %s\n", buf);

	bzero(buf, 64);

	printf("\nTESTING MULTIPLES SMALL READ FOR ID\n");
	fd = open(ID_PATH, O_RDWR);
	printf("return value : %ld from read(fd, buf, 1)\n", read(fd, buf, 1));
	printf("buffer read  : %s\n", buf);
	bzero(buf, 64);

	printf("return value : %ld from read(fd, buf, 3)\n", read(fd, buf, 3));
	printf("buffer read  : %s\n", buf);
	bzero(buf, 64);

	printf("return value : %ld from read(fd, buf, 64)\n", read(fd, buf, 64));
	printf("buffer read  : %s\n", buf);
	bzero(buf, 64);

	printf("\nTESTING WRITE FOR ID\n");
	fd = open(ID_PATH, O_RDWR);
	printf("return value : % ld from write(fd, \"tnaton\", 6)\n", write(fd, "tnaton", 6));
	printf("return value : %ld from write(fd, \"tnato\", 5)\n", write(fd, "tnato", 5));
	printf("return value : %ld from write(fd, \"tnaton\", 5)\n", write(fd, "tnaton", 5));
	printf("return value : %ld from write(fd, \"tnaton\\n\", 6)\n", write(fd, "tnaton\n", 6));


	printf("TESTING READ JIFFIES\n");
	fd = open(JIFFIES_PATH, O_RDONLY);

	printf("return value : %ld from read(fd, buf, 64)\n", read(fd, buf, 64));
	printf("buffer read  : %s\n", buf);

	fd = open(JIFFIES_PATH, O_RDONLY);
	usleep(1000);
	printf("return value : %ld from read(fd, buf, 64)\n", read(fd, buf, 64));
	printf("buffer read  : %s\n", buf);

	pthread_t reader;
	pthread_create(&reader, NULL, &ft_read, NULL);
	for (int i = 0; i < 5000; i++) {
		fd = open(FOO_PATH, O_WRONLY);
		if (i % 2) {
			write(fd, "1234", 4);
		} else {
			write(fd, "4321", 4);
		}
	}
	pthread_join(reader, NULL);

}
