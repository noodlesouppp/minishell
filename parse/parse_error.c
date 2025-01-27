/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yousong <yousong@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 12:49:04 by yousong           #+#    #+#             */
/*   Updated: 2025/01/27 16:38:04 by yousong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

int	check_error(char **token)
{
	if (is_cmd(*token, 0) == PIPE)
		return (print_error("syntax error near command"));
	while (*token)
	{
		if (is_cmd(*token, 0) == REDIR || is_cmd(*token, 0) == D_REDIR)
		{
			if (*(token + 1) == NULL || is_cmd(*(token + 1), 0) > 2)
				return (print_error("syntax error near redirection"));
		}
		if (is_cmd(*token, 0) == PIPE)
			if (*(token + 1) == NULL || is_cmd(*(token + 1), 0) == PIPE)
				return (print_error("syntax error near pipe"));
		if (is_in_quote(*token, ft_strlen(*token)))
			return (print_error("syntax error near quote"));
		token++;
	}
	return (0);
}

int	print_error(char *msg)
{
	printf("minishell: %s\n", msg);
	return (-1);
}