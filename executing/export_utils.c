/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalamarn <jalamarn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 17:00:00 by jalamarn          #+#    #+#             */
/*   Updated: 2026/05/10 14:44:46 by jalamarn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sortenv(t_env **env, int counter)
{
	t_env	*tmp;
	int		i;
	int		j;

	i = 0;
	while (i < counter - 1)
	{
		j = 0;
		while (j < counter - 1 - i)
		{
			if (ft_strcmp(env[j]->key, env[j + 1]->key) > 0)
			{
				tmp = env[j];
				env[j] = env[j + 1];
				env[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

static t_env	**copyenv(t_env *env, int *counter)
{
	t_env	**copy;
	t_env	*tmp;
	int		i;

	*counter = 0;
	tmp = env;
	while (tmp)
	{
		(*counter)++;
		tmp = tmp->next;
	}
	copy = malloc(sizeof(t_env *) * (*counter));
	if (!copy)
		return (NULL);
	i = 0;
	while (env)
	{
		copy[i++] = env;
		env = env->next;
	}
	sortenv(copy, *counter);
	return (copy);
}

static void	print_escaped(const char *str, int fd)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '"' || str[i] == '\\')
			ft_putchar_fd('\\', fd);
		ft_putchar_fd(str[i], fd);
		i++;
	}
}

int	print_export_env(t_env *env, int fd)
{
	t_env	**copy;
	int		counter;
	int		i;

	copy = copyenv(env, &counter);
	if (!copy)
		return (1);
	i = 0;
	while (i < counter)
	{
		ft_putstr_fd("declare -x ", fd);
		ft_putstr_fd(copy[i]->key, fd);
		if (copy[i]->value)
		{
			ft_putstr_fd("=\"", fd);
			print_escaped(copy[i]->value, fd);
			ft_putchar_fd('"', fd);
		}
		ft_putchar_fd('\n', fd);
		i++;
	}
	free(copy);
	return (0);
}
