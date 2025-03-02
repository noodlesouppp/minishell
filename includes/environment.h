/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yousong <yousong@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 11:27:42 by yousong           #+#    #+#             */
/*   Updated: 2025/03/01 22:36:36 by yousong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

# include "minishell.h"

# include "../libs/libft/libft.h"
# include <stdio.h>

/*  key: name of environment variable (e.g., "PATH") 
	value: value associated with the key (e.g., "/usr/bin:/bin") 
	next: pointer to next node	*/

typedef struct s_cmd	t_cmd;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
	int				exit_stat;
}	t_env;

/* env_util.c */
char	*get_env(char *key, t_env *env);
char	**env_to_array(t_cmd *cmd);
void	free_envlist(t_env *env);

/* env.c */
t_env	*set_envlist(char **envp);
int		add_env(char *env, t_env **head);

#endif
