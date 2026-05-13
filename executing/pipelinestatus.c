/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_status.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalamarn <jalamarn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 17:00:00 by jalamarn          #+#    #+#             */
/*   Updated: 2026/05/13 14:32:16 by jalamarn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	convertstatus(int stat)
{
	if (WIFEXITED(stat))
		return (WEXITSTATUS(stat));
	if (WIFSIGNALED(stat))
		return (128 + (WTERMSIG(stat)));
	return (1);
}

int	waitpipeline(pid_t *pid, int count)
{
	int	rawst;
	int	status;
	int	i;

	status = 0;
	i = 0;
	while (i < count)
	{
		if (waitpid(pid[i], &rawst, 0) != -1 && i == count - 1)
			status = convertstatus(rawst);
		i++;
	}
	return (status);
}
