#include "minishell.h"
#include <signal.h>
#include <unistd.h>

// ----
void	print_minishell()
{
	ft_printf("%s", GREEN);
	ft_printf("\n>\t __  __ _       _     _          _ _\t    <\n");
	ft_printf(">\t|  \\/  (_)_ __ (_)___| |__   ___| | |\t    <\n");
	ft_printf(">\t| |\\/| | | '_ \\| / __| '_ \\ / _ \\ | |       <\t\n");
	ft_printf(">\t| |  | | | | | | \\__ \\ | | |  __/ | |\t    <\n");
	ft_printf(">\t|_|  |_|_|_| |_|_|___/_| |_|\\___|_|_|\t    <\n\n");
	ft_printf("%s", NC);
}

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
	str = ft_join(ft_strdup(color), str);
	str = ft_join(str, ft_strdup(NC));
	return (str);
}

// ----
char	*display_user_prompt()
{
	char	*username;
	char	*result;
	char	cwd[1024];

	username = getenv_check("USER");
	if (username == NULL)
		return (NULL);
	username = ft_join(ft_strdup("("), username);
	username = ft_join(username, ft_strdup(")"));
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return (NULL);
	
	result = ft_join(ccn(username, "\033[32;1m"), ft_join(ft_strdup(" "), ccn(cwd, "\033[34m")));
	return (result);
}

// ----
void handle_ctrl_l()
{
    rl_on_new_line();
    rl_redisplay();
    kill(getpid(), SIGUSR1); // Envoie le signal SIGUSR1 au processus
}

// ----

void handle_sigusr1()
{
	char	*prompt;

    printf("\n");
	rl_on_new_line();
	prompt = display_user_prompt();
	write(STDOUT_FILENO, prompt, ft_strlen(prompt));
	free(prompt);
    rl_redisplay();
}

// ----
int main()
{
	char	*user;
	char	*input;

	print_minishell();

	// Installation du gestionnaire de signal pour Ctrl+L
	signal(SIGINT, handle_ctrl_l);
	signal(SIGUSR1, handle_sigusr1);

	user = display_user_prompt();

	while (1)
	{
		write(STDOUT_FILENO, user, ft_strlen(user));
		input = readline("\033[34m $> \033[0m");
		if (strcmp(input, "exit") == 0)
		{
			free(input);
			break;
		}
		// On va Traiter l'entrée ici...
		add_history(input);
		free(input);
	}
	rl_clear_history();
	free(user);
	return (0);
}
