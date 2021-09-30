/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compile_argv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msales-a <msales-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 18:42:57 by msales-a          #+#    #+#             */
/*   Updated: 2021/09/30 18:43:05 by msales-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**compile_argv(t_dlist *args)
{
	size_t	len;
	char	**result;
	size_t	index;

	len = ft_dlstsize(args);
	result = malloc(sizeof(char *) * (len + 1));
	result[len] = NULL;
	index = 0;
	while (args)
	{
		result[index] = ft_strdup(args->content);
		index++;
		args = args->next;
	}
	return (result);
}
