/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ht_insert.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 10:11:35 by smodesto          #+#    #+#             */
/*   Updated: 2021/11/27 10:12:01 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Minishell.h"

/*
	insert an intem in the hash table
*/
void	ht_insert(t_ht_tab *ht, char *key, char *value, t_cmd_tab *table)
{
	t_ht_item	*item;
	t_ht_item	*current_item;
	int			index;

	item = create_item(key, value, table);
	index = hash_function(key);
	current_item = ht->items[index];
	if (current_item == NULL)
	{
		if (ht->count == ht->size)
		{
			ft_check_error(1, "INSERT ERROR: HASH TABLE IS FULL", table);
			free_ht_item(item);
			return ;
		}
		ht->items[index] = item;
		ht->count++;
	}
	else if (ft_strncmp(current_item->key, key, ft_strlen(key)) == 0)
		ht->items[index]->value = ft_strdup(value);
	else
		ht_collision(ht, index, item);
	return ;
}