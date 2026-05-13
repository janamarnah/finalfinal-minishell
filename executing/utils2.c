/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalamarn <jalamarn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 19:15:47 by jalamarn          #+#    #+#             */
/*   Updated: 2026/05/13 19:16:58 by jalamarn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	savestdio(int *savein, int *saveout)
{
	*savein = dup(STDIN_FILENO);
	if (*savein < 0)
		return (1);
	*saveout = dup(STDOUT_FILENO);
	if (*saveout < 0)
	{
		close(*savein);
		return (1);
	}
	return (0);
}
