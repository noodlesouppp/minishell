/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yousong <yousong@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 00:03:35 by yousong           #+#    #+#             */
/*   Updated: 2025/02/15 07:15:08 by yousong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

int	cd(t_cmd *cmd)
{
	char	*path;

	if (!cmd->input[1])
	{
		path = get_env("HOME", cmd->env);
		if (!path)
			return (err_print("cd: ", "HOME not set", NULL, 1));
	}
	else
		path = cmd->input[1];
	if (chdir(path) < 0)
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		return (1);
	}
	return (0);
}
