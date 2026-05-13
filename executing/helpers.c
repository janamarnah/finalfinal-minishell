/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalamarn <jalamarn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 17:00:00 by jalamarn          #+#    #+#             */
/*   Updated: 2026/05/13 19:24:50 by jalamarn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	errormsg(const char *cmd, const char *msg, int fd)
{
	ft_putstr_fd("minishell: ", fd);
	if (cmd)
	{
		ft_putstr_fd(cmd, fd);
		ft_putstr_fd(": ", fd);
	}
	ft_putstr_fd(msg, fd);
	ft_putchar_fd('\n', fd);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (i <= (int)ft_strlen(s))
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	return (NULL);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	n;
	char	*substr;

	i = 0;
	if (!s)
		return (NULL);
	n = ft_strlen(s);
	if (start >= n || len == 0)
		return (ft_strdup(""));
	if (len > n - start)
		len = n - start;
	substr = malloc((len + 1) * sizeof(char));
	if (!substr)
		return (NULL);
	while (i < len && s[start])
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}

int	execpipehelp(t_shell *shellstate, t_pipeline *pl, t_pipe_ctx *ctx)
{
	ctx->i = 0;
	ctx->previousread = -1;
	ctx->pid = (pid_t *)malloc(sizeof(pid_t) * pl->num_commands);
	if (!ctx->pid)
	{
		shellstate->exitstatus = 1;
		return (1);
	}
	return (0);
}

int	execpipeloop(t_shell *shellstate, t_pipeline *pl, t_pipe_ctx *ctx)
{
	while (ctx->i < pl->num_commands)
	{
		if (!forkcommand(shellstate, pl, ctx))
		{
			closefds(&ctx->previousread);
			free(ctx->pid);
			return (1);
		}
		if (pl->commands[ctx->i].input_fd != STDIN_FILENO)
			closefds(&pl->commands[ctx->i].input_fd);
		if (pl->commands[ctx->i].output_fd != STDOUT_FILENO)
			closefds(&pl->commands[ctx->i].output_fd);
		ctx->i++;
	}
	return (0);
}
