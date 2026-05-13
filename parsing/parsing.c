/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalamarn <jalamarn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 17:00:00 by jalamarn          #+#    #+#             */
/*   Updated: 2026/05/13 14:47:22 by jalamarn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redir_token(t_token_type type)
{
	return (type == REDIR_IN || type == REDIR_OUT
		|| type == REDIR_APPEND || type == HEREDOC);
}

static t_pipeline	*initialize_pipeline(int num_commands)
{
	t_pipeline	*pipeline;
	int			i;

	pipeline = malloc(sizeof(t_pipeline));
	if (!pipeline)
		return (NULL);
	pipeline->num_commands = num_commands;
	pipeline->commands = malloc(sizeof(t_command) * num_commands);
	if (!pipeline->commands)
	{
		free(pipeline);
		return (NULL);
	}
	i = 0;
	while (i < num_commands)
	{
		pipeline->commands[i].args = NULL;
		pipeline->commands[i].input_fd = STDIN_FILENO;
		pipeline->commands[i].output_fd = STDOUT_FILENO;
		i++;
	}
	return (pipeline);
}

t_pipeline	*parse_pipeline(t_token *tokens)
{
	t_pipeline	*pipeline;
	int			num_commands;

	if (!syntax_validator(tokens))
		return (NULL);
	num_commands = command_counter(tokens);
	pipeline = initialize_pipeline(num_commands);
	if (!pipeline)
		return (NULL);
	if (!fill_command(&pipeline, tokens))
	{
		free_pipeline(pipeline);
		return (NULL);
	}
	return (pipeline);
}
