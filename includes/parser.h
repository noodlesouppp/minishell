/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yousong <yousong@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 22:18:00 by yousong           #+#    #+#             */
/*   Updated: 2025/01/30 16:50:39 by yousong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../includes/minishell.h"

# define SQOUTE			1
# define DQOUTE			2

# define PIPE			1
# define REDIR			2
# define D_REDIR		3

t_cmd	*parse_cmd(char *line);

char	**get_space_token(char *line);
int		count_space(char *line);
int		tokenise_space(char **token, char *line, int *index, int *start);

int		is_in_quote(char *line, int idx);
int		is_cmd(char *line, int i);
void	free_tokens(char **tokens);

int		check_error(char **token);
int		print_error(char *msg);

char	**get_cmd_token(char **line);
int		cmd_space(char **line);
void	check_for_cmd(char *line, int *i, int *count);
int		tokenise_cmd(char **token, char *line, int i, int *idx);


#endif