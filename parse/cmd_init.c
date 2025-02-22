/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yousong <yousong@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 05:44:56 by yousong           #+#    #+#             */
/*   Updated: 2025/02/22 15:06:49 by yousong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

/* initialise a clean dummy node for a command token */

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

/* iterates through and removes the quotes from the input tokens */

void	remove_quotes(char **input)
{
	char	*temp;

	if (!input)
		return ;
	while (*input)
	{
		temp = *input;
		if (temp)
		{
			*input = rm_quote_strdup(*input);
			free(temp);
		}
		input++;
	}
}

/* counts number of pipes ONLY if they are not in quotes */

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
