/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svereten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 11:51:25 by jwolfram          #+#    #+#             */
/*   Updated: 2025/02/21 14:54:57 by svereten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

void	parser(void)
{
	size_t		i;

	i = 0;
	prompt_init();
	while (data(GET)->prompt[i])
	{
		data(GET)->prompt[i]->idx = i;
		expander_init(data(GET)->prompt[i]);
		token_init(data(GET)->prompt[i]);
		quotes_rm_init(data(GET)->prompt[i]->first);
		i++;
	}
	command_table_init();
}
