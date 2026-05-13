/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalamarn <jalamarn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 17:00:00 by jalamarn          #+#    #+#             */
/*   Updated: 2026/05/13 19:23:54 by jalamarn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_lastsig = 0;

static t_env	*env_node_from_str(char *str)
{
	t_env	*node;
	char	*eq;

	eq = ft_strchr(str, '=');
	if (!eq)
		return (NULL);
	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = ft_substr(str, 0, eq - str);
	node->value = ft_strdup(eq + 1);
	if (!node->key || !node->value)
	{
		free(node->key);
		free(node->value);
		free(node);
		return (NULL);
	}
	node->next = NULL;
	return (node);
}

static t_env	*init_env(char **envp)
{
	t_env	*head;
	t_env	*node;
	int		i;

	i = 0;
	head = NULL;
	if (!envp)
		return (NULL);
	while (envp[i])
	{
		node = env_node_from_str(envp[i]);
		if (node)
		{
			node->next = head;
			head = node;
		}
		i++;
	}
	return (head);
}

static void	free_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		free(env->key);
		free(env->value);
		free(env);
		env = tmp;
	}
}

int	handle_line(t_shell *shellstate, char *line)
{
	t_token		*tokens;
	t_pipeline	*pl;

	pl = NULL;
	if (*line == '\0')
		return (0);
	add_history(line);
	tokens = lexing(line, shellstate);
	if (ifsmain(shellstate, tokens, &pl) == 1)
		return (1);
	shellstate->exitstatus = dispatcherexecute(shellstate, pl);
	free_pipeline(pl);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shellstate;

	(void)argc;
	(void)argv;
	shellstate.exitstatus = 0;
	shellstate.should_exit = 0;
	shellstate.env = init_env(envp);
	installsig();
	mainhelper(&shellstate);
	free_env(shellstate.env);
	clear_history();
	return (shellstate.exitstatus);
}
