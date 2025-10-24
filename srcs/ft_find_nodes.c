/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_nodes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 17:29:24 by tlavared          #+#    #+#             */
/*   Updated: 2025/10/24 03:52:00 by tlavared         ###   ########.fr       */
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

int	ft_insert_pos(t_stack *stack, t_node *insert)
{
	t_node	*node;
	int		pos;

	if (!stack->head | !insert)
		return (-1);
	node = stack->head;
	pos = 0;
	while (pos < stack->size)
	{
		if (node->next && node->value < insert->value
			&& insert->value < node->next->value)
			return (pos + 1);
		if (node->next && node->value > node->next->value)
		{
			if (insert->value > node->value
				|| insert->value < node->next->value)
				return (pos + 1);
		}
		node = node->next;
		pos++;
	}
	return (0);
}
