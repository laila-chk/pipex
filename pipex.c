/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchokri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 18:30:12 by lchokri           #+#    #+#             */
/*   Updated: 2022/06/14 19:33:16 by lchokri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>

//1- split paths
//check if file exist
//check if cmds exist
//run da command

void	manage_err(char *ptr)
{
	if (ptr != NULL)
		free(ptr);
	perror("Error");
	exit(EXIT_FAILURE);
}

void	add_cmd_to_paths(char **paths, char *cmd)
{
}

char	*check_cmd(char *cmd, char **envp)
{
	char	**paths;
	char	*path;

	while (envp)
	{
		if (!ft_strncmp("PATH", *envp, 5))
			break;
		envp++;
	}
	paths = ft_split(*envp, ':');
	while (paths)
	{
		ft_strjoin2(*paths, cmd);
		if (access(*paths, X_OK) == 0)
			path = ft_strdup(paths);
		//free (*paths);
		paths++;
	}
	free(path);
}

int main(int ac, char **av, char **envp)
{
	int		fd;
	int		chld_pid;
	char	*cmd;

	if (ac == 5)
	{
		if ((fd = open(av[1], O_RDWR))== -1)
			manage_err(NULL);
		check_cmd(av[2], envp);
		check_cmd(av[3], envp);
		chld_pid = fork();
		if (chld_pid == 0)
		{
			printf("we're in da child");
		//	execve("", );
		}
		wait(NULL);
		close(fd);
	}
	else
		printf("you should enter 4 argument beside the executable instead of %d", ac - 1);
}
