/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_operations.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 21:07:37 by tlavared          #+#    #+#             */
/*   Updated: 2025/10/18 21:41:32 by tlavared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	ft_push(t_stack *from, t_stack *dest)
{
	t_node	*node;
	
	if (!from->head)
		return ;
	node = from->head;
	from->head = node->next;
	if (from->head)
		from->head->prev = NULL;
	else
		from->tail = NULL;
	from->size--;
	node->next = dest->head;
	node->prev = NULL;
	if (dest->head)
		dest->head->prev = node;
	else
		dest->tail = node;
	dest->head = node;
	dest->size++;
}

void	ft_rotate(t_stack *stack)
{
	t_node	*first;

	if (!stack->head || stack->size < 2)
		return ;
	first = stack->head;
	stack->head = first->next;
	stack->head->prev = NULL;
	first->next = NULL;
	first->prev = stack->tail;
	stack->tail->next = first;
	stack->tail = first;
}

void	ft_rrotate(t_stack *stack)
{
	t_node	*last;

	if (!stack->head || stack->size < 2)
		return ;
	last = stack->tail;
	stack->tail = last->prev;
	stack->tail->next = NULL;
	last->prev = NULL;
	last->next = stack->head;
	stack->head->prev = last;
	stack->head = last;
}

void	ft_swap(t_stack *stack)
{
	t_node	*first;
	t_node	*second;
	t_node	*tmp;

	if (!stack->head || !stack->head->next)
		return ;
	first = stack->head;
	second = first->next;
	tmp = second->next;
	second->next = first;
	second->prev = NULL;
	first->next = tmp;
	first->prev = second;
	if (tmp)
		tmp->prev = first;
	else
		stack->tail = first;
	stack->head = second;
}
