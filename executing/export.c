/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalamarn <jalamarn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 17:00:00 by jalamarn          #+#    #+#             */
/*   Updated: 2026/05/10 14:44:52 by jalamarn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	export_error(const char *arg, int fd)
{
	ft_putstr_fd("minishell: export: `", fd);
	ft_putstr_fd(arg, fd);
	ft_putstr_fd("': not a valid identifier\n", fd);
}

int	valid_identifier(char *str)
{
	int	i;

	if (!str || (!((str[0] >= 'A' && str[0] <= 'Z')
				|| (str[0] >= 'a' && str[0] <= 'z') || str[0] == '_')))
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!((str[i] >= 'A' && str[i] <= 'Z')
				|| (str[i] >= 'a' && str[i] <= 'z')
				|| (str[i] >= '0' && str[i] <= '9') || str[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

static int	handle_export_arg(char *arg, t_env **env, int fd)
{
	int		valueprovided;
	char	*key;
	char	*value;

	if (!valid_identifier(arg))
	{
		export_error(arg, fd);
		return (1);
	}
	if (parse_export_arg(arg, &key, &value, &valueprovided) != 0)
		return (1);
	if (set_shellenv(env, key, value, valueprovided) != 0)
	{
		free(key);
		free(value);
		return (1);
	}
	free(key);
	free(value);
	return (0);
}

int	builtinexport(char **args, t_env **env, int fd)
{
	int	status;
	int	i;

	if (!env || !args)
		return (1);
	if (!args[1])
		return (print_export_env(*env, fd));
	status = 0;
	i = 1;
	while (args[i])
	{
		if (handle_export_arg(args[i], env, fd))
			status = 1;
		i++;
	}
	return (status);
}
