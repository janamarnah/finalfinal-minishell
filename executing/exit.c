/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalamarn <jalamarn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 17:00:00 by jalamarn          #+#    #+#             */
/*   Updated: 2026/05/13 18:37:38 by jalamarn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	isnumeric(const char *args)
{
	int	i;

	if (!args || !args[0])
		return (0);
	i = 0;
	if (args[i] == '+' || args[i] == '-')
		i++;
	if (!args[i])
		return (0);
	while (args[i])
	{
		if (args[i] < '0' || args[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static long long	ft_atolong(const char *nptr)
{
	int			i;
	long long	ret;
	int			sign;

	i = 0;
	ret = 0;
	sign = 1;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (nptr[i] <= '9' && nptr[i] >= '0')
		ret = ret * 10 + (nptr[i++] - '0');
	return (ret * sign);
}

int	builtinexit(char **args, int laststatus, int fd)
{
	long long	n;

	ft_putstr_fd("exit\n", fd);
	if (!args[1])
		return (laststatus);
	if (!isnumeric(args[1]))
	{
		ft_putstr_fd("minishell: exit: ", fd);
		ft_putstr_fd(args[1], fd);
		ft_putstr_fd(": numeric argument required\n", fd);
		return (2);
	}
	if (args[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", fd);
		return (1);
	}
	n = ft_atolong(args[1]);
	return ((unsigned char)n);
}
