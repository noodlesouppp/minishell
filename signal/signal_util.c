/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yousong <yousong@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 00:24:09 by yousong           #+#    #+#             */
/*   Updated: 2025/02/25 20:46:03 by yousong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "../includes/signals.h"

void	heredoc_quiet(int sig)
{
	if (sig == SIGINT)
		g_exit_stat = 1;
	rl_replace_line("", 1);
}

void	heredoc_sigint(int sig)
{
	(void)sig;
	printf("^C\n");
	rl_on_new_line();
	rl_replace_line("", 1);
	g_exit_stat = 130;
	close(STDIN_FILENO);
}

void	set_echoctl(int mode)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	if (mode)
		term.c_lflag |= ECHOCTL;
	else
		term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}
