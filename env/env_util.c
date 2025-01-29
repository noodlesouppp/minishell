/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yousong <yousong@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 12:36:30 by yousong           #+#    #+#             */
/*   Updated: 2025/01/28 12:38:43 by yousong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/environment.h"

char	*get_env(char *key)
{
	t_env	*tmp;

	tmp = g_env;
	while (tmp)
	{
		if (is_equal(tmp->key, key))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}