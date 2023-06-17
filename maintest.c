#include "minishell.h"
#include <signal.h>
#include <unistd.h>

// ----

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

char	*stick_color(char *str, char *color)
{
	char	*new_str;

	new_str = ft_join(color, str);
	new_str = ft_join(new_str, ft_strdup(NC));
	return (new_str);
}

// ----
char	*display_user_prompt()
{
	char	*result;
	char	*user;
	char	cwd[1024];

	if (!(user = getenv("USER")))
		return (NULL);
	user = stick_color(ft_join(ft_strdup(user), ft_strdup("@minishell42:")), ft_strdup("\033[32;1m"));
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return (NULL);
	result = ft_join(ft_strdup(cwd + ft_len(user) + 5), ft_strdup(" $ "));
	result = stick_color(ft_join(ft_strdup(" ~"), result), ft_strdup(BLUE));
	result = ft_join(user, result);
	return (result);
}

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

void sigint_handler()
{
	char	*prompt;

	rl_redisplay();
	ft_printf("\n");
	rl_replace_line("", 0);
	prompt = display_user_prompt();
	ft_printf("%s", prompt);
	free(prompt);
}

int main()
{
    char	*prompt;
    char	*input;

	signal(SIGINT, sigint_handler);
	prompt = display_user_prompt();
    while ((input = readline(prompt)) != NULL)
	{
		if (input[0])
			add_history(input);
		free(input);
    }
    free(prompt);
    return (0);
}