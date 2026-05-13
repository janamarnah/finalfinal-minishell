/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_validator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalamarn <jalamarn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 17:00:00 by jalamarn          #+#    #+#             */
/*   Updated: 2026/05/07 17:00:00 by jalamarn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	pipe_validator(t_token *tokens)
{
	if (tokens->type == PIPE)
		return (0);
	while (tokens && tokens->type != T_EOF)
	{
		if (tokens->type == PIPE)
		{
			if (tokens->next && tokens->next->type == T_EOF)
				return (0);
			if (tokens->next && tokens->next->type == PIPE)
				return (2);
		}
		tokens = tokens->next;
	}
	return (1);
}

static int	redirections_validator(t_token *tokens)
{
	while (tokens && tokens->type != T_EOF)
	{
		if (is_redir_token(tokens->type))
		{
			if (!tokens->next || tokens->next->type != WORD)
				return (0);
		}
		tokens = tokens->next;
	}
	return (1);
}

int	syntax_validator(t_token *tokens)
{
	int	pipe_status;

	if (!tokens || tokens->type == T_EOF)
		return (1);
	pipe_status = pipe_validator(tokens);
	if (pipe_status == 0)
	{
		write(2, "minishell: syntax error near unexpected token `newline'\n",
			57);
		return (0);
	}
	if (pipe_status == 2)
		return (write(2, "syntax error near unexpected token `|'\n", 40), 0);
	if (!redirections_validator(tokens))
	{
		write(2, "syntax error near unexpected token `newline'\n", 46);
		return (0);
	}
	return (1);
}
