/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estruckm <estruckm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 22:29:28 by estruckm          #+#    #+#             */
/*   Updated: 2023/04/10 17:20:30 by estruckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	init_fd(t_stack *stack)
{
	int	fd;

	fd = open(stack->argv[1], O_RDONLY | O_APPEND);
	stack->fd_infile = fd;
	if (stack->fd_infile == -1)
		error_msg("couldn't find file or create file descriptor");
	stack->fd_outfile = open(stack->argv[stack->argc - 1],
			O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (stack->fd_outfile == -1)
	{
		close(stack->fd_infile);
		error_msg("Couldn't create file or file descriptor");
	}
}

void	init_stack(t_stack *stack, int argc, char **argv, char **env)
{
	stack->argv = argv;
	stack->env = env;
	stack->argc = argc;
}

void	init_pipes(t_stack *stack)
{
	int	i;

	i = 0;
	stack->fd_pipe = malloc(sizeof(int *) * (stack->argc - 4));
	while (i < (stack->argc - 4))
	{
		stack->fd_pipe[i] = malloc(sizeof(int) * 2);
		if (pipe(stack->fd_pipe[i++]) == -1)
			error_handler(*stack, "Couldn't create pipe");
	}
}

int	main(int argc, char **argv, char **env)
{
	t_stack	stack;

	if (argc < 5)
		error_msg("too less arguments");
	init_stack(&stack, argc, argv, env);
	check_commands(&stack);
	init_fd(&stack);
	init_pipes(&stack);
	execute_child_processes(stack);
	close(stack.fd_outfile);
	close(stack.fd_infile);
	fd_close(stack, 1, 3);
	ft_free_integer_array(stack.fd_pipe, argc -4);
	waitpid(0, NULL, 0);
	return (0);
}

//
//    while (i < (argc - 3))
//    {
//        stack.pid[i] = fork();
//        if ( stack.pid[i++] < 0)
//            exit(0);
//    }
//    if (stack.pid[0] == 0)
//    {
//        close(stack.fd_pipe[0][0]);
//        close(stack.fd_pipe[1][1]);
//        close(stack.fd_pipe[1][0]);
//        close(stack.fd_outfile);
//        dup2(stack.fd_infile, STDIN_FILENO);
//        close(stack.fd_infile);
//        dup2(stack.fd_pipe[0][1], STDOUT_FILENO);
//        close(stack.fd_pipe[0][1]);
//        exec_command(stack.env, stack.argv[2]);
//    }
//    if (stack.pid[1]== 0)
//    {
//        close(stack.fd_pipe[0][1]);
//        close(stack.fd_pipe[1][0]);
//        close(stack.fd_outfile);
//        close(stack.fd_infile);
//        dup2(stack.fd_pipe[0][0], STDIN_FILENO);
//        close(stack.fd_pipe[0][0]);
//        dup2(stack.fd_pipe[1][1], STDOUT_FILENO);
//        close(stack.fd_pipe[1][1]);
//        exec_command(stack.env, stack.argv[3]);
//    }

//
//    if (stack.pid[2] == 0)
//    {
//        close(stack.fd_pipe[0][0]);
//        close(stack.fd_pipe[0][1]);
//        close(stack.fd_pipe[1][1]);
//        close(stack.fd_infile);
//        dup2(stack.fd_pipe[1][0], STDIN_FILENO);
//        close(stack.fd_pipe[1][0]);
//        dup2(stack.fd_outfile, STDOUT_FILENO);
//        close(stack.fd_outfile);
//        exec_command(env, argv[4]);
//    }
