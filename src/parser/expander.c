/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolfram <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 16:59:06 by jwolfram          #+#    #+#             */
/*   Updated: 2025/01/14 13:23:22 by jwolfram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*exp_new_str_init(char	*old)
{
	char	*new;

	if (!old)
		return (NULL);
	if (!ft_strcmp(old, "$?"))
	{
		new = ft_itoa(data(GET)->exit_code);
		if (!new)
			minishell_exit(1, NULL);
	}
	else
	{
		new = ft_getenv(old + 1);
		if (new)
			new = ft_strdup(new);
	}
	return (new);
}

static char	*exp_find_str(char *str)
{
	char	*res;
	size_t	len;

	len = 1;
	while (str[len] && (str[len] == '_' || ft_isalpha(str[len])))
		len++;
	res = ft_substr(str, 0, len);
	if (!res)
		minishell_exit(1, NULL);
	return (res);
}

static char	*exp_old_str_init(char *str)
{
	size_t	i;
	char	*res;

	i = 0;
	res = NULL;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] && valid_operator(str, i, '\''))
		{
			if (str[i + 1] == '?')
				res = ft_strdup("$?");
			else if (ft_isalpha(str[i + 1]) || str[i + 1] == '_')
				res = exp_find_str(str + i);
			break ;
		}
		i++;
	}
	return (res);
}

void	expander_init(t_token *token)
{
	char	*old_str;
	char	*new_str;

	while (token)
	{
		while (token->tok_type == WORD && ft_strchr(token->tok_str, '$'))
		{
			old_str = exp_old_str_init(token->tok_str);
			if (!old_str)
				break ;
			new_str = exp_new_str_init(old_str);
			token->tok_str = substrrplc(token->tok_str, old_str, new_str);
		}
		token = token->next;
	}
}
