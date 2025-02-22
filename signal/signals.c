/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yousong <yousong@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:02:24 by yousong           #+#    #+#             */
/*   Updated: 2025/02/20 13:14:58 by yousong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/signals.h"
#include <signal.h>

void	print_prompt(int sig)
{
	(void)sig;
	printf("\n");
	g_exit_stat = 130;
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
}

void	print_newline(int sig)
{
	if (sig == SIGINT)
	{
		usleep(1000);
		printf("\n");
		g_exit_stat = 130;
	}
	else if (sig == SIGQUIT)
	{
		usleep(1000);
		printf("Quit (core dumped)\n");
		g_exit_stat = 131;
	}
	rl_on_new_line();
	rl_replace_line("", 1);
}

void	quiet(int sig)
{
	if (sig == SIGINT)
		g_exit_stat = 130;
	else if (sig == SIGQUIT)
		g_exit_stat = 131;
}

void	set_handler(void (*sint_handler)(int s), void (*squit_handler)(int s))
{
	if (sint_handler)
		signal(SIGINT, sint_handler);
	else
		signal(SIGINT, SIG_IGN);
	if (squit_handler)
		signal(SIGQUIT, squit_handler);
	else
		signal(SIGQUIT, SIG_IGN);
}
