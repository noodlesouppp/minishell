/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yousong <yousong@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 17:31:17 by yousong           #+#    #+#             */
/*   Updated: 2025/02/18 16:28:27 by yousong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

static void	print_env(t_cmd *cmd)
{
	t_env	*tmp;

	tmp = cmd->env;
	while (tmp)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(tmp->key, 1);
		if (tmp->value)
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(tmp->value, 1);
			ft_putstr_fd("\"", 1);
		}
		ft_putstr_fd("\n", 1);
		tmp = tmp->next;
	}
}

int	export(t_cmd *cmd)
{
	int		i;

	if (!cmd->input[1])
	{
		print_env(cmd);
		return (g_exit_stat);
	}
	i = 1;
	while (cmd->input[i])
	{
		if (!ft_isalpha(cmd->input[i][0]))
		{
			err_print("export: '", cmd->input[i],
				"': not a valid identifier", 1);
			g_exit_stat = 1;
		}
		else if (add_env(cmd->input[i], &cmd->env) < 0)
		{
			g_exit_stat = 1;
		}
		i++;
	}
	return (g_exit_stat);
}
