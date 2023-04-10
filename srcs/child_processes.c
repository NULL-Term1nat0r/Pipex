/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_processes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estruckm <estruckm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 17:07:50 by estruckm          #+#    #+#             */
/*   Updated: 2023/04/10 17:14:52 by estruckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	first_child_process(t_stack stack)
{
	close(stack.fd_outfile);
	dup2(stack.fd_infile, STDIN_FILENO);
	close(stack.fd_infile);
	dup2(stack.fd_pipe[0][1], STDOUT_FILENO);
	close(stack.fd_pipe[0][1]);
	exec_command(stack, stack.env, stack.argv[2]);
}

void	middle_child_processes(t_stack stack, int i)
{
	dup2(stack.fd_pipe[i - 1][0], STDIN_FILENO);
	close(stack.fd_pipe[i - 1][0]);
	dup2(stack.fd_pipe[i][1], STDOUT_FILENO);
	close(stack.fd_pipe[i][1]);
	exec_command(stack, stack.env, stack.argv[i + 2]);
}

void	last_child_process(t_stack stack, int i)
{
	close(stack.fd_infile);
	dup2(stack.fd_pipe[i - 1][0], STDIN_FILENO);
	close(stack.fd_pipe[i - 1][0]);
	dup2(stack.fd_outfile, STDOUT_FILENO);
	close(stack.fd_outfile);
	exec_command(stack, stack.env, stack.argv[i + 2]);
}
