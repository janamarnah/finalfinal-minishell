/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalamarn <jalamarn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 17:00:00 by jalamarn          #+#    #+#             */
/*   Updated: 2026/05/13 19:24:56 by jalamarn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	closefds(int *fd)
{
	if (fd && *fd >= 0)
	{
		close(*fd);
		*fd = -1;
	}
}

static void	childproc(int previousread, int hasnext, int pipefd[2],
	t_command *cmd)
{
	if (cmd->input_fd != STDIN_FILENO)
		dup2(cmd->input_fd, STDIN_FILENO);
	else if (previousread != -1)
		dup2(previousread, STDIN_FILENO);
	if (cmd->output_fd != STDOUT_FILENO)
		dup2(cmd->output_fd, STDOUT_FILENO);
	else if (hasnext)
		dup2(pipefd[1], STDOUT_FILENO);
	closefds(&previousread);
	if (hasnext)
	{
		close(pipefd[0]);
		close(pipefd[1]);
	}
	if (cmd->input_fd != STDIN_FILENO)
		closefds(&cmd->input_fd);
	if (cmd->output_fd != STDOUT_FILENO)
		closefds(&cmd->output_fd);
}

static void	exec_pipeline_child(t_shell *shellstate, t_pipeline *pl,
	t_pipe_ctx *ctx, int hasnext)
{
	setup_signals_child();
	childproc(ctx->previousread, hasnext, ctx->pipefd,
		&pl->commands[ctx->i]);
	if (!pl->commands[ctx->i].args || !pl->commands[ctx->i].args[0])
		exit(0);
	if (isbuiltin(pl->commands[ctx->i].args[0]))
		exit(runbuiltinchild(shellstate, pl->commands[ctx->i].args));
	executecmd(shellstate, pl->commands[ctx->i].args);
}

int	forkcommand(t_shell *shellstate, t_pipeline *pl, t_pipe_ctx *ctx)
{
	int	hasnext;

	hasnext = ctx->i < pl->num_commands - 1;
	if (hasnext && pipe(ctx->pipefd) == -1)
	{
		closefds(&ctx->previousread);
		return (0);
	}
	ctx->pid[ctx->i] = fork();
	if (ctx->pid[ctx->i] == -1)
		return (forkcommanderror(ctx, hasnext));
	if (ctx->pid[ctx->i] == 0)
		exec_pipeline_child(shellstate, pl, ctx, hasnext);
	closefds(&ctx->previousread);
	if (hasnext)
	{
		close(ctx->pipefd[1]);
		ctx->previousread = ctx->pipefd[0];
		return (1);
	}
	return (1);
}

int	executepipeline(t_shell *shellstate, t_pipeline *pl)
{
	t_pipe_ctx	ctx;

	if (!shellstate)
		return (1);
	if (!pl || pl->num_commands <= 0 || !pl->commands)
	{
		shellstate->exitstatus = 1;
		return (1);
	}
	if (execpipehelp(shellstate, pl, &ctx))
		return (1);
	if (execpipeloop(shellstate, pl, &ctx))
		return (1);
	shellstate->exitstatus = waitpipeline(ctx.pid, pl->num_commands);
	free(ctx.pid);
	return (shellstate->exitstatus);
}
