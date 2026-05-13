/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalamarn <jalamarn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 17:00:00 by jalamarn          #+#    #+#             */
/*   Updated: 2026/05/07 17:00:00 by jalamarn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	add_operator(t_token **token_list, t_token_type type, char *value)
{
	t_token	*token;
	char	*copy;

	copy = ft_strdup(value);
	if (!copy)
	{
		lst_clear(token_list);
		return (0);
	}
	token = token_list_new(type, copy);
	if (!token)
	{
		free(copy);
		lst_clear(token_list);
		return (0);
	}
	ft_lstadd_back(token_list, token);
	return (1);
}

int	handle_redirect_in(t_token **token_list, char *line, int *i)
{
	if (line[*i + 1] && line[*i + 1] == '<')
	{
		if (!add_operator(token_list, HEREDOC, "<<"))
			return (0);
		*i = *i + 2;
		return (1);
	}
	if (!add_operator(token_list, REDIR_IN, "<"))
		return (0);
	(*i)++;
	return (1);
}

int	handle_redirect_out(t_token **token_list, char *line, int *i)
{
	if (line[*i + 1] && line[*i + 1] == '>')
	{
		if (!add_operator(token_list, REDIR_APPEND, ">>"))
			return (0);
		*i = *i + 2;
		return (1);
	}
	if (!add_operator(token_list, REDIR_OUT, ">"))
		return (0);
	(*i)++;
	return (1);
}

int	handle_pipe(t_token **token_list, int *i)
{
	if (!add_operator(token_list, PIPE, "|"))
		return (0);
	(*i)++;
	return (1);
}
