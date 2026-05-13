/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execexternal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalamarn <jalamarn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 17:00:00 by jalamarn          #+#    #+#             */
/*   Updated: 2026/05/13 14:28:48 by jalamarn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	isdirectory(const char *path)
{
	struct stat	infofile;

	if (stat(path, &infofile) == 0 && S_ISDIR(infofile.st_mode))
		return (1);
	return (0);
}

static void	cmdnotfound(const char *cmd)
{
	ft_putstr_fd(cmd, STDERR_FILENO);
	write(2, ": ", 2);
	ft_putstr_fd("command not found\n", STDERR_FILENO);
	exit(127);
}

static void	execvefail(const char *cmd)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	perror(cmd);
	if (errno == EACCES)
		exit(126);
	if (errno == ENOENT)
		exit(127);
	exit(127);
}

void	executecmd(t_shell *shellstate, char **argv)
{
	char	**envp;
	char	*path;

	if (!argv || !argv[0])
		exit(0);
	envp = envtoenvp(shellstate->env);
	if (!envp)
		exit(1);
	path = findpath(envp, argv[0]);
	if (!path)
	{
		free_tab(envp);
		cmdnotfound(argv[0]);
	}
	if (isdirectory(path))
	{
		free_tab(envp);
		errormsg(path, "is a directory", STDERR_FILENO);
		free(path);
		exit(126);
	}
	execve(path, argv, envp);
	free(path);
	free_tab(envp);
	execvefail(argv[0]);
}
