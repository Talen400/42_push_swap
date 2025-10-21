/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_small.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 19:48:23 by tlavared          #+#    #+#             */
/*   Updated: 2025/10/20 22:05:39 by tlavared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

t_node	*ft_highnest_node(t_stack *stack)
{
	t_node	*node;
	t_node	*head;

	if (!stack->head)
		return (0);
	head = stack->head;
	node = head;
	while (head)
	{
		if (head && node->value < head->value)
			node = head;
		head = head->next;
	}
	return (node);
}

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
