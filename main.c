/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yousong <yousong@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 00:51:00 by yousong           #+#    #+#             */
/*   Updated: 2025/01/23 22:16:21 by yousong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**g_envp = NULL;

void	show_logo(void)
{
	int		fd;
	char	*line;

	fd = open("utils/ascii.txt", O_RDONLY);
	line = get_next_line(fd);
	while (get_next_line(fd))
	{
		printf("%s", line);
		free(line);
	}
	printf("\n");
	close(fd);
}

void	run_minishell(void)
{
	char	*line;
	t_cmd	*cmd;

	while (1)
	{
//		set_echoctl(0);
//		set_handler(print_prompt, NULL);
		line = readline("minishell> ");
		if (line)
		{
			if (line[0] != '\0')
				add_history(line);
			cmd = parse_cmd(line);
			free(line);
			line = NULL;
//			if (cmd)
//				execute_cmd(cmd);
		}
		else
		{
			printf("exiting\n");
			break ;
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	show_logo();
//	set_envlist(envp);
	run_minishell();
	rl_clear_history();
//	free_envlist();
	return (0);
}

/*void	show_prompt(void)
{
	static char	*curpath;

	ft_putstr_fd(getcwd(curpath, MAXSIZE), STDIN);
	ft_putstr_fd("> ", STDOUT);
}
*/