/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anuketay <anuketay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 16:21:43 by anuketay          #+#    #+#             */
/*   Updated: 2024/11/16 16:21:45 by anuketay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/libft/inc/libft.h"
# include "sys/wait.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef enum e_token_type
{
	TOKEN_END,
	TOKEN_R_INPUT,
	TOKEN_HERE_DOC,
	TOKEN_R_OUTPUT,
	TOKEN_A_OUTPUT,
	TOKEN_TEXT,
	TOKEN_LAST,
	TOKEN_PIPE
}					t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
}					t_token;

typedef struct s_data
{
	int		exit_flag;
	char	**envp;
}			t_data;

//signal_handler.c
void	set_handler_one(struct sigaction *sa);
void	set_handler_two(struct sigaction *sa);

//parse_input.c
t_list	*tokenize_input(char *line, int index, t_list *new, t_list *root);

//pipex.c
void	process_tokens(t_list *tokens, char *envp[], t_data *data);

//pipex_utils.c
char	*get_command_path(char **envp, char *argv);
void	free_split(char **args);
int		is_command(char *cmd);

//get_last_token.c
t_list	*finish_tokenizing(t_list *first);

//handle_quotes.c
char	*handle_quotes(char *line);

//execute.c
void	process_exec(t_list **command, t_token_type *first, t_data *data);

//redirections.c
int		redirect_input(char *filename);
int		redirect_output(char *filename, t_token_type type);
void	here_doc(char *limiter);

void	unset(char **args, char *envp[]);
void	pwd(char **args, char *envp[]);
void	cd(char **args, t_data *data);
void	export(char **args, char *envp[]);
void	ft_exit(void);
void	env(char **args, char *envp[]);
void	echo(char **args, char *envp[]);

void	print_lst(t_list *lst);
void	print_array(char **arr);
#endif
