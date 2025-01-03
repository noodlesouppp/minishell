/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yousong <yousong@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 00:51:00 by yousong           #+#    #+#             */
/*   Updated: 2025/01/03 04:19:02 by yousong          ###   ########.fr       */
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

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	int		return_value;

	(void)argv;
	g_envp = envp;
	show_logo();
	return_value = argc;
	while (return_value)
	{
		input = readline("minishell> ");
		printf("%s\n", input);
	}
}
