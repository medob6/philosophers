// you are free to play her

// #include "philo_bonus.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <semaphore.h>

void do_task(const char *task, sem_t *sem)
{
	sem_wait(sem); // decrement 
	printf("PID %d is doing: %s\n", getpid(), task);
	sleep(1);
	sem_post(sem); // increament
	exit(0);
}

int main(void)
{
	sem_t *sem = sem_open("/task_sem", O_CREAT | O_EXCL, 0644, 1); // we gave it a path to make it a shared knowen space in mem
	if (sem == SEM_FAILED)
	{
		perror("sem_open");
		exit(1);
	}

	pid_t pids[4];
	const char *tasks[] = {"Add", "Subtract", "Multiply", "Add"};

	for (int i = 0; i < 4; i++)
	{
		pids[i] = fork();
		if (pids[i] == 0)
			do_task(tasks[i], sem);
	}

	for (int i = 0; i < 4; i++)
		waitpid(pids[i], NULL, 0);

	sem_close(sem); // close 
	sem_unlink("/task_sem"); //remove

	return 0;
}
