/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yousong <yousong@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 12:36:30 by yousong           #+#    #+#             */
/*   Updated: 2025/02/15 07:13:29 by yousong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/environment.h"

void	free_envlist(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env;
		env = env->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
}

static char	*node_to_line(t_env *node)
{
	char	*line;
	int		size;

	size = ft_strlen(node->key) + ft_strlen(node->value) + 1;
	line = malloc(sizeof(char) * (size + 1));
	line[0] = '\0';
	ft_strlcat(line, node->key, size + 1);
	ft_strlcat(line, "=", size + 1);
	ft_strlcat(line, node->value, size + 1);
	return (line);
}

static int	env_len(t_cmd *cmd)
{
	t_env	*tmp;
	int		cnt;

	tmp = cmd->env;
	cnt = 0;
	while (tmp)
	{
		cnt++;
		tmp = tmp->next;
	}
	return (cnt);
}

char	**env_to_array(t_cmd *cmd)
{
	t_env	*tmp;
	char	**envp;
	int		env_idx;

	tmp = cmd->env;
	env_idx = 0;
	envp = malloc(sizeof(char *) * (env_len(cmd) + 1));
	while (tmp)
	{
		if (tmp->value)
			envp[env_idx++] = node_to_line(tmp);
		tmp = tmp->next;
	}
	envp[env_idx] = NULL;
	return (envp);
}

char	*get_env(char *key, t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (is_equal(tmp->key, key))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}
