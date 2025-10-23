/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_turk_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 03:14:11 by tlavared          #+#    #+#             */
/*   Updated: 2025/10/23 04:50:41 by tlavared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static void	ft_execute_rrr(t_stack *a, t_stack *b, t_cost *cost, int *combined)
{
	if (cost->cost_a < cost->cost_b)
		*combined = cost->cost_a;
	else
		*combined = cost->cost_b;
	while (*combined > 0)
	{
		ft_rrr(a, b);
		cost->cost_a--;
		cost->cost_b--;
		(*combined)--;
	}
}

static void	ft_execute_rr_rrr(t_stack *a, t_stack *b, t_cost *cost,
	int *combined)
{
	if (cost->dir_a == cost->dir_b && cost->dir_a == 1)
	{
		if (cost->cost_a < cost->cost_b)
			*combined = cost->cost_a;
		else
			*combined = cost->cost_b;
		while (*combined > 0)
		{
			ft_rr(a, b);
			cost->cost_a--;
			cost->cost_b--;
			(*combined)--;
		}
	}
	else if (cost->dir_a == cost->dir_b && cost->dir_a == -1)
	{
		ft_execute_rrr(a, b, cost, combined);
	}
}

void	ft_execute_operations(t_stack *a, t_stack *b, t_cost cost)
{
	int	combined;

	ft_execute_rr_rrr(a, b, &cost, &combined);
	while (cost.cost_b > 0)
	{
		if (cost.dir_b > 0)
			ft_rb(b);
		else
			ft_rrb(b);
		cost.cost_b--;
	}
	while (cost.cost_a > 0)
	{
		if (cost.dir_a == 1)
			ft_ra(a);
		else
			ft_rra(a);
		cost.cost_a--;
	}
	ft_pa(a, b);
}
