/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_align_ra.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 03:15:27 by tlavared          #+#    #+#             */
/*   Updated: 2025/10/24 04:12:06 by tlavared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static void	ft_move_ra(t_stack *stack, int count)
{
	while (count > 0)
	{
		ft_ra(stack);
		count--;
	}
}

static void	ft_move_rra(t_stack *stack, int count)
{
	while (count > 0)
	{
		ft_rra(stack);
		count--;
	}
}

void	ft_final_align(t_stack *stack)
{
	t_node	*lownest;
	int		pos_low;
	int		cost;

	lownest = ft_lownest_node(stack);
	pos_low = ft_get_pos(stack, lownest);
	if (pos_low == 0)
		return ;
	if (pos_low <= (stack->size / 2))
	{
		cost = pos_low;
		ft_move_ra(stack, cost);
	}
	else
	{
		cost = stack->size - pos_low;
		ft_move_rra(stack, cost);
	}
}
