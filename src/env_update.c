/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_update.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolfram <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 11:58:05 by jwolfram          #+#    #+#             */
/*   Updated: 2025/02/25 14:34:51 by jwolfram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_update(void)
{
	char		*cur;
	t_env_var	*env;

	env = data(GET)->env.first;
	while (env)
	{
		cur = ft_getenv(env->key);
		if (ft_strncmp(env->value, cur, ft_strlen(env->value)))
		{
			ft_free(STR, &env->value);
			if (cur)
			{
				env->value = ft_strdup(cur);
				if (!env->value)
					minishell_exit(1, NULL);
			}
		}
		env = env->next;
	}
}
