/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_fill.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalamarn <jalamarn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 17:00:00 by jalamarn          #+#    #+#             */
/*   Updated: 2026/05/07 17:00:00 by jalamarn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_words_until_pipe(t_token *tokens)
{
	int	count;

	count = 0;
	while (tokens && tokens->type != PIPE && tokens->type != T_EOF)
	{
		if (is_redir_token(tokens->type) && tokens->next)
			tokens = tokens->next;
		else if (tokens->type == WORD)
			count++;
		tokens = tokens->next;
	}
	return (count);
}

static int	fill_command_args(t_pipeline **pipeline, t_token *tokens, int i)
{
	int	j;

	j = 0;
	while (tokens && tokens->type != T_EOF && tokens->type != PIPE)
	{
		if (is_redir_token(tokens->type))
		{
			if (!parse_redir(*pipeline, &tokens, i))
			{
				(*pipeline)->commands[i].args[j] = NULL;
				return (0);
			}
		}
		else if (tokens->type == WORD)
		{
			(*pipeline)->commands[i].args[j] = ft_strdup(tokens->value);
			if (!(*pipeline)->commands[i].args[j])
				return ((*pipeline)->commands[i].args[j] = NULL, 0);
			j++;
		}
		tokens = tokens->next;
	}
	(*pipeline)->commands[i].args[j] = NULL;
	return (1);
}

static int	fill_one_command(t_pipeline **pipeline, t_token *start, int i)
{
	int	count_words;

	count_words = count_words_until_pipe(start);
	(*pipeline)->commands[i].args = malloc(sizeof(char *) * (count_words + 1));
	if (!(*pipeline)->commands[i].args)
		return (0);
	return (fill_command_args(pipeline, start, i));
}

int	fill_command(t_pipeline **pipeline, t_token *tokens)
{
	t_token	*tmp;
	t_token	*cmd_start;
	int		i;

	i = 0;
	tmp = tokens;
	while (tmp && tmp->type != T_EOF)
	{
		cmd_start = tmp;
		while (tmp && tmp->type != PIPE && tmp->type != T_EOF)
			tmp = tmp->next;
		if (!fill_one_command(pipeline, cmd_start, i))
			return (0);
		i++;
		if (tmp && tmp->type == PIPE)
			tmp = tmp->next;
	}
	return (1);
}
