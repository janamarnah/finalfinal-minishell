/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipehelpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalamarn <jalamarn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 17:00:00 by jalamarn          #+#    #+#             */
/*   Updated: 2026/05/13 14:30:59 by jalamarn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	isbuiltin(char *cmd)
{
	if (!cmd)
		return (0);
	if (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "cd"))
		return (1);
	if (!ft_strcmp(cmd, "env") || !ft_strcmp(cmd, "exit"))
		return (1);
	if (!ft_strcmp(cmd, "export") || !ft_strcmp(cmd, "pwd"))
		return (1);
	if (!ft_strcmp(cmd, "unset"))
		return (1);
	return (0);
}

int	runbuiltinchild(t_shell *shellstate, char **argv)
{
	if (!shellstate || !argv || !argv[0])
		return (0);
	if (!ft_strcmp(argv[0], "echo"))
		return (builtinecho(argv, STDOUT_FILENO));
	if (!ft_strcmp(argv[0], "cd"))
		return (builtincd(argv, &shellstate->env, STDOUT_FILENO));
	if (!ft_strcmp(argv[0], "env"))
		return (builtinenv(argv, shellstate->env, STDOUT_FILENO));
	if (!ft_strcmp(argv[0], "exit"))
		return (builtinexit(argv, shellstate->exitstatus, STDOUT_FILENO));
	if (!ft_strcmp(argv[0], "export"))
		return (builtinexport(argv, &shellstate->env, STDOUT_FILENO));
	if (!ft_strcmp(argv[0], "pwd"))
		return (builtinpwd(STDOUT_FILENO));
	if (!ft_strcmp(argv[0], "unset"))
		return (builtinunset(argv, &shellstate->env, STDOUT_FILENO));
	return (1);
}

int	envcount(t_env *env)
{
	int	count;

	count = 0;
	while (env)
	{
		if (env->key && env->value)
			count++;
		env = env->next;
	}
	return (count);
}

char	*joinkeyvalue(const char *key, const char *value)
{
	char	*tmp;
	char	*retur;

	tmp = ft_strjoin(key, "=");
	if (!tmp)
		return (NULL);
	retur = ft_strjoin(tmp, value);
	if (!retur)
	{
		free(tmp);
		return (NULL);
	}
	free(tmp);
	return (retur);
}

char	**envtoenvp(t_env *env)
{
	char	**envp;
	int		i;

	i = 0;
	envp = malloc(sizeof(char *) * (envcount(env) + 1));
	if (!envp)
		return (NULL);
	while (env)
	{
		if (env->key && env->value)
		{
			envp[i] = joinkeyvalue(env->key, env->value);
			if (!envp[i])
			{
				free_tab(envp);
				return (NULL);
			}
			i++;
		}
		env = env->next;
	}
	envp[i] = NULL;
	return (envp);
}
