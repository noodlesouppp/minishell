/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yousong <yousong@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 00:11:01 by yousong           #+#    #+#             */
/*   Updated: 2025/02/04 00:11:34 by yousong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

static void	del_env(char *key)
{
	t_env	*tmp;
	t_env	*prev;

	tmp = g_env;
	prev = NULL;
	while (tmp)
	{
		if (is_equal(tmp->key, key))
		{
			if (!prev)
				g_env = tmp->next;
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
	return ;
}

int	unset(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->input[++i])
		del_env(cmd->input[i]);
	return (0);
}
