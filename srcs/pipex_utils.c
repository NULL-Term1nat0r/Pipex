/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estruckm <estruckm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 22:31:48 by estruckm          #+#    #+#             */
/*   Updated: 2023/03/29 22:32:07 by estruckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char *get_command(char *argv)
{
    char **string;
    char *command;
    int i;

    i = 0;

    string = ft_split(argv, ' ');
    command = string[i];
//    printf("command: %s\n", command);
    while (string[i + 1] != NULL)
            free(string[((i++) + 1)]);
    return (command);
}

char  **get_path(char **env)
{
    char *path;
    char **path_folder;
    int str_len;

    str_len = ft_strlen(env[0]);
    path = ft_substr(env[0], 5, str_len);
    path_folder = ft_split(path, ':');
    return (path_folder);
}

char *get_command_path(char *arg, char **env)
{
    char **path_folder;
    char *command;
    char *command_path;
    int i;

    i = 0;
    path_folder = get_path(env);
    command = get_command(arg);
    command = ft_strjoin("/", command);
    while (path_folder[i])
    {

        command_path = ft_strjoin(path_folder[i++], command);

        if(access(command_path, F_OK | X_OK) == 0)
            return (command_path);
        free(command_path);
    }
    return (NULL);
}

char **get_arguments(char *arg)
{
    char **arguments;

    arguments = ft_split(arg, ' ');
    return (arguments);
}

void exec_command(char **env, char *arg)
{
    char *command_path;
    char **args;

    command_path = get_command_path(arg, env);
    args = get_arguments(arg);
    if(execve(command_path, args, env) == -1)
        perror("Could execute command\n");
}



//#include <unistd.h>
//
//int main() {
//    char *argv[] = {"ls", "-l", NULL};
//    char *envp[] = {"PATH=/bin:/usr/bin", NULL};
//    execve("/bin/ls", argv, envp);
//    return 0;
//}


//char	*get_path(char *cmd, char **env)
//{
//    int		i;
//    char	*exec;
//    char	**allpath;
//    char	*path_part;
//    char	**s_cmd;
//
//    i = -1;
//    allpath = ft_split(my_getenv("PATH", env), ':');
//    s_cmd = ft_split(cmd, ' ');
//    while (allpath[++i])
//    {
//        path_part = ft_strjoin(allpath[i], "/");
//        exec = ft_strjoin(path_part, s_cmd[0]);
//        free(path_part);
//        if (access(exec, F_OK | X_OK) == 0)
//        {
//            ft_free_tab(s_cmd);
//            printf("exec: %s\n", exec);
//            return (exec);
//        }
//        free(exec);
//    }
//    ft_free_tab(allpath);
//    ft_free_tab(s_cmd);
//    return (cmd);
//}