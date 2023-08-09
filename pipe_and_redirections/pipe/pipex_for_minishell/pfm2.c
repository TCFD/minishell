#include "../../../minishell.h"


// BRUT TEST ---------------

/* void	brut_test(char **elmt)
{
	t_cmd_and_opt	cmdopt;
	int				pipes1[2], pipes2[2];
	int				pids1, pids2, pids3;
	int				idx;

	idx = 0;
	if (pipe(pipes1) < 0)
		return ;
	pids1 = fork();
	if (pids1 < 0)
		return ;
	if (pids1 == 0)
	{
		close(pipes1[0]);
		dup2(pipes1[1], STDOUT_FILENO);
		close(pipes1[1]);	
		create_command(elmt[idx], &cmdopt);
		exec(&cmdopt);
	}
	if (pipe(pipes2) < 0)
		return ;
	idx = 1;
	pids2 = fork();
	if (pids2 < 0)
		return ;
	if (pids2 == 0)
	{
		close(pipes1[1]);
		close(pipes2[0]);	
		
		dup2(pipes1[0], STDIN_FILENO);
		close(pipes1[0]);
		
		dup2(pipes2[1], STDOUT_FILENO);
		close(pipes2[1]);
		
		create_command(elmt[idx], &cmdopt);
		exec(&cmdopt);
	}
	
	idx = 2;
	pids3 = fork();
	if (pids3 < 0)
		return ;
	if (pids3 == 0)
	{
		close(pipes1[0]);
		close(pipes1[1]);
		close(pipes2[1]);
		
		dup2(pipes2[0], STDIN_FILENO);
		close(pipes2[0]);
		
		create_command(elmt[idx], &cmdopt);
		exec(&cmdopt);
	}


	close(pipes1[0]);
	close(pipes1[1]);
	close(pipes2[0]);
	close(pipes2[1]);
	waitpid(pids1, NULL, 0);
	waitpid(pids2, NULL, 0);
	waitpid(pids3, NULL, 0);
	return ;

}
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int pipe1[2], pipe2[2];
    pid_t pid1, pid2;

    // Création du premier tube
    if (pipe(pipe1) == -1) {
        perror("Erreur lors de la création du tube 1");
        exit(EXIT_FAILURE);
    }

    // Fork du premier processus
    pid1 = fork();

    if (pid1 < 0) {
        perror("Erreur lors du premier fork");
        exit(EXIT_FAILURE);
    }

    if (pid1 == 0) {
        // Code du premier processus fils (cat)
        close(pipe1[0]);  // Ferme l'extrémité de lecture du tube 1

        // Redirection de la sortie standard vers l'extrémité d'écriture du tube 1
        dup2(pipe1[1], STDOUT_FILENO);

        // Exécution de la commande "cat"
        execlp("cat", "cat", NULL);

        // En cas d'erreur de l'exécution de "cat"
        perror("Erreur lors de l'exécution de cat");
        exit(EXIT_FAILURE);
    }

    // Création du deuxième tube
    if (pipe(pipe2) == -1) {
        perror("Erreur lors de la création du tube 2");
        exit(EXIT_FAILURE);
    }

    // Fork du deuxième processus
    pid2 = fork();

    if (pid2 < 0) {
        perror("Erreur lors du deuxième fork");
        exit(EXIT_FAILURE);
    }

    if (pid2 == 0) {
        // Code du deuxième processus fils (cat)
        close(pipe1[1]);  // Ferme l'extrémité d'écriture du tube 1
        close(pipe2[0]);  // Ferme l'extrémité de lecture du tube 2

        // Redirection de l'entrée standard depuis l'extrémité de lecture du tube 1
        dup2(pipe1[0], STDIN_FILENO);

        // Redirection de la sortie standard vers l'extrémité d'écriture du tube 2
        dup2(pipe2[1], STDOUT_FILENO);

        // Exécution de la commande "cat"
        execlp("cat", "cat", NULL);

        // En cas d'erreur de l'exécution de "cat"
        perror("Erreur lors de l'exécution de cat");
        exit(EXIT_FAILURE);
    }

    // Code du processus père (ls)
    close(pipe1[0]);  // Ferme l'extrémité de lecture du tube 1
    close(pipe1[1]);  // Ferme l'extrémité d'écriture du tube 1
    close(pipe2[1]);  // Ferme l'extrémité d'écriture du tube 2

    // Redirection de l'entrée standard depuis l'extrémité de lecture du tube 2
    dup2(pipe2[0], STDIN_FILENO);

    // Exécution de la commande "ls"
    execlp("ls", "ls", NULL);

    // En cas d'erreur de l'exécution de "ls"
    perror("Erreur lors de l'exécution de ls");
    exit(EXIT_FAILURE);

    // Attente de la terminaison des processus fils
    wait(NULL);
    wait(NULL);

    return 0;
}



// -------------------------