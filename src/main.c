#include "../inc/minishell.h"

sig_atomic_t	g_sigint_received = 0;

void	handler(int signum)
{
	if (signum == SIGINT)
		g_sigint_received = 1;
}

void	free_split(char **split_line)
{
	int	i;

	i = 0;
	while (split_line[i])
	{
		free(split_line[i]);
		i++;
	}
	free(split_line);
}

int	main(void)
{
	char	*line;
	char	**split_line;
	int		i;

	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	while (1)
	{
		i = 0;
		if (g_sigint_received)
		{
			printf("\n");
			g_sigint_received = 0;
			continue ;
		}
		line = readline("$ ");
		if (line == NULL)
			break ;
		split_line = ft_split_str(line);
		while (split_line[i])
		{
			ft_printf("%s\n", split_line[i]);
			i++;
		}
		free_split(split_line);
	}
	return (0);
}
