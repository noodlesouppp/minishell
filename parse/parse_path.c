/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yousong <yousong@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 10:14:52 by yousong           #+#    #+#             */
/*   Updated: 2025/03/01 23:04:59 by yousong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"
#include "../includes/utils.h"

/* finds the value of the env variable 
	if $? returns exit status instead 
	returns empty string when none found (like bash does) */

char	*find_env(char *key, t_env *env_head)
{
	char	*env;

	if (is_equal(key, "?"))
		env = ft_itoa(env_head->exit_stat);
	else
	{
		if (get_env(key, env_head))
			env = ft_strdup(get_env(key, env_head));
		else
			env = ft_strdup("");
	}
	return (env);
}

/* extracts variable name from the string e.g. "HOME_123" from "$HOME_123" */

static int	find_key(char *start, char **key)
{
	int	len;

	len = 0;
	while (ft_isalnum(start[len]) || start[len] == '?' || start[len] == '_')
		len++;
	if (len == 0)
		return (0);
	*key = ft_substr(start, 0, len);
	return (len);
}

/* replaces the env variable with its value
	joins the variable value onto token string then appends the rest
	returns the new index after expansion */

int	expand_token(char **token, int dollar_idx, t_env *env_head)
{
	char	*key;
	char	*env;
	char	*result;
	char	*tmp;
	int		len;

	len = find_key((*token) + dollar_idx + 1, &key);
	if (len == 0)
		return (dollar_idx + 1);
	env = find_env(key, env_head);
	(*token)[dollar_idx] = '\0';
	result = ft_strjoin(*token, env);
	tmp = result;
	result = ft_strjoin(tmp, &(*token)[dollar_idx + len + 1]);
	free(tmp);
	free(key);
	free(*token);
	len = ft_strlen(env);
	free(env);
	*token = result;
	return (dollar_idx + len);
}

/* iterates over each character in each index, checks for env variables
	makes sure its not in squotes or if prev token is heredoc (<<)
	adjusts index if expansion ends with $ or is empty */

char	**check_path(char **token, t_env *env)
{
	int	i;
	int	j;

	i = -1;
	while (token[++i])
	{
		j = -1;
		while (token[i][++j])
		{
			if (token[i][j] == '$' && is_in_quote(token[i], j) != SQUOTE
				&& token[i][j + 1] != '\'')
			{
				if (i > 0 && is_equal(token[i - 1], "<<"))
					continue ;
				j = expand_token(&token[i], j, env);
				if (token[i][j] == '\0' || token[i][j] == '$')
					j--;
			}
		}
	}
	return (token);
}
