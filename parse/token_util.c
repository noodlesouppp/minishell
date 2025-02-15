/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yousong <yousong@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 07:32:27 by yousong           #+#    #+#             */
/*   Updated: 2025/02/15 07:41:26 by yousong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

void	handle_d_redir(t_token *info, int *pos)
{
	if (*pos > 0)
		info->t[(*info->i)++] = ft_substr(info->l, info->s, *pos - info->s);
	info->t[(*info->i)++] = ft_substr(info->l, *pos, 2);
	*pos += 1;
	info->s = *pos + 1;
}

void	handle_sp_cmd(t_token *info, int *pos)
{
	if (*pos > 0)
		info->t[(*info->i)++] = ft_substr(info->l, info->s, *pos - info->s);
	info->t[(*info->i)++] = ft_substr(info->l, *pos, 1);
	info->s = *pos + 1;
}
