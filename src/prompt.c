/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lniehues <lniehues@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 20:31:27 by lniehues          #+#    #+#             */
/*   Updated: 2021/09/20 20:53:51 by lniehues         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* TODO check input signals */

static void	save_history(char *input)
{
	if (input && *input)
		add_history(input);
}

char	*create_prompt(void)
{
	t_str_builder	*builder;
	char			*prompt;

	builder = str_builder_init();
	str_builder_add_str(builder, BOLD_RED);
	str_builder_add_str(builder, find_env(g_minishell.penv, "LOGNAME"));
	str_builder_add_char(builder, '@');
	str_builder_add_str(builder, find_env(g_minishell.penv, "NAME"));
	str_builder_add_char(builder, ':');
	str_builder_add_str(builder, ESC_RESET_COLOR);
	str_builder_add_str(builder, BOLD_PURPLE);
	if (ft_strcmp(find_env(g_minishell.penv, "HOME"),
			find_env(g_minishell.penv, "PWD")) == 0)
		str_builder_add_char(builder, '~');
	else
		str_builder_add_str(builder, find_env(g_minishell.penv, "PWD"));
	str_builder_add_str(builder, ESC_RESET_COLOR);
	str_builder_add_str(builder, "$ ");
	prompt = ft_strdup(builder->str);
	str_builder_destroy(builder);
	return (prompt);
}

void	read_input_and_save_history(char **input)
{
	char	*prompt;

	prompt = create_prompt();
	set_input_signals();
	*input = readline(prompt);
	free(prompt);
	save_history(*input);
}