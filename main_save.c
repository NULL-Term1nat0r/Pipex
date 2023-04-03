/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estruckm <estruckm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 22:29:28 by estruckm          #+#    #+#             */
/*   Updated: 2023/04/02 00:56:50 by estruckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"
void child_process_1(t_stack stack, int *fd)
{
    stack.pid[0] = fork();
    printf("pid: %d\n", stack.pid[0]);
    if (stack.pid[0] < 0)
    {
        exit(0);
    }
    if (stack.pid[0] == 0)
    {
        dup2(stack.fd_infile, fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        close(fd[1]);
        close(stack.fd_infile);
        exec_command(stack.env, stack.argv[2]);
    }


    //        dup2(fd[1], STDOUT_FILENO);
    //        close(fd[0]);
    //        close(fd[1]);
    //        exec_command(env, argv[1]);
}

//void child_process_2(t_stack stack) {
//    stack.pid[1] = fork();
//    if (stack.pid[0] < 0) {
//        exit(0);
//    }
//    if (stack.pid[0] == 0) {
//        dup2(fd[1], STDOUT_FILENO);
//        dup2(stack.fd_infile, STDOUT_FILENO);
//        close(fd[0]);
//        close(fd[1]);
//        close(stack.fd_infile);
//        exec_command(stack.env, stack.argv[2]);
//    }
//}
//void close_fd()

void	error_handler(char *str, int fd)
{
    if (fd != -1)
        write(fd, "       0\n", 9);
    write(STDERR_FILENO, "pipex: ", 7);
    perror(str);
    exit(0);
}
//int main (int argc, char **argv, char **env)
int main (int argc, char **argv, char **env)
{
    t_stack stack;
    int i;
    i = 0;

    stack.argv = argv;
    stack.env = env;
    stack.argc = argc;
//    stack.pid = malloc(sizeof(pid_t) * (argc - 3));
//    stack.fd_pipe = malloc(sizeof(int *) * (argc - 3));
//    i = 0;
//    while (i < (argc - 3))
//        stack.fd_pipe[i++] = malloc(sizeof(int) * 2);

//    stack.pid = stack.pid[argc - 3][2];


    stack.fd_outfile = open(argv[argc - 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
    if (stack.fd_outfile == -1)
        error_handler(stack.argv[2], -1);
    stack.fd_infile = open(argv[1], O_RDONLY);
    if (stack.fd_infile == -1)
        error_handler(stack.argv[1], stack.fd_outfile);
//    char *s;
    int pid1;
    int pid2;
    int pid3;
    int fd[2];
    int fd_2[2];

    if (pipe(fd) == -1)
    {
        return (1);
    }
    if (pipe(fd_2) == -1)
    {
        return (1);
    }
//    child_process_1(stack, fd);
    pid1 = fork();
    if (pid1 < 0)
    {
        exit(0);
    }
    if (pid1 == 0)
    {
        close(stack.fd_outfile);
        close(fd_2[0]);
        close(fd_2[1]);
        close(fd[0]);
        dup2(stack.fd_infile, STDIN_FILENO);
//        close(fd[0]);
        close(stack.fd_infile);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);
        exec_command(stack.env, stack.argv[2]);
    }

    pid2 = fork();
    if (pid2 < 0)
    {
        exit(0);
    }
    if (pid2 == 0)
    {
        close(fd_2[0]);
        close(fd[1]);
        close(stack.fd_infile);
        close(stack.fd_outfile);
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);
        dup2(fd_2[1], STDOUT_FILENO);
        close(fd_2[1]);
        exec_command(stack.env, stack.argv[3]);
    }

//            dup2(fd[1], STDOUT_FILENO);
//            close(fd[0]);
//            close(fd[1]);
//            exec_command(env, argv[1]);

//    printf("test\n"),
    pid3 = fork();
    if (pid3 < 0)
    {
        return (3);
    }
    if (pid3 == 0)
    {
        close(fd[0]);
        close(fd[1]);
        close(fd_2[1]);
        close(stack.fd_infile);
//        close(fd_2[1]);
        dup2(fd_2[0], STDIN_FILENO);
        close(fd_2[0]);
        dup2(stack.fd_outfile, STDOUT_FILENO);
        close(stack.fd_outfile);
        exec_command(env, argv[4]);
    }
    close(stack.fd_infile);
    close(stack.fd_outfile);
    close(fd[0]);
    close(fd[1]);
    close(fd_2[0]);
    close(fd_2[1]);

    waitpid(pid1, NULL, 0);
    waitpid(pid3, NULL, 0);
    waitpid(pid2, NULL, 0);



	return 0;
}









