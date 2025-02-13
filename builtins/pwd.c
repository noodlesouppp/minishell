/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yousong <yousong@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 12:10:04 by yousong           #+#    #+#             */
/*   Updated: 2025/02/04 00:09:32 by yousong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

int	pwd(void)
{
	char	*dir;

	dir = getcwd(NULL, 0);
	if (!dir)
	{
		perror(NULL);
		return (1);
	}
	printf("%s\n", dir);
	free(dir);
	return (0);
}
