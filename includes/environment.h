/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yousong <yousong@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 11:27:42 by yousong           #+#    #+#             */
/*   Updated: 2025/01/31 15:49:05 by yousong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

# include "../includes/minishell.h"

# include "../libs/libft/libft.h"
# include <stdio.h>

/*  key: name of environment variable (e.g., "PATH") 
	value: value associated with the key (e.g., "/usr/bin:/bin") 
	exit_stat: error no. of exit status 
	next: pointer to next node	*/

typedef struct	s_env
{
	char			*key;
	char			*value;
	int				*exit_stat;
	struct s_env	*next;
}	t_env;

extern t_env	*g_env;

char	*get_env(char *key);

#endif