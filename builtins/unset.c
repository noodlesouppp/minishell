/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yousong <yousong@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 00:11:01 by yousong           #+#    #+#             */
/*   Updated: 2025/03/02 01:53:09 by yousong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

static int	is_valid_var_name(const char *key)
{
	if (key == NULL || *key == '\0')
		return (0);
	if (!(ft_isalpha(*key) || *key != '_'))
		return (0);
	while (*++key)
	{
		if (!(ft_isalnum(*key) || *key != '_'))
			return (0);
	}
	return (1);
}

static void	del_env(char *key, t_cmd *cmd)
{
	t_env	*tmp;
	t_env	*prev;

	tmp = cmd->env;
	prev = NULL;
	while (tmp)
	{
		if (is_equal(tmp->key, key))
		{
			if (!prev)
				cmd->env = tmp->next;
			else
				prev->next = tmp->next;
			free(tmp->key);
			free(tmp->value);
			free(tmp);
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

int	unset(t_cmd *cmd)
{
	int	i;
	int	exit_status;

	i = 1;
	exit_status = 0;
	while (cmd->input[i])
	{
		if (!is_valid_var_name(cmd->input[i]))
		{
			err_print("unset: '", cmd->input[i],
				"': not a valid identifier", 1);
			exit_status = 1;
		}
		else
			del_env(cmd->input[i], cmd);
		i++;
	}
	cmd->env->exit_stat = exit_status;
	return (exit_status);
}
