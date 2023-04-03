/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estruckm <estruckm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 22:26:26 by estruckm          #+#    #+#             */
/*   Updated: 2023/03/29 23:26:47 by estruckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
# include <fcntl.h>

typedef struct s_stack
{
    int		fd_infile;
    int		fd_outfile;
    int		argc;
    pid_t   *pid;
    int     **fd_pipe;
    char	**argv;
    char	**env;
}		t_stack;

char  **get_path(char **env);
char *get_command(char *argv);
char *get_command_path(char *arg, char **env);
void exec_command(char **env, char *args);

# endif