/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yousong <yousong@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 00:51:00 by yousong           #+#    #+#             */
/*   Updated: 2025/01/27 16:46:11 by yousong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

//char	**g_envp = NULL;

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
	char	**cmd;
//	t_cmd	*cmd;

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
			for (int i = 0; cmd[i]; i++)
				printf("cmd[%d]: %s\n", i, cmd[i]);
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
	(void)envp;
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