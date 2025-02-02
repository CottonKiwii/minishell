/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolfram <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 14:25:27 by jwolfram          #+#    #+#             */
/*   Updated: 2025/01/31 14:38:35 by jwolfram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	lexer_double_redir_check(char *prompt)
{
	char	redir;

	redir = prompt[0];
	if (!prompt[1])
		return (lexer_error(prompt[0], 0), 0);
	if (prompt[1] != redir)
	{
		if (isredir(prompt[1]) || prompt[1] == '|')
			return (lexer_error(prompt[1], 0), 0);
		else
			return (1);
	}
	if (prompt[2] && isredir(prompt[2]))
		return (lexer_error(prompt[0], prompt[1]), 0);
	return (1);
}

static int	lexer_redir_check_last(char *prompt)
{
	char	last;
	size_t	i;

	i = 0;
	last = prompt[i];
	while (isspace(prompt[i]))
		i++;
	if (!prompt[i] || isredir(prompt[i]))
		return (lexer_error(last, 0), 0);
	if (prompt[i] == '|')
		return (lexer_error(prompt[i], 0), 0);
	return (1);
}

int	lexer_redir_check(void)
{
	size_t	i;

	i = 0;
	if (!ft_strchr(data(GET)->rl_prompt, '<')
		&& !ft_strchr(data(GET)->rl_prompt, '>'))
		return (1);
	while (data(GET)->rl_prompt[i])
	{
		if (isredir(data(GET)->rl_prompt[i])
			&& valid_operator(data(GET)->rl_prompt, i, 0))
		{
			if (!lexer_double_redir_check(data(GET)->rl_prompt + i))
				return (0);
			i += 2;
			if (!lexer_redir_check_last(data(GET)->rl_prompt + i))
				return (0);
		}
		i++;
	}
	return (1);
}
