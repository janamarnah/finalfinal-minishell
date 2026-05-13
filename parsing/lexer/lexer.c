/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalamarn <jalamarn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 17:00:00 by jalamarn          #+#    #+#             */
/*   Updated: 2026/05/07 17:00:00 by jalamarn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	end_of_file_token(t_token **token_list)
{
	t_token	*token;

	token = token_list_new(T_EOF, NULL);
	if (!token)
	{
		lst_clear(token_list);
		return ;
	}
	ft_lstadd_back(token_list, token);
}

static int	handle_operator(t_token **token_list, char *line, int *i)
{
	if (line[*i] == '<')
		return (handle_redirect_in(token_list, line, i));
	else if (line[*i] == '>')
		return (handle_redirect_out(token_list, line, i));
	else if (line[*i] == '|')
		return (handle_pipe(token_list, i));
	return (1);
}

static int	handle_word(t_token **list, int *i, char *line, t_shell *shell)
{
	t_token	*token;

	token = word_parser(line, i, shell);
	if (!token)
	{
		lst_clear(list);
		return (0);
	}
	ft_lstadd_back(list, token);
	return (1);
}

t_token	*lexing(char *line, t_shell *shellstate)
{
	t_token	*token_list;
	int		i;

	if (!line || !*line)
		return (NULL);
	token_list = NULL;
	i = 0;
	while (line[i])
	{
		if (space_finder(line[i]))
			i++;
		else if (line[i] == '<' || line[i] == '>' || line[i] == '|')
		{
			if (!handle_operator(&token_list, line, &i))
				return (NULL);
		}
		else if (!handle_word(&token_list, &i, line, shellstate))
			return (NULL);
	}
	end_of_file_token(&token_list);
	return (token_list);
}
