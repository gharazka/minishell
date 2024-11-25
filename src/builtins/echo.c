#include "../../inc/minishell.h"

void	echo(char **args, char *envp[])
{
    int		index;
    int		newline;

    index = 1;
    newline = 1;
    if (args[index] && ft_strncmp(args[index], "-n", 2) == 0)
    {
        newline = 0;
        index++;
    }
    while (args[index])
    {
        ft_putstr_fd(args[index], STDOUT_FILENO);
        if (args[index + 1])
            ft_putchar_fd(' ', STDOUT_FILENO);
        index++;
    }
    if (newline)
        ft_putchar_fd('\n', STDOUT_FILENO);
}
