/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msales-a <msales-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 17:28:08 by msales-a          #+#    #+#             */
/*   Updated: 2021/09/30 22:19:31 by msales-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*static void	configure_and_run_redirect(int *p, t_command *command)
{
	if (command->redirect.type == TD_INPUT
		|| command->redirect.type == TD_HERE_DOCUMENT)
		configure_writer_pipe_and_free(p);
	else
		configure_reader_pipe_and_free(p);
	execute_redirect(command->redirect);
}*/

static pid_t	configure_and_run_call(int *p, t_command *command)
{
	if (command->redirect.type == TD_INPUT
		|| command->redirect.type == TD_HERE_DOCUMENT)
		configure_reader_pipe_and_free(p);
	else
		configure_writer_pipe_and_free(p);
	return (execute_call(command->call));
}

pid_t	execute_command(t_command *command)
{
	int		*p;

	p = NULL;
	/*
	pid_t	child;

	if (command->redirect.type)
	{
		create_pipe(&p);
		child = fork();
		if (child == -1)
			exit_minishell();
		if (child == 0)
			configure_and_run_redirect(p, command);
	}*/
	return (configure_and_run_call(p, command));
}
