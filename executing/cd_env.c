/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalamarn <jalamarn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 17:00:00 by jalamarn          #+#    #+#             */
/*   Updated: 2026/05/10 14:43:55 by jalamarn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*findenv(t_env *env, const char	*key)
{
	while (env)
	{
		if (env->key && ft_strcmp(key, env->key) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

t_env	*newenv(const char *key, const char *value)
{
	t_env	*node;

	node = (t_env *)malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = ft_strdup(key);
	if (!node->key)
		return (free(node), NULL);
	if (value)
	{
		node->value = ft_strdup(value);
		if (!node->value)
			return (free(node->key), free(node), NULL);
	}
	else
		node->value = NULL;
	node->next = NULL;
	return (node);
}

void	addnode(t_env **env, t_env *node)
{
	t_env	*tmp;

	if (!env || !node)
		return ;
	if (!*env)
	{
		*env = node;
		return ;
	}
	tmp = (*env);
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = node;
}
