/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svereten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 15:08:58 by svereten          #+#    #+#             */
/*   Updated: 2025/02/18 16:42:35 by svereten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "command.h"
#include "minishell.h"
#include <errno.h>
#include <stdio.h>
#include <sys/wait.h>

static void	execute_single(void)
{
	int	s;

	#if DEBUG
		dprintf(STDERR_FILENO, "Executing single command\n");
	#endif
	if (data(GET)->commands[0]->type == BIN)
	{
		if (!cmd_execute_single_bin(data(GET)->commands[0]))
		{
			data(GET)->exit_code = 1;
			return ;
		}
		if (waitpid(data(GET)->commands[0]->pid, &s, 0) < 0)
			minishell_exit(1, NULL);
		if (WIFEXITED(s))
			data(GET)->exit_code = WEXITSTATUS(s);
	}
	else
		cmd_execute_single_builtin(data(GET)->commands[0]);
}

static void	execute_pipeline(void)
{
	int		i;
	int		status;

	i = 0;
	stdfd_copy();
	while (i < data(GET)->cmd_amount)
	{
		if (!cmd_execute(data(GET)->commands[i]))
			break ;
		i++;
	}
	stdfd_restore();
	if (waitpid(data(GET)->commands[data(GET)->cmd_amount - 1]->pid, &status, 0) < 0)
		minishell_exit(1, NULL);
	if (WIFEXITED(status))
		data(GET)->exit_code = WEXITSTATUS(status);
	while (wait(NULL) > 0)
		;
	if (errno != ECHILD)
		minishell_exit(1, NULL);
	errno = 0;
}

static void	execute(void)
{
	if (data(GET)->cmd_amount == 1)
		execute_single();
	else
		execute_pipeline();
	commands_reset();
}

void	executor(void)
{
	#if DEBUG
		dprintf(STDERR_FILENO, "Executor\n");
		dprintf(STDERR_FILENO, "Amount of commands: %d\n", data(GET)->cmd_amount);
	#endif
	data(GET)->mode = IN_HEREDOC;
	if (!commands_heredocs_run())
		return ;
	execute();
}
