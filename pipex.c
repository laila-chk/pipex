/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchokri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 18:30:12 by lchokri           #+#    #+#             */
/*   Updated: 2022/06/17 14:46:33 by lchokri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h" 

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

void	not_accessible(char **av, char **cmd1, char **cmd2, char **envp)
{
	char **argv1;
	char **argv2;

	argv1 = ft_split(av[2], ' ' );
	argv2 = ft_split(av[3], ' ' );
	if (access(argv1[0], X_OK))
	{
		*cmd1 = ft_strjoin("/", argv1[0]);
		*cmd1 = check_cmd(*cmd1, envp);
	}
	else
		*cmd1 = av[2];
	if (access(argv2[0], X_OK))
	{
		*cmd2 = ft_strjoin("/", argv2[0]);
		*cmd2 = check_cmd(*cmd2, envp);
	}
	else
		*cmd2 = av[3];
}

void	manage_err(char *ptr, char *ptr2)
{
	if (ptr != NULL)
		free(ptr);
	if (ptr2 != NULL)
		free(ptr);
	perror("Error");
	exit(EXIT_FAILURE);
}

int main(int ac, char **av, char **envp)
{
	int		*fd;
	int		chld_pid;
	char	*cmd1;
	char	*cmd2;
	char	**argv1;
	char	**argv2;

	argv1 = ft_split(av[1], ' ' );
	argv2 = ft_split(av[4], ' ' );
	if (ac == 5)
	{
		fd = malloc(2 * sizeof(int));
		if ((fd[0] = open(av[1], O_RDONLY))== -1)
			manage_err(NULL, NULL);
		if ((fd[1] = open(av[4], O_RDWR | O_CREAT, 0666))== -1)
			manage_err(NULL, NULL);
		not_accessible(av, &argv1[0], &argv2[0], envp);
		if (!argv1[0])
			manage_err(NULL, NULL);
		if (!argv2[0])
			manage_err(NULL, NULL);
		dup2(fd[1], 1);
		dup2(fd[0], 0);
		pipe(fd);
		chld_pid = fork();
		if (chld_pid > 0)
		{
			execve(argv2[0], argv2, envp);
			execve(argv1[0], argv1, envp);
//			close()
		}
		else
		{
			wait(NULL);
		}
		printf("we made it here\n");
	}
	else
			write(2, "Error!\nUsage: ./pipex f1 cmd1 cmd2 f2\n", 41);
}
