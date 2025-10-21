/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_small.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 19:48:23 by tlavared          #+#    #+#             */
/*   Updated: 2025/10/21 17:29:54 by tlavared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	ft_sort_small(t_stack *a)
{
	t_node	*high;

	if (a->size < 2)
		return ;
	else if (a->size < 3 && a->head->value > a->head->next->value)
		ft_sa(a);
	else if (a->size < 4)
	{
		high = ft_highnest_node(a);
		printf("highnest: %d\n", high->value);
		if (a->head->value == high->value)
			ft_rra(a);
		if (high->value > a->tail->value)
			ft_rra(a);
		if (a->head->value > a->head->next->value)
			ft_sa(a);
	}
}
