/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_nodes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 17:29:24 by tlavared          #+#    #+#             */
/*   Updated: 2025/10/21 20:25:30 by tlavared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

t_node	*ft_lownest_node(t_stack *stack)
{
	t_node	*node;
	t_node	*head;

	if (!stack->head)
		return (0);
	head = stack->head;
	node = head;
	while (head)
	{
		if (head && node->value > head->value)
			node = head;
		head = head->next;
	}
	return (node);
}

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

t_node	*ft_find_pivot(t_stack *stack)
{
	t_node	*median;
	int		i;

	median = stack->head;
	i = -1;
	while (median && ++i < (stack->size / 2))
		median = median->next;
	return (median);
}

int	ft_get_pos(t_stack *stack, t_node *search)
{
	t_node	*node;
	int		pos;

	node = stack->head;
	pos = 0;
	while (node)
	{
		if (node == search)
			return (pos);
		node = node->next;
		pos++;
	}
	return (-1);
}
