/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yousong <yousong@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 05:44:56 by yousong           #+#    #+#             */
/*   Updated: 2025/01/29 05:45:32 by yousong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

t_cmd	*cmd_lstinit(void)
{
	t_cmd	*new;

	new = (t_cmd *)malloc(sizeof(t_cmd));
	if (new == 0)
		return (0);
	new->input = NULL;
	new->type = 0;
	new->pipe_count = 0;
	new->unit_count = 0;
	new->next = NULL;
	return (new);
}

void	cmd_lstadd(t_cmd *head)
{
	t_cmd	*node;

	node = cmd_lstinit();
	head->next = node;
	node->next = NULL;
}

void	remove_quotes(char **input)
{
	char	*temp;

	while (*input)
	{
		temp = *input;
		*input = no_quote_strdup(*input);
		input++;
		free(temp);
	}
}

int	cnt_pipe(char **token)
{
	int	i;
	int	cnt;

	cnt = 0;
	while (*token)
	{
		i = 0;
		while ((*token)[i])
		{
			if ((*token)[i] == '|' && is_in_quote(*token, i) == 0)
				cnt++;
			i++;
		}
		token++;
	}
	return (cnt);
}