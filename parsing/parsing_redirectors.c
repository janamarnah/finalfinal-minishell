/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redirectors.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalamarn <jalamarn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 17:00:00 by jalamarn          #+#    #+#             */
/*   Updated: 2026/05/13 14:46:23 by jalamarn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	redir_target_ok(t_token *token)
{
	if (!token || !token->next || token->next->type != WORD)
	{
		write(2, "syntax error near unexpected token `newline'\n", 45);
		return (0);
	}
	return (1);
}

static int	set_input_redir(t_pipeline *pipeline, t_token **token, int i)
{
	int	fd;

	if (!redir_target_ok(*token))
		return (0);
	if (pipeline->commands[i].input_fd != STDIN_FILENO)
		close(pipeline->commands[i].input_fd);
	fd = open((*token)->next->value, O_RDONLY);
	if (fd == -1)
	{
		perror("minishell");
		return (0);
	}
	pipeline->commands[i].input_fd = fd;
	*token = (*token)->next;
	return (1);
}

static int	set_output_redir(t_pipeline *pipeline, t_token **token, int i,
	int flags)
{
	int	fd;

	if (!redir_target_ok(*token))
		return (0);
	if (pipeline->commands[i].output_fd != STDOUT_FILENO)
		close(pipeline->commands[i].output_fd);
	fd = open((*token)->next->value, flags, 0644);
	if (fd == -1)
	{
		perror("minishell");
		return (0);
	}
	pipeline->commands[i].output_fd = fd;
	*token = (*token)->next;
	return (1);
}

int	parse_redir(t_pipeline *pipeline, t_token **tmp_tokens, int i)
{
	int	flags;

	if ((*tmp_tokens)->type == REDIR_IN)
		return (set_input_redir(pipeline, tmp_tokens, i));
	if ((*tmp_tokens)->type == REDIR_OUT)
	{
		flags = O_WRONLY | O_CREAT | O_TRUNC;
		return (set_output_redir(pipeline, tmp_tokens, i, flags));
	}
	if ((*tmp_tokens)->type == REDIR_APPEND)
	{
		flags = O_WRONLY | O_CREAT | O_APPEND;
		return (set_output_redir(pipeline, tmp_tokens, i, flags));
	}
	if ((*tmp_tokens)->type == HEREDOC)
		return (parse_heredoc(pipeline, tmp_tokens, i));
	return (1);
}
