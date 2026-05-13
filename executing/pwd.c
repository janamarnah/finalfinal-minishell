/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalamarn <jalamarn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 17:00:00 by jalamarn          #+#    #+#             */
/*   Updated: 2026/05/10 14:47:06 by jalamarn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtinpwd(int fd)
{
	char	str[MAXPATH];

	if (getcwd(str, MAXPATH) == NULL)
	{
		errormsg("pwd", "No such file or directory", fd);
		return (1);
	}
	ft_putstr_fd(str, fd);
	ft_putchar_fd('\n', fd);
	return (0);
}
