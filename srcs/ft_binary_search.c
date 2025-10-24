/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_binary_search.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 13:45:25 by tlavared          #+#    #+#             */
/*   Updated: 2025/10/23 19:09:54 by tlavared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int	*ft_array_binary(t_stack *list)
{
	t_node	*node;
	int		i;
	int		*values;

	node = list->head;
	i = 0;
	values = malloc (sizeof(int ) * list->size);
	if (!values)
		return (NULL);
	while (i < list->size)
	{
		values[i] = node->value;
		node = node->next;
		i++;
	}
	return (values);
}
