/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yousong <yousong@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 00:51:00 by yousong           #+#    #+#             */
/*   Updated: 2025/03/02 00:19:06 by yousong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

volatile sig_atomic_t	g_sig_num = 0;

void	show_logo(void)
{
	int		fd;
	char	*line;

	fd = open("utils/ascii.txt", O_RDONLY);
	if (fd < 0)
		return ;
	line = get_next_line(fd);
	while (line)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	printf("\n");
	close(fd);
}

void	run_minishell(t_env *env)
{
	t_cmd	*cmd;
	char	*line;

	while (1)
	{
		set_echoctl(1);
		set_handler(print_prompt, NULL);
		line = readline("minishell> ");
		if (line)
		{
			if (line[0] != '\0')
				add_history(line);
			cmd = parse_cmd(line, env);
			free(line);
			line = NULL;
			if (cmd)
				process(cmd);
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
	t_env	*env;

	(void)argc;
	(void)argv;
	show_logo();
	env = set_envlist(envp);
	run_minishell(env);
	rl_clear_history();
	free_envlist(env);
	return (0);
}

// void print_cmd(t_cmd *cmd)
// {
// 	t_cmd	*tmp = cmd;
// 	while (tmp)
// 	{
// 		printf("Parsed command segment:\n");
// 		for (int i = 0; tmp->input[i]; i++)
// 			printf("  Arg[%d]: \"%s\"\n", i, tmp->input[i]);
// 		printf("  Type: %d | Pipe Count: %d | Unit Count: %d\n",
// 		tmp->type, tmp->pipe_count, tmp->unit_count);
// 		tmp = tmp->next;
// 	}
// }
