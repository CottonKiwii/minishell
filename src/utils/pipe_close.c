/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_close.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svereten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 15:50:29 by svereten          #+#    #+#             */
/*   Updated: 2025/01/14 17:06:44 by svereten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	pipe_close(int pipe_fd[2])
{
	ft_close(pipe_fd[RD]);
	ft_close(pipe_fd[WR]);
}
