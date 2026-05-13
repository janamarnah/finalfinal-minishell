/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalamarn <jalamarn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 17:00:00 by jalamarn          #+#    #+#             */
/*   Updated: 2026/05/07 17:00:00 by jalamarn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	space_finder(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

static int	find_end_of_word(char *line, int *i)
{
	char	quote;

	while (line[*i])
	{
		if (space_finder(line[*i]) || line[*i] == '|'
			|| line[*i] == '<' || line[*i] == '>')
			return (1);
		if (line[*i] == '\'' || line[*i] == '"')
		{
			quote = line[*i];
			(*i)++;
			while (line[*i] && line[*i] != quote)
				(*i)++;
			if (!line[*i])
				return (write(2, "syntax error: unclosed quote\n", 29), 0);
			(*i)++;
		}
		else
			(*i)++;
	}
	return (1);
}

t_token	*word_parser(char *line, int *i, t_shell *shellstate)
{
	t_token	*token;
	char	*word;
	char	*raw;
	int		start;

	start = *i;
	if (!find_end_of_word(line, i))
		return (NULL);
	raw = ft_substr(line, start, *i - start);
	if (!raw)
		return (NULL);
	word = expand_word(raw, shellstate);
	free(raw);
	if (!word)
		return (NULL);
	token = token_list_new(WORD, word);
	if (!token)
		return (free(word), NULL);
	return (token);
}
