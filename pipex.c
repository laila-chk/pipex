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

#include "pipex.h" 

//1- split paths
//check if file exist
//check if cmds exist
//run da command

void	manage_err(char *ptr, char *ptr2)
{
	if (ptr != NULL)
		free(ptr);
	if (ptr2 != NULL)
		free(ptr);
	perror("Error");
	exit(EXIT_FAILURE);
}

char	*check_cmd(char *cmd, char **envp)
{
	char	**paths;
	char	**p;
	char	*path;

	p = paths;
	path = NULL;
	while (envp)
	{
		if ((ft_strncmp("PATH", *envp, 4)) == 0)
			break;
		envp++;
	}
	paths = ft_split(*envp+5, ':');
	while (*paths)
	{
		*paths = ft_strjoin(*paths, cmd);
		if (access(*paths, X_OK) == 0)
			path = ft_strdup(*paths);
		free (*paths);
		paths++;
	}
//	free(p); where da fuck is that dbl free?
	return (path);
}

//went wrong on that cmd joining, split the cmd by space first, then append only the
//cmd not the option too
int main(int ac, char **av, char **envp)
{
	int		*fd;
	int		chld_pid;
	char	*cmd1;
	char	*cmd2;
// pipefd[0] for read end of pipe, pipefd[1] write end of pipe
	if (ac == 5)
	{
		fd = malloc(2 * sizeof(int));
		if ((fd[1] = open(av[1], O_RDONLY))== -1)
			manage_err(NULL, NULL);
		if ((fd[0] = open(av[4], O_RDWR | O_CREAT))== -1)
			manage_err(NULL, NULL);
		pipe(fd);
		cmd1 = ft_strjoin("/", av[2]);
		cmd2 = ft_strjoin("/", av[3]);
		cmd1 = check_cmd(cmd1, envp);
		cmd2 = check_cmd(cmd2, envp);
		printf("cmd1=%s, cmd2=%s\n", cmd1, cmd2);
		if (!cmd1 || !cmd2)
			manage_err(cmd1, cmd2);
		chld_pid = fork();
		if (chld_pid > 0)
		{
			printf("child problem");
			execve(cmd1, &cmd1, envp);
		}
		else
		{
			execve(cmd2, &cmd2, envp);
			wait(NULL);
		}
	}
	else
			write(2, "Error!\nUsage: ./pipex f1 cmd1 cmd2 f2\n", 41);
}
