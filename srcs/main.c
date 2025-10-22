/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 05:19:47 by tlavared          #+#    #+#             */
/*   Updated: 2025/10/22 05:20:19 by tlavared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

typedef struct s_cost
{
	int		cost_a;
	int		cost_b;
	int		dir_a;
	int		dir_b;
	int		total;
	t_node	*target;
}	t_cost;

typedef struct s_calc_data
{
	int	pos_a;
	int	pos_b;
	int	cost_ra;
	int	cost_rra;
	int	cost_rb;
	int	cost_rrb;
}	t_calc_data;

void	ft_equal_dir_cost(t_cost *cost)
{
	if (cost->dir_a == cost->dir_b)
	{
		if (cost->cost_a > cost->cost_b)
			cost->total = cost->cost_a;
		else
			cost->total = cost->cost_b;
	}
	else
		cost->total = cost->cost_a + cost->cost_b;
}

t_cost ft_get_plan_cost(t_node *node, int cost_a, int dir_a, int cost_b, int dir_b)
{
	t_cost	plan;
	int		total;

	plan.cost_a = cost_a;
	plan.dir_a = dir_a;
	plan.cost_b = cost_b;
	plan.dir_b = dir_b;
	plan.target = node;
	if (dir_a == dir_b)
	{
		if (cost_a > cost_b)
			total = cost_a;
		else
			total = cost_b;
	}
	else
		total = cost_a + cost_b;
	plan.total = total;
	return (plan);
}

t_cost	ft_calculate_cost(t_stack *a, t_stack *b, t_node *node)
{
	t_cost		best_cost;
	t_cost		current_cost;
	t_calc_data	data;

	best_cost = (t_cost){0, 0, 0, 0, 9999999, node};
	data.pos_a = ft_insert_pos(a, node);
	data.pos_b = ft_get_pos(b, node);
	data.cost_ra = data.pos_a;
	data.cost_rra = a->size - data.pos_a;
	data.cost_rb = data.pos_b;
	data.cost_rrb = b->size - data.pos_b;
	current_cost = ft_get_plan_cost(node, data.cost_ra, 1, data.cost_rb, 1);
	if (current_cost.total < best_cost.total)
		best_cost = current_cost;
	current_cost = ft_get_plan_cost(node, data.cost_rra, -1, data.cost_rrb, -1);
	if (current_cost.total < best_cost.total)
		best_cost = current_cost;
	current_cost = ft_get_plan_cost(node, data.cost_ra, 1, data.cost_rrb, -1);
	if (current_cost.total < best_cost.total)
		best_cost = current_cost;
	current_cost = ft_get_plan_cost(node, data.cost_rra, -1, data.cost_rb, 1);
	if (current_cost.total < best_cost.total)
		best_cost = current_cost;
	return (best_cost);
}

t_node	*ft_find_cheap_node(t_stack *a, t_stack *b)
{
	t_node	*node;
	t_cost	cost;
	t_cost	min_cost;

	if (!b->head)
		return (NULL);
	node = b->head;
	min_cost = ft_calculate_cost(a, b, node);
	while (node)
	{
		cost = ft_calculate_cost(a, b, node);
		if (cost.total < min_cost.total)
				min_cost = cost;
		node = node->next;
	}
	return (min_cost.target);
}

void	ft_execute_operations(t_stack *a, t_stack *b, t_cost cost)
{
	int	combined;

	if (cost.dir_a == cost.dir_b && cost.dir_a == 1)
	{
		if (cost.cost_a < cost.cost_b)
			combined = cost.cost_a;
		else
			combined = cost.cost_b;
		while (combined > 0)
		{
			ft_rr(a, b);
			cost.cost_a--;
			cost.cost_b--;
			combined--;
		}
	}
	else if (cost.dir_a == cost.dir_b && cost.dir_a == -1)
	{
		if (cost.cost_a < cost.cost_b)
			combined = cost.cost_a;
		else
			combined = cost.cost_b;
		while (combined > 0)
		{
			ft_rrr(a, b);
			cost.cost_a--;
			cost.cost_b--;
			combined--;
		}
	}
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
		while (cost > 0)
		{
			ft_ra(stack);
			cost--;
		}
	}
	else
	{
		cost = stack->size - pos_low;
		while (cost > 0)
		{
			ft_rra(stack);
			cost--;
		}
	}
}

void	ft_push_b_turk(t_stack *a, t_stack *b)
{
	t_node	*cheap;
	t_cost	cost;

	while (b->size > 0)
	{
		cheap = ft_find_cheap_node(a, b);
		cost = ft_calculate_cost(a, b, cheap);
		ft_execute_operations(a, b, cost);
	}
	ft_final_align(a);
}

int	main(int argc, char **argv)
{
	t_stack		*a;
	t_stack		*b;

	if (argc < 2)
		return (ft_handler_logic("Error\n"));
	a = ft_stacknew();
	b = ft_stacknew();
	if (!a || !b)
		return (1);
	if (!ft_parse(argv + 1, a))
	{
		ft_stack_free(a);
		ft_stack_free(b);
	}
	if (ft_check_repeat(a->head))
	{
		ft_stack_free(a);
		ft_stack_free(b);
		return ((ft_handler_logic("Error\n")));
	}
	ft_choose_sort(a, b);	
	ft_push_b_turk(a, b);
	//ft_print_stacks(a, b, "final");
	ft_stack_free(a);
	ft_stack_free(b);
	(void ) argc;
}
