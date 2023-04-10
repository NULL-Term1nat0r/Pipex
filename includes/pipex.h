/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estruckm <estruckm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 22:26:26 by estruckm          #+#    #+#             */
/*   Updated: 2023/04/10 17:32:02 by estruckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

typedef struct s_stack
{
	int		fd_infile;
	int		fd_outfile;
	int		argc;
	int		**fd_pipe;
	char	**argv;
	char	**env;
}		t_stack;

void	error_msg(char *str);
void	check_commands(t_stack *stack);
char	**get_path(char **env);
char	*get_command(char *argv);
char	*get_command_path(char *arg, char **env);
void	exec_command(t_stack stack, char **env, char *args);
void	execute_child_processes(t_stack stack);
void	fd_close(t_stack stack, int fd_open, int mode);
void	error_handler(t_stack stack, char *str);
void	first_child_process(t_stack stack);
void	middle_child_processes(t_stack stack, int i);
void	last_child_process(t_stack stack, int i);

#endif
