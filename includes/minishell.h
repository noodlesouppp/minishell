/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yousong <yousong@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 02:40:46 by yousong           #+#    #+#             */
/*   Updated: 2025/02/04 00:55:25 by yousong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <errno.h>
# include <unistd.h>
# include <fcntl.h>
# include <termios.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/stat.h>

# include "../libs/libft/libft.h"
# include "../libs/get_next_line/get_next_line.h"

# include "../includes/parser.h"
# include "../includes/environment.h"
# include "../includes/utils.h"
# include "../includes/signals.h"
# include "../includes/execute.h"
# include "../includes/builtins.h"

enum	e_str_type {word, pipeline, redirect};

typedef struct s_cmd
{
	char			**input;
	int				type;
	int				pipe_count;
	int				unit_count;
	struct s_cmd	*next;
}	t_cmd;

void	run_minishell(void);
void	show_logo(void);

#endif