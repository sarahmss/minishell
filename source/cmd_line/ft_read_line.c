/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 11:22:40 by smodesto          #+#    #+#             */
/*   Updated: 2021/12/20 17:50:19 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Minishell.h"

void	ft_read_line(t_cmd_tab *tb)
{
	char	*prompt;

	prompt = create_prompt();
	tb->cmd_line = readline(prompt);
	if (tb->cmd_line == NULL)
		ft_check_error(SIGEXIT, "Ctrl+c", tb);
	if (strlen(tb->cmd_line) != 0)
		add_history(tb->cmd_line);
	free(prompt);
}
