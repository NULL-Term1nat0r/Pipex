/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estruckm <estruckm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 22:31:48 by estruckm          #+#    #+#             */
/*   Updated: 2023/04/10 17:32:12 by estruckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*get_command(char *argv)
{
	char	**string;
	char	*string2;
	int		i;

	i = 1;
	string = ft_split(argv, ' ');
	while (string[i] != NULL)
		free(string[((i++))]);
	string2 = string[0];
	free(string);
	return (string2);
}

char	**get_path(char **env)
{
	int		i;
	char	*path;
	char	**path_folder;
	int		str_len;

	i = 0;
	while (ft_strncmp("PATH=", env[i], 5) != 0)
		i++;
	str_len = ft_strlen(env[i]);
	path = ft_substr(env[i], 5, str_len);
	path_folder = ft_split(path, ':');
	free(path);
	return (path_folder);
}

char	*get_command_path(char *arg, char **env)
{
	char	**path_folder;
	char	*command;
	char	*command_built;
	char	*command_path;
	int		i;

	i = 0;
	path_folder = get_path(env);
	command = get_command(arg);
	command_built = ft_strjoin("/", command);
	free(command);
	while (path_folder[i])
	{
		command_path = ft_strjoin(path_folder[i++], command_built);
		if (access(command_path, F_OK | X_OK) == 0)
		{
			ft_free_char_array(path_folder);
			free(command_built);
			return (command_path);
		}
		free(command_path);
	}
	ft_free_char_array(path_folder);
	free(command_built);
	return (NULL);
}

char	**get_command_arguments(char *arg)
{
	char	**arguments;

	arguments = ft_split(arg, ' ');
	return (arguments);
}

void	exec_command(t_stack stack, char **env, char *arg)
{
	char	*command_path;
	char	**command_args;

	command_path = get_command_path(arg, env);
	if (command_path == NULL)
		error_handler(stack, "could not execute command");
	command_args = get_command_arguments(arg);
	if (execve(command_path, command_args, env) == -1)
	{
		free(command_path);
		ft_free_char_array(command_args);
		error_handler(stack, "Couldn't execute command");
	}
}
