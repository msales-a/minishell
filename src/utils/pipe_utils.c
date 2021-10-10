/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msales-a <msales-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 13:29:43 by msales-a          #+#    #+#             */
/*   Updated: 2021/10/10 16:09:36 by msales-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	*pipe_create(void)
{
	int	*p;

	p = malloc(sizeof(int) * 2);
	if (!p)
		exit_minishell();
	if (pipe(p) == -1)
		exit_minishell();
	return (p);
}

void	pipe_free(int *p)
{
	if (!p)
		return ;
	close(p[1]);
	close(p[0]);
	free(p);
}

void	pipe_set_writer(int *p)
{
	if (!p)
		return ;
	if (dup2(p[1], STDOUT_FILENO) == -1)
		exit_minishell();
}

void	pipe_set_reader(int *p)
{
	if (!p)
		return ;
	if (dup2(p[0], STDIN_FILENO) == -1)
		exit_minishell();
}