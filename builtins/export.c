/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yousong <yousong@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 17:31:17 by yousong           #+#    #+#             */
/*   Updated: 2025/02/15 07:15:55 by yousong          ###   ########.fr       */
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
	char	*str;

	str = cmd->input[1];
	if (str)
	{
		if (!ft_isalpha(str[0]))
		{
			err_print("export: '", str, "': not a valid identifier", 1);
			return (1);
		}
		if (add_env(str, &cmd->env) < 0)
			return (1);
	}
	else
		print_env(cmd);
	return (0);
}
