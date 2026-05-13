/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalamarn <jalamarn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 17:00:00 by jalamarn          #+#    #+#             */
/*   Updated: 2026/05/07 17:00:00 by jalamarn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*append_char_local(char *dst, char c)
{
	char	tmp[2];
	char	*joined;

	tmp[0] = c;
	tmp[1] = '\0';
	joined = ft_strjoin(dst, tmp);
	free(dst);
	return (joined);
}

static char	*expand_single_quotes(char *result, char *word, int *x)
{
	(*x)++;
	while (word[*x] && word[*x] != '\'')
		result = append_char_local(result, word[(*x)++]);
	if (word[*x] == '\'')
		(*x)++;
	return (result);
}

static char	*expand_double_quotes(char *result, char *word, int *x,
	t_shell *shellstate)
{
	(*x)++;
	while (word[*x] && word[*x] != '"')
	{
		if (word[*x] == '$')
			result = expand_variable(result, word, x, shellstate);
		else
			result = append_char_local(result, word[(*x)++]);
	}
	if (word[*x] == '"')
		(*x)++;
	return (result);
}

char	*expand_word(char *word, t_shell *shellstate)
{
	char	*result;
	int		x;

	x = 0;
	result = ft_strdup("");
	while (result && word[x])
	{
		if (word[x] == '\'')
			result = expand_single_quotes(result, word, &x);
		else if (word[x] == '"')
			result = expand_double_quotes(result, word, &x, shellstate);
		else if (word[x] == '$')
			result = expand_variable(result, word, &x, shellstate);
		else
			result = append_char_local(result, word[x++]);
	}
	return (result);
}
