/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msales-a <msales-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/19 17:33:24 by msales-a          #+#    #+#             */
/*   Updated: 2021/09/19 18:21:22 by msales-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*token_init(int id, char *str_to_copy)
{
	t_token	*token;

	token = malloc(sizeof(token));
	if (!token)
		return (NULL);
	token->id = id;
	token->value = NULL;
	if (str_to_copy)
		token->value = ft_strdup(str_to_copy);
	if (str_to_copy && !token->value)
		return (NULL);
	return (token);
}

void	token_free(void *token)
{
	t_token	*t;

	t = token;
	free(t->value);
	free(t);
}