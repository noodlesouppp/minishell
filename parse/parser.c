/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yousong <yousong@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 10:02:03 by yousong           #+#    #+#             */
/*   Updated: 2025/01/30 22:18:31 by yousong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

void	init_type(t_cmd *cmd)
{
	int	cmd_flag;

	while (cmd)
	{
		cmd_flag = is_cmd(cmd->input[0], 0);
		if (cmd_flag > 0)
		{
			if (cmd_flag == 1)
				cmd->type = pipeline;
			else if (cmd_flag > 1)
				cmd->type = redirect;
			else
				cmd->type = word;
		}
		else
			cmd->type = word;
		cmd = cmd->next;
	}
}

/* if special command is not at start, save previous tokens
	*/

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

	i = 0;
	while (token[i++])
	{
		cmd->unit_count = unit;
		if (is_cmd(token[i], 0) > 0)
		{
			cmd = init_input_util(cmd, token, &i, &unit);
			token += i;
			i = 0;
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

t_cmd	*get_cmd_info(char **token)
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
		cmd = cmd->next;
	}
	return (head);
}

t_cmd	*parse_cmd(char *line)
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
		return (NULL);
	}
	token = check_path(token);
	cmd = get_cmd_info(token);
	free_tokens(token);
	return (cmd);
	return (token);
}
