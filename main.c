#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>

static void sighandler(int signo) {
	if (signo == SIGINT) {
		int file = open("exitNote.txt", O_CREAT | O_APPEND | O_RDWR, 0766);
		char message[] = "Exited: SIGINT\n";
		write(file, message, strlen(message));
		close(file);
		exit(0);
	}
	if (signo == SIGUSR1)
		printf("PPID: %d\n", getppid());

}

int main() {
	signal(SIGINT, sighandler);
	signal(SIGUSR1, sighandler);

	while (1) {
		printf("PID: %d\n", getpid());
		sleep(1);
	}

	return 0;
}
