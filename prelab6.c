#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
struct student {
	char name[26];
	int id;
	float gpa;
	char major[16];
	int credits;
};
int readLine(int fd, char line[], int max)
{
	int i = 0;
	char c;
	while (read(fd, &c, 1) == 1){
		if ( c == '\n')
			break;
		if ( i < max - 1 )
			line[i++] = c;
	}
	line[i] = '\0';
	return i;
}
void probation(int infd, int outfd)
{
	struct student s;
	char line[100];
	while (readLine(infd, line, sizeof(line)) > 0) {
		sscanf(line, "%25s %d %f %15s %d", 
				s.name, &s.id, &s.gpa, s.major, &s.credits);
		if (s.gpa < 2.0 && s.credits > 30)
			strcpy(s.major, "PROBATION");
		 write(outfd, &s, sizeof(s));
	}
}
int main(int argc, char *argv[])
{
	int infd, outfd, txtfd;
        struct student s;
        char buf[100];
	if (argc != 2){
		printf("Usage: %s inputfile\n", argv[0]);
		return 1;
	}
	infd = open(argv[1], O_RDONLY);
	if (infd == -1){
		perror("open input");
		return -1;
	}
	outfd = open("updated.dat", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (outfd == -1){
		perror("open updated.dat");
		return 1;
	}
	probation(infd, outfd);
	txtfd =  open("probation.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (txtfd == -1){
		perror("open probation.txt");
		return 1;
	}
	lseek(outfd, 0, SEEK_SET);
	while (read(outfd, &s, sizeof(s)) == sizeof(s)){
		sprintf(buf, "%-10s %5d %6.2f %5d %s\n",
				s.name, s.id, s.gpa, s.credits,
				strcmp(s.major, "PROBATION") == 0 ? "YES" : "NO");
		write(txtfd, buf, strlen(buf));
	}
	close(infd);
	close(outfd);
	close(txtfd);
	return 0;
}

