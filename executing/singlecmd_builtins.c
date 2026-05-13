/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singlecmd_builtins.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalamarn <jalamarn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 17:00:00 by jalamarn          #+#    #+#             */
/*   Updated: 2026/05/13 15:44:58 by jalamarn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	runbuiltinparent(t_shell *shellstate, t_command *cmd)
{
	char	**argv;
	int		status;

	argv = cmd->args;
	if (!ft_strcmp(argv[0], "echo"))
		return (builtinecho(argv, STDOUT_FILENO));
	if (!ft_strcmp(argv[0], "cd"))
		return (builtincd(argv, &shellstate->env, STDOUT_FILENO));
	if (!ft_strcmp(argv[0], "env"))
		return (builtinenv(argv, shellstate->env, STDOUT_FILENO));
	if (!ft_strcmp(argv[0], "exit"))
	{
		status = builtinexit(argv, shellstate->exitstatus, STDOUT_FILENO);
		shellstate->exitstatus = status;
		return (status + 1000);
	}
	if (!ft_strcmp(argv[0], "export"))
		return (builtinexport(argv, &shellstate->env, STDOUT_FILENO));
	if (!ft_strcmp(argv[0], "pwd"))
		return (builtinpwd(STDOUT_FILENO));
	if (!ft_strcmp(argv[0], "unset"))
		return (builtinunset(argv, &shellstate->env, STDOUT_FILENO));
	return (1);
}
