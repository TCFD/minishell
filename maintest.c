#include "minishell.h"
#include <signal.h>
#include <unistd.h>

// ----
char	*input;

// ----
char	*getenv_check(char *str)
{
	char	*found_it;

	found_it = getenv(str);
	if (found_it == NULL)
		return (NULL);
	return (found_it);
}

// ----
char	*ccn(char *str, char *color)
{
	ft_printf("%s%s%s ", color, str, NC);
	return (str);
}

// ----
void	display_user_prompt()
{
	char	*result;
	char	*user;
	char	cwd[1024];

	if (!(user = getenv("USER")))
		return ;

	user = ft_join(ft_strdup(user), ft_strdup("@minishell42:"));
	ccn(user, "\033[32;1m");
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return ;
	result = ft_join(ft_strdup(cwd + 2 + ft_len(user)), ft_strdup(""));
	result = ft_join(ft_strdup("~"), result);
	ccn(result, BLUE);
	ccn("$>", GREEN);
	free(user);
	free(result);
}

// ----
void handle_ctrl_l()
{
	rl_clear_history();
    rl_on_new_line();
    rl_redisplay();
    kill(getpid(), SIGUSR1); // Envoie le signal SIGUSR1 au processus
}

// ----

void handle_ctrl_c()
{
	rl_replace_line("", 0);
	rl_on_new_line();
	write(1, "\n", 1);
	display_user_prompt();

}

void handle_sigusr1()
{
    printf("\n");
	rl_on_new_line();
    rl_redisplay();
	display_user_prompt();

}

// ----
int main()
{
	// Installation du gestionnaire de signal pour Ctrl+L

	signal(SIGUSR1, handle_ctrl_l);
	signal(SIGINT, handle_ctrl_c);
	while (1)
	{
		display_user_prompt();
		//write(STDOUT_FILENO, user, ft_strlen(user));
		input = readline("");
		if (strcmp(input, "exit") == 0)
		{
			free(input);
			return (1);
		}
		// On va Traiter l'entrée ici...
		if (input[0])
			add_history(input);
		if (input[0] == '\0')
			write(1, "\n", 1);
		free(input);
	}
	rl_clear_history();
	return (0);
}
