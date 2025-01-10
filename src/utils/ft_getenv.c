/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolfram <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 12:01:29 by jwolfram          #+#    #+#             */
/*   Updated: 2025/01/10 16:04:47 by jwolfram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(char *key)
{
	t_env_var	*var;

	var = data(GET)->env.first;
	while (var)
	{
		if (!ft_strcmp(key, var->key))
			return (var->value);
		var = var->next;
	}
	return (NULL);
}
