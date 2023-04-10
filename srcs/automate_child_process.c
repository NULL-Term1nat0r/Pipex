/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   automate_child_process.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estruckm <estruckm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 17:06:07 by estruckm          #+#    #+#             */
/*   Updated: 2023/04/10 17:14:09 by estruckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	fd_close(t_stack stack, int fd_open, int mode)
{
	int	i;
	int	j;

	i = 0;
	while (i < (stack.argc - 4))
	{
		j = 0;
		while (j < 2)
		{
			if (mode == 0)
				if (!(i == fd_open && j == 1))
					close(stack.fd_pipe[i][j]);
			if (mode == 1)
				if (!(i == fd_open - 1 && j == 0) && !(i == fd_open && j == 1))
					close(stack.fd_pipe[i][j]);
			if (mode == 2)
				if (!(i == fd_open - 1 && j == 0))
					close(stack.fd_pipe[i][j]);
			if (mode == 3)
				close(stack.fd_pipe[i][j]);
			j++;
		}
		i++;
	}
}

void	execute_child_process(t_stack stack, int i, int mode)
{
	if (mode == 0)
	{
		first_child_process(stack);
	}
	if (mode == 1)
	{
		middle_child_processes (stack, i);
	}
	if (mode == 2)
	{
		last_child_process (stack, i);
	}
}

void	execute_child_processes_mode(t_stack stack, int i)
{
	if (i == 0)
	{
		fd_close(stack, i, 0);
		execute_child_process(stack, i, 0);
	}
	if (i > 0 && i < stack.argc - 4)
	{
		fd_close(stack, i, 1);
		execute_child_process(stack, i, 1);
	}
	if (i == stack.argc - 4)
	{
		fd_close(stack, i, 2);
		execute_child_process(stack, i, 2);
	}
}

void	execute_child_processes(t_stack stack)
{
	int		i;
	pid_t	pid;

	i = 0;
	while (i < (stack.argc - 3))
	{
		pid = fork();
		if (pid < 0)
			error_handler(stack, "Couldn't create child_process");
		if (pid == 0)
		{
			execute_child_processes_mode(stack, i);
		}
		i++;
	}
}

//void execute_child_process_1(t_stack stack)
//{
//        close(stack.fd_outfile);
//        dup2(stack.fd_infile, STDIN_FILENO);
//        close(stack.fd_infile);
//        dup2(stack.fd_pipe[0][1], STDOUT_FILENO);
//        close(stack.fd_pipe[0][1]);
//        exec_command(stack.env, stack.argv[2]);
//}
//
//void execute_child_process_2(t_stack stack, int i)
//{
//    dup2(stack.fd_pipe[i - 1][0], STDIN_FILENO);
//    close(stack.fd_pipe[i - 1][0]);
//    dup2(stack.fd_pipe[i][1], STDOUT_FILENO);
//    close(stack.fd_pipe[i][1]);
//    exec_command(stack.env, stack.argv[i + 2]);
//}
//
//void execute_child_process_3(t_stack stack, int i)
//{
//    close(stack.fd_infile);
//    dup2(stack.fd_pipe[i - 1][0], STDIN_FILENO);
//    close(stack.fd_pipe[i - 1][0]);
//    dup2(stack.fd_outfile, STDOUT_FILENO);
//    close(stack.fd_outfile);
//    exec_command(stack.env, stack.argv[i + 2]);
//}
