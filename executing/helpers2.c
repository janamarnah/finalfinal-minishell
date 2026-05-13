/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalamarn <jalamarn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 17:00:00 by jalamarn          #+#    #+#             */
/*   Updated: 2026/05/13 19:01:13 by jalamarn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	a;
	char	*string;

	i = 0;
	a = 0;
	if (!s1 || !s2)
		return (NULL);
	string = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!string)
		return (NULL);
	while (s1[i])
		string[a++] = s1[i++];
	i = 0;
	while (s2[i])
		string[a++] = s2[i++];
	string[a] = '\0';
	return (string);
}

void	free_tab(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int	ifsmain(t_shell *shellstate, t_token *tokens, t_pipeline **pl)
{
	if (!tokens)
	{
		shellstate->exitstatus = 258;
		return (1);
	}
	if (!syntax_validator(tokens))
	{
		lst_clear(&tokens);
		shellstate->exitstatus = 258;
		return (1);
	}
	*pl = parse_pipeline(tokens);
	lst_clear(&tokens);
	if (!pl)
	{
		shellstate->exitstatus = 1;
		return (1);
	}
	return (0);
}

void	mainhelper(t_shell *shellstate)
{
	char	*line;

	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
		{
			ft_putstr_fd("exit \n", STDERR_FILENO);
			break ;
		}
		if (g_lastsig == SIGINT)
			shellstate->exitstatus = 130;
		else
			handle_line(shellstate, line);
		g_lastsig = 0;
		free(line);
		if (shellstate->should_exit)
			break ;
	}
}

int	forkcommanderror(t_pipe_ctx *ctx, int hasnext)
{
	if (hasnext)
	{
		close(ctx->pipefd[0]);
		close(ctx->pipefd[1]);
	}
	return (0);
}
