/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalamarn <jalamarn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 17:00:00 by jalamarn          #+#    #+#             */
/*   Updated: 2026/05/07 17:00:00 by jalamarn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_args(char **args)
{
	int	j;

	if (!args)
		return ;
	j = 0;
	while (args[j])
		free(args[j++]);
	free(args);
}

void	free_pipeline(t_pipeline *pipeline)
{
	int	i;

	if (!pipeline)
		return ;
	i = 0;
	while (pipeline->commands && i < pipeline->num_commands)
	{
		free_args(pipeline->commands[i].args);
		if (pipeline->commands[i].input_fd != STDIN_FILENO)
			close(pipeline->commands[i].input_fd);
		if (pipeline->commands[i].output_fd != STDOUT_FILENO)
			close(pipeline->commands[i].output_fd);
		i++;
	}
	free(pipeline->commands);
	free(pipeline);
}

int	command_counter(t_token *tokens)
{
	int	i;

	if (!tokens)
		return (0);
	i = 1;
	while (tokens && tokens->type != T_EOF)
	{
		if (tokens->type == PIPE)
			i++;
		tokens = tokens->next;
	}
	return (i);
}
