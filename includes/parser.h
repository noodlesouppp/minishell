/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yousong <yousong@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 22:18:00 by yousong           #+#    #+#             */
/*   Updated: 2025/02/15 07:55:03 by yousong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

# define SQUOTE			1
# define DQUOTE			2

# define PIPE			1
# define REDIR			2
# define D_REDIR		3

typedef struct s_cmd	t_cmd;
typedef struct s_env	t_env;

typedef struct s_token
{
	char	**t;
	char	*l;
	int		*i;
	int		s;
}		t_token;

/* parser.c */
t_cmd		*parse_cmd(char *line, t_env *env);
t_cmd		*get_cmd_info(char **token, t_env *env);
void		init_input(t_cmd *cmd, char **token, int unit);
t_cmd		*init_input_util(t_cmd *cmd, char **token, int *i, int *unit);
void		init_type(t_cmd *cmd);

/* space_token.c */
char		**get_space_token(char *line);
int			count_space(char *line);
int			tokenise_space(char **token, char *line, int *index, int *start);

/* parser_util.c */
int			is_in_quote(char *line, int idx);
int			is_cmd(char *line, int i);
void		free_tokens(char **tokens);
char		**ft_array_dup(char **arr, int len);
char		*rm_quote_strdup(char *s1);

/* parse_error.c */
int			check_error(char **token);
int			print_error(char *msg);

/* cmd_token.c */
char		**get_cmd_token(char **line);
int			cmd_space(char **line);
void		check_for_cmd(char *line, int *i, int *count);
int			tokenise_cmd(char **t, char *l, int pos, int *idx);

/* parse_path.c */
char		**check_path(char **token, t_env *env);
int			expand_token(char **token, int dollar_idx, t_env *env_head);

/* cmd_init.c */
int			cnt_pipe(char **token);
void		remove_quotes(char **input);
void		cmd_lstadd(t_cmd *head);
t_cmd		*cmd_lstinit(void);

/* token_util.c */
void		handle_d_redir(t_token *info, int *pos);
void		handle_sp_cmd(t_token *info, int *pos);

#endif