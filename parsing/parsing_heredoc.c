/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalamarn <jalamarn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 17:00:00 by jalamarn          #+#    #+#             */
/*   Updated: 2026/05/07 17:00:00 by jalamarn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	heredoc_target_ok(t_token **token)
{
	if (!token || !*token || !(*token)->next || (*token)->next->type != WORD)
	{
		write(2, "syntax error near unexpected token `newline'\n", 45);
		return (0);
	}
	return (1);
}

static int	read_heredoc_lines(int write_fd, char *delimiter)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
			break ;
		ft_putstr_fd(line, write_fd);
		ft_putchar_fd('\n', write_fd);
		free(line);
	}
	free(line);
	return (1);
}

int	parse_heredoc(t_pipeline *pipeline, t_token **token, int i)
{
	int	fd[2];

	if (!heredoc_target_ok(token))
		return (0);
	if (pipe(fd) == -1)
		return (perror("minishell"), 0);
	read_heredoc_lines(fd[1], (*token)->next->value);
	close(fd[1]);
	if (pipeline->commands[i].input_fd != STDIN_FILENO)
		close(pipeline->commands[i].input_fd);
	pipeline->commands[i].input_fd = fd[0];
	*token = (*token)->next;
	return (1);
}
