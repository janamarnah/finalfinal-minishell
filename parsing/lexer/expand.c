/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalamarn <jalamarn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 17:00:00 by jalamarn          #+#    #+#             */
/*   Updated: 2026/05/07 17:00:00 by jalamarn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_var_char(char c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')
		|| (c >= '0' && c <= '9') || c == '_');
}

static char	*append_env_value(char *result, char *word, int *x,
	t_shell *shellstate)
{
	char	*key;
	t_env	*env;
	int		start;

	start = *x;
	while (is_var_char(word[*x]))
		(*x)++;
	key = ft_substr(word, start, *x - start);
	if (!key)
		return (NULL);
	env = findenv(shellstate->env, key);
	if (env && env->value)
		result = append_expand_str(result, env->value);
	else
		result = append_expand_str(result, "");
	return (free(key), result);
}

char	*expand_variable(char *result, char *word, int *x, t_shell *shellstate)
{
	char	*value;

	(*x)++;
	if (word[*x] == '?')
	{
		value = status_to_str(shellstate->exitstatus);
		result = append_expand_str(result, value);
		return (free(value), (*x)++, result);
	}
	if (word[*x] >= '0' && word[*x] <= '9')
		return ((*x)++, result);
	if (!is_var_char(word[*x]))
		return (append_expand_char(result, '$'));
	return (append_env_value(result, word, x, shellstate));
}
