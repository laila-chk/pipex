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

int	get_path(char **envp, char *cmd)
{
	//split those paths && search for the cmd inside them
}

int main(int ac, char **av, char **envp)
{
	int		fd;
	int		chld_pid;

	if (ac == 5)
	{
		fd = open(av[1], O_RDWR);
		chld_pid = fork();	
		if (chld_pid == 0)
		{
			execve("", );
		}
		close(fd);
	}
	else
		printf("you should enter 4 argument beside the executable instead of %d", ac - 1);
}
