/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estruckm <estruckm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 14:41:51 by estruckm          #+#    #+#             */
/*   Updated: 2023/04/10 17:33:06 by estruckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	error_msg(char *str)
{
	char	*output_str;
	int		str_len;

	output_str = ft_strjoin(str, "\n");
	str_len = ft_strlen(output_str);
	write(1, output_str, str_len);
	free(output_str);
	exit (1);
}

void	check_commands(t_stack *stack)
{
	int		i;
	char	*command_path;

	i = 0;
	while (i < stack->argc - 4)
	{
		command_path = get_command_path(stack->argv[i + 2], stack->env);
		if (command_path == NULL)
		{
			free(command_path);
			error_msg("Invalid command found");
		}
		free(command_path);
		i++;
	}
}

void	error_handler(t_stack stack, char *str)
{
	if (stack.fd_outfile != -1)
		close(stack.fd_infile);
	if (stack.fd_outfile != -1)
		close(stack.fd_outfile);
	fd_close(stack, 1, 3);
	ft_free_integer_array(stack.fd_pipe, stack.argc - 4);
	write(STDERR_FILENO, "error: ", 7);
	perror(str);
	exit(1);
}
