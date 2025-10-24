/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 20:43:25 by tlavared          #+#    #+#             */
/*   Updated: 2025/10/23 19:18:46 by tlavared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/checker_bonus.h"

int	ft_is_sorted(t_stack *stack_a, t_stack *b)
{
	t_node	*current;

	if (b->head)
		return (0);
	if (!stack_a || !stack_a->head || stack_a->size <= 1)
		return (1);
	current = stack_a->head;
	while (current->next)
	{
		if (current->value > current->next->value)
			return (0);
		current = current->next;
	}
	return (1);
}
