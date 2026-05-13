/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_set.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalamarn <jalamarn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 17:00:00 by jalamarn          #+#    #+#             */
/*   Updated: 2026/05/10 14:44:40 by jalamarn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	update_existing_env(t_env *found, const char *value,
	int valueprovided)
{
	if (!valueprovided)
		return (0);
	free(found->value);
	if (value)
		found->value = ft_strdup(value);
	else
		found->value = ft_strdup("");
	return (!found->value);
}

static t_env	*new_export_env(const char *key, const char *value,
	int valueprovided)
{
	if (!valueprovided)
		return (newenv(key, NULL));
	if (value)
		return (newenv(key, value));
	return (newenv(key, ""));
}

int	set_shellenv(t_env **env, const char *key, const char *value,
	int valueprovided)
{
	t_env	*found;
	t_env	*node;

	if (!env || !key)
		return (1);
	found = findenv(*env, key);
	if (found)
		return (update_existing_env(found, value, valueprovided));
	node = new_export_env(key, value, valueprovided);
	if (!node)
		return (1);
	addnode(env, node);
	return (0);
}

int	parse_export_arg(const char *arg, char **key, char **value, int *flag)
{
	char	*findeq;
	size_t	keylength;

	*key = NULL;
	*value = NULL;
	*flag = 0;
	findeq = ft_strchr(arg, '=');
	if (!findeq)
	{
		*key = ft_strdup(arg);
		return (!*key);
	}
	keylength = (size_t)(findeq - arg);
	*key = ft_substr(arg, 0, keylength);
	if (!*key)
		return (1);
	*value = ft_strdup(findeq + 1);
	if (!*value)
		return (free(*key), *key = NULL, 1);
	*flag = 1;
	return (0);
}
