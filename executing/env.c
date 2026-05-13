/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalamarn <jalamarn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 17:00:00 by jalamarn          #+#    #+#             */
/*   Updated: 2026/05/10 14:44:22 by jalamarn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtinenv(char **argv, t_env *env, int fd)
{
	if (argv[1])
	{
		errormsg("env", "too many arguments", fd);
		return (1);
	}
	while (env)
	{
		if (env->value)
		{
			ft_putstr_fd(env->key, fd);
			ft_putchar_fd('=', fd);
			ft_putstr_fd(env->value, fd);
			ft_putchar_fd('\n', fd);
		}
		env = env->next;
	}
	return (0);
}
