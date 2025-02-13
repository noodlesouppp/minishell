/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yousong <yousong@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 00:51:00 by yousong           #+#    #+#             */
/*   Updated: 2025/02/13 20:42:11 by yousong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

t_env	*g_env;

void	show_logo(void)
{
	int		fd;
	char	*line;

	fd = open("utils/ascii.txt", O_RDONLY);
	while ((line = get_next_line(fd)))
	{
		printf("%s", line);
		free(line);
	}
	printf("\n");
	close(fd);
}

void	run_minishell(t_env *env)
{
	t_cmd	*cmd;
	char	*line;
	int		exit_stat;

	exit_stat = 0;
	while (1)
	{
		set_echoctl(0);
		set_handler(print_prompt, NULL);
		line = readline("minishell> ");
		if (line)
		{
			if (line[0] != '\0')
				add_history(line);
			cmd = parse_cmd(line, exit_stat, env);
			free(line);
			line = NULL;
			// if (cmd)
			// {
			// 	t_cmd	*tmp = cmd;
			// 	while (tmp)
			// 	{
			// 		printf("Parsed command segment:\n");
			// 		for (int i = 0; tmp->input[i]; i++) // Print each argument
			// 			printf("  Arg[%d]: \"%s\"\n", i, tmp->input[i]);
					
			// 		printf("  Type: %d | Pipe Count: %d | Unit Count: %d\n",
			// 			tmp->type, tmp->pipe_count, tmp->unit_count);

			// 		tmp = tmp->next;
			// 	}
			// }
			if (cmd) {
				printf("env var: %s", cmd->env->key);
				process(cmd, &exit_stat);
			}
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

	for (t_env *tmp = env; tmp; tmp = tmp->next)
	run_minishell(env);
	rl_clear_history();
	free_envlist(env);
	return (0);
}
