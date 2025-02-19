/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yousong <yousong@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 10:02:03 by yousong           #+#    #+#             */
/*   Updated: 2025/02/19 11:31:03 by yousong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

/* lastly, set if a cmd segment is pipeline, redirect, or word */

void	init_type(t_cmd *cmd)
{
	int	cmd_flag;

	while (cmd)
	{
		cmd_flag = is_cmd(cmd->input[0], 0);
		if (cmd_flag > 0)
		{
			if (cmd_flag == PIPE)
				cmd->type = pipeline;
			else if (cmd_flag >= REDIR)
				cmd->type = redirect;
			else
				cmd->type = word;
		}
		else
			cmd->type = word;
		cmd = cmd->next;
	}
}

/* first checks if token is before special cmd i.e. a word
	if it is, copies as a cmd segment until the special cmd
	if any redirection, instead copy the redirection then advance 2
	otherwise if pipe, copy pipe token, unit_count++, skip over pipe */

t_cmd	*init_input_util(t_cmd *cmd, char **token, int *i, int *unit)
{
	if (*i != 0)
	{
		cmd->input = ft_array_dup(token, *i);
		cmd_lstadd(cmd);
		cmd = cmd->next;
		cmd->unit_count = *unit;
	}
	if (is_cmd(token[*i], 0) >= REDIR)
	{
		cmd->input = ft_array_dup(token + *i, 2);
		*i += 2;
	}
	else if (is_cmd(token[*i], 0) == PIPE)
	{
		cmd->input = ft_array_dup(token + *i, 1);
		(*unit)++;
		(*i)++;
	}
	return (cmd);
}

/* initialises the INPUT for each cmd segment through the linked list
	if token is special cmd, */

void	init_input(t_cmd *cmd, char **token, int unit)
{
	int	i;

	i = -1;
	while (token[++i])
	{
		cmd->unit_count = unit;
		if (is_cmd(token[i], 0) > 0)
		{
			cmd = init_input_util(cmd, token, &i, &unit);
			token += i;
			i = -1;
			if (token[i + 1])
			{
				cmd_lstadd(cmd);
				cmd = cmd->next;
			}
		}
	}
	if (cmd->input == NULL)
	{
		cmd->unit_count = unit;
		cmd->input = ft_array_dup(token, i);
	}
}

/* convert the token array into t_cmd nodes
	and init them into corresponding values
	unit count is for tracking command segments */

t_cmd	*get_cmd_info(char **token, t_env *env)
{
	t_cmd	*cmd;
	t_cmd	*head;
	int		p_cnt;
	int		unit;

	unit = 0;
	cmd = cmd_lstinit();
	head = cmd;
	p_cnt = cnt_pipe(token);
	init_input(cmd, token, unit);
	while (cmd)
	{
		init_type(cmd);
		cmd->pipe_count = p_cnt;
		remove_quotes(cmd->input);
		cmd->env = env;
		cmd = cmd->next;
	}
	return (head);
}

t_cmd	*parse_cmd(char *line, t_env *env)
{
	t_cmd	*cmd;
	char	**token;
	char	**tmp;

	while (*line == ' ')
		line++;
	if (!*line)
		return (NULL);
	token = get_space_token(line);
	tmp = token;
	token = get_cmd_token(tmp);
	free_tokens(tmp);
	if (check_error(token) < 0)
	{
		free_tokens(token);
		g_exit_stat = 2;
		return (NULL);
	}
	token = check_path(token, env);
	cmd = get_cmd_info(token, env);
	free_tokens(token);
	return (cmd);
}
