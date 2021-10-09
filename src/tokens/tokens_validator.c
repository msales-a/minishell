/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_validator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msales-a <msales-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 19:45:31 by msales-a          #+#    #+#             */
/*   Updated: 2021/10/09 17:54:54 by msales-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	syntax_error(t_token *token)
{
	char				*line;
	t_token_definition	*tokens;

	line = "minishell: syntax error near unexpected token `";
	tokens = (t_token_definition[]){
	{.id = TD_HERE_DOCUMENT, .value = "<<"}, {.id = TD_AND, .value = "&&"},
	{.id = TD_OR, .value = "||"}, {.id = TD_APPEND_MODE, .value = ">>"},
	{.id = TD_PIPE, .value = "|"}, {.id = TD_OUTPUT, .value = ">"},
	{.id = TD_INPUT, .value = "<"}, {.id = TD_DOUBLE_QUOTE, .value = "\""},
	{.id = TD_SINGLE_QUOTE, .value = "'"}, {.id = TD_SPACE, .value = " "},
	{.id = TD_NEWLINE, .value = "newline"}, {.id = TD_UNKNOWN}};
	ft_putstr_fd(line, STDERR_FILENO);
	while (tokens->id != TD_NEWLINE && (!token || tokens->id != token->id))
		tokens++;
	ft_putstr_fd(tokens->value, STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
}

static bool	redirect_validator(
	t_token *current,
	t_token *next)
{
	if (!current)
		return (true);
	if (current->id != TD_INPUT && current->id != TD_OUTPUT
		&& current->id != TD_APPEND_MODE && current->id != TD_HERE_DOCUMENT)
		return (true);
	if (!next)
		return ((syntax_error(NULL), false));
	if (next->id != TD_WORD
		&& next->id != TD_SINGLE_QUOTE && next->id != TD_DOUBLE_QUOTE)
		return ((syntax_error(next), false));
	return (true);
}

static bool	operator_validator(
	t_token *previous,
	t_token *current,
	t_token *next)
{
	if (!current)
		return (true);
	if (current->id != TD_PIPE
		&& current->id != TD_AND && current->id != TD_OR)
		return (true);
	if (!next)
		return ((syntax_error(NULL), false));
	if (!previous)
		return ((syntax_error(current), false));
	return (true);
}

static bool	verify(t_dlist *previous, t_dlist *current, t_dlist *next)
{
	t_token	*p;
	t_token	*c;
	t_token	*n;

	p = NULL;
	if (previous)
		p = previous->content;
	c = NULL;
	if (current)
		c = current->content;
	n = NULL;
	if (next)
		n = next->content;
	return (redirect_validator(c, n) && operator_validator(p, c, n));
}

bool	tokens_validator(t_dlist *tokens)
{
	t_dlist	*previous;
	t_dlist	*current;
	t_dlist	*next;

	if (!tokens)
		return (false);
	while (tokens)
	{
		previous = previous_token(tokens);
		current = tokens;
		next = next_token_non_space(tokens);
		if (!verify(previous, current, next))
		{
			((t_token *)current->content)->id = TD_UNKNOWN;
			return (false);
		}
		tokens = tokens->next;
	}
	return (true);
}