/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalamarn <jalamarn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 17:00:00 by jalamarn          #+#    #+#             */
/*   Updated: 2026/05/13 15:43:49 by jalamarn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	flagprompt(int sig)
{
	(void)sig;
	g_lastsig = SIGINT;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	installsig(void)
{
	struct sigaction	sa;

	sa.sa_handler = flagprompt;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGQUIT, &sa, NULL);
}

void	setup_signals_child(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

int	dispatcherexecute(t_shell *shellstate, t_pipeline *pl)
{
	if (!shellstate || !pl || !pl->commands || pl->num_commands <= 0)
	{
		shellstate->exitstatus = 1;
		return (1);
	}
	if (pl->num_commands == 1)
		return (executesinglecmd(shellstate, &pl->commands[0]));
	return (executepipeline(shellstate, pl));
}
