/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seulogin <seue-mail@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 08:51:24 by smodesto          #+#    #+#             */
/*   Updated: 2021/11/27 09:56:07 by seulogin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H
# define CLEAR "\033[H\033[J"
# define CAPACITY 50000

// store the cmds that will be executed.
typedef struct s_cmd_tab
{
	char	**cmd_splitted;
	char	*history;
}	t_cmd_tab;

#endif
