/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalamarn <jalamarn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 17:00:00 by jalamarn          #+#    #+#             */
/*   Updated: 2026/05/10 14:56:42 by jalamarn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	unset_error(const char *arg, int fd)
{
	ft_putstr_fd("minishell: unset: `", fd);
	ft_putstr_fd(arg, fd);
	ft_putstr_fd("': not a valid identifier\n", fd);
}

static void	freenode(t_env *node)
{
	if (!node)
		return ;
	free(node->key);
	free(node->value);
	free(node);
}

static void	removekey(t_env **env, const char *key)
{
	t_env	*tmp;
	t_env	*prev;

	if (!env || !*env || !key)
		return ;
	tmp = *env;
	prev = NULL;
	while (tmp)
	{
		if (tmp->key && ft_strcmp(tmp->key, key) == 0)
		{
			if (prev)
				prev->next = tmp->next;
			else
				*env = tmp->next;
			freenode(tmp);
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

int	builtinunset(char **args, t_env **env, int fd)
{
	int	i;
	int	status;

	if (!env || !args)
		return (1);
	i = 1;
	status = 0;
	while (args[i])
	{
		if (!valid_identifier(args[i]))
		{
			unset_error(args[i], fd);
			status = 1;
		}
		else
			removekey(env, args[i]);
		i++;
	}
	return (status);
}
