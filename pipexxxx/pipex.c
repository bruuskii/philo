/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izouine <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 04:33:58 by izouine           #+#    #+#             */
/*   Updated: 2024/04/18 16:44:30 by izouine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

char	*join(char **argv, int k, char **cmd, char **envp)
{
	int		i;
	char	*temp;
	char	*two_joined;
	char	**splited;

	i = 0;
	temp = NULL;
	splited = find_path(envp);
	cmd = ft_split(argv[k], ' ');
	while (splited[i])
	{
		temp = ft_strjoin(splited[i], "/");
		two_joined = ft_strjoin(temp, cmd[0]);
		free(temp);
		if (!access(two_joined, F_OK | X_OK))
			return (ft_free(splited), two_joined);
		free(two_joined);
		i++;
	}
	return (NULL);
}

static void	child(char **argv, int fd[2], char **envp)
{
	char	*path;
	char	**cmd;
	char	**pathh;
	char	*msg;
	char	*lol;

	pathh = NULL;
	path = join(argv, 2, pathh, envp);
	if (path == NULL)
	{
		msg = "zsh: command not found :";
		write(STDERR_FILENO, msg, ft_strlen(msg));
		lol = argv[2];
		write(STDERR_FILENO, lol, ft_strlen(lol));
		write(STDERR_FILENO, "\n", 1);
		exit(1);
	}
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	cmd = ft_split(argv[2], ' ');
	execve(path, cmd, NULL);
	exitt(1);
}

static void	parent(char **argv, int fd[2], char **envp)
{
	char	*path;
	char	**cmd2;
	char	**pathh;
	char	*message;
	char	*lol;

	pathh = NULL;
	if (!ft_strncmp("sleep", argv[2], 4))
		wait(NULL);
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	path = join(argv, 3, pathh, envp);
	if (!path)
	{
		message = "zsh: command not found :";
		write(STDERR_FILENO, message, ft_strlen(message));
		lol = argv[3];
		write(STDERR_FILENO, lol, ft_strlen(lol));
		write(STDERR_FILENO, "\n", 1);
		exit(1);
	}
	cmd2 = ft_split(argv[3], ' ');
	execve(path, cmd2, NULL);
	exitt(1);
}

void	exitt(int check)
{
	perror("zsh");
	if (check)
		exit(1);
}

int	main(int argc, char **argv, char **envp)
{
	int	fd[2];
	int	in;
	int	output_fd;
	int	pid;

	if (argc != 5)
		exitt(1);
	if (pipe(fd) == -1)
		exitt(1);
	in = open(argv[1], O_RDONLY);
	output_fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (output_fd == -1)
		exitt(1);
	else if (in == -1)
		exitt(0);
	dup2(in, STDIN_FILENO);
	dup2(output_fd, STDOUT_FILENO);
	pid = fork();
	if (pid < 0)
		exitt(1);
	else if (pid == 0 && in != -1)
		child(argv, fd, envp);
	else if (pid > 0)
		parent(argv, fd, envp);
	la_fin(in);
}
