#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include "minishell.h"
#include <stdio.h> // librearia de test
#include <string.h> // libreria de tt

int main(void)
{
    int pid[5];
    int i;

    i = 0;
    while (i < 5)
    { 
        pid = fork();
		if (pid == 0)
		{
			printf("hola %d\n", i);
			exit (-1);
		}
		else
			waitpid(pid, NULL, 0);
        i++;
    }
    return (0);
}