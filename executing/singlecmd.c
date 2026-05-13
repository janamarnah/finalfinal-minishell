/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singlecmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalamarn <jalamarn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 17:00:00 by jalamarn          #+#    #+#             */
/*   Updated: 2026/05/13 19:18:02 by jalamarn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	isbuiltinparent(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strcmp(cmd, "cd") == 0 || ft_strcmp(cmd, "exit") == 0)
		return (1);
	if (ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd, "export") == 0)
		return (1);
	return (0);
}

static int	redirectionsparent(t_command *cmd, int *savein, int *saveout)
{
	if (savestdio(savein, saveout))
		return (1);
	if (cmd->input_fd != STDIN_FILENO)
	{
		if (dup2(cmd->input_fd, STDIN_FILENO) < 0)
		{
			close(*savein);
			close(*saveout);
			return (1);
		}
	}
	if (cmd->output_fd != STDOUT_FILENO)
	{
		if (dup2(cmd->output_fd, STDOUT_FILENO) < 0)
		{
			dup2(*savein, STDIN_FILENO);
			close(*savein);
			close(*saveout);
			return (1);
		}
	}
	return (0);
}

static void	restore_parent(t_command *cmd, int *savein, int *saveout)
{
	if (*savein >= 0)
	{
		dup2(*savein, STDIN_FILENO);
		close(*savein);
		*savein = -1;
	}
	if (*saveout >= 0)
	{
		dup2(*saveout, STDOUT_FILENO);
		close(*saveout);
		*saveout = -1;
	}
	if (cmd->input_fd != STDIN_FILENO)
		close(cmd->input_fd);
	if (cmd->output_fd != STDOUT_FILENO)
		close(cmd->output_fd);
	cmd->input_fd = STDIN_FILENO;
	cmd->output_fd = STDOUT_FILENO;
}

static int	execute_parent_builtin(t_shell *shellstate, t_command *cmd)
{
	int	savein;
	int	saveout;
	int	status;

	savein = -1;
	saveout = -1;
	if (redirectionsparent(cmd, &savein, &saveout) == 1)
	{
		shellstate->exitstatus = 1;
		return (1);
	}
	status = runbuiltinparent(shellstate, cmd);
	restore_parent(cmd, &savein, &saveout);
	if (status >= 1000)
	{
		shellstate->exitstatus = status - 1000;
		shellstate->should_exit = 1;
		return (shellstate->exitstatus);
	}
	shellstate->exitstatus = status;
	return (status);
}

int	executesinglecmd(t_shell *shellstate, t_command *cmd)
{
	pid_t	pid;
	int		rawstat;

	if (!cmd || !cmd->args || !cmd->args[0])
	{
		shellstate->exitstatus = 0;
		return (0);
	}
	if (isbuiltin(cmd->args[0]) && isbuiltinparent(cmd->args[0]))
		return (execute_parent_builtin(shellstate, cmd));
	pid = fork();
	if (pid == -1)
	{
		shellstate->exitstatus = 1;
		return (1);
	}
	if (pid == 0)
		child_single(shellstate, cmd);
	if (cmd->input_fd != STDIN_FILENO)
		close(cmd->input_fd);
	if (cmd->output_fd != STDOUT_FILENO)
		close(cmd->output_fd);
	waitpid(pid, &rawstat, 0);
	shellstate->exitstatus = convertstatus(rawstat);
	return (shellstate->exitstatus);
}
