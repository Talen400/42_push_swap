/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 05:19:47 by tlavared          #+#    #+#             */
/*   Updated: 2025/10/19 04:46:50 by tlavared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int	op_count = 0;

typedef struct	s_move_cost
{
	int	ra;
	int	rb;
	int	rra;
	int	rrb;
	int	total_cost;
}	t_move_cost;

int	ft_abs(int n)
{
	if (n < 0)
		n *= -1;
	return (n);
}

int	ft_max(int a, int b)
{
	if (a > b)
		return (a);
	else
		return (b);
}

int	ft_min(int a, int b)
{
	if (a < b)
		return (a);
	else
		return (b);
}

int	ft_get_node_position(t_stack *stack, int target_value)
{
	t_node	*node;
	int		pos;

	node = stack->head;
	pos = 0;
	while (node)
	{
		if (node->value == target_value)
			return (pos);
		node = node->next;
		pos++;
	}
	return (-1);
}

static int	*ft_array_binary(t_stack *list)
{
	int		i;
	t_node	*node;
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

static int	*ft_normalized(t_stack *stack)
{
	int	*values;
	int	*sorted;
	int	*normalized;
	int	i;
	int	j;

	values = ft_array_binary(stack);
	if (!values)
		return (NULL);
	sorted = malloc (sizeof(int) * stack->size);
	if (!sorted)
	{
		free(values);
		return (NULL);
	}
	i = 0;
	while (i < stack->size)
	{
		sorted[i] = values[i];
		i++;
	}
	i = 0;
	while (i < stack->size - 1)
	{
		j = 0;
		while (j < stack->size - i - 1)
		{
			if (sorted[j] > sorted[j + 1])
			{
				int	temp = sorted[j];
				sorted[j] = sorted[j + 1];
				sorted[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
	normalized = malloc(sizeof(int) * stack->size);
	if (!normalized)
	{
		free(values);
		free(sorted);
		return (NULL);
	}
	i = 0;
	while (i < stack->size)
	{
		j = 0;
		while (j < stack->size)
		{
			if (values[i] == sorted[j])
			{
				normalized[i] = j;
				break ;
			}
			j++;
		}
		i++;
	}
	free(values);
	free(sorted);
	return (normalized);
}

static int	ft_binary_search(int *arr, int search, int len)
{
	int	mid;
	int	left;
	int	right;

	left = 0;
	right = len;
	while (left < right)
	{
		mid = left + (right - left) / 2;
		if (arr[mid] < search)
			left = mid + 1;
		else
			right = mid;
	}
	return (left);
}

t_lis_data	*ft_find_lis(int *values, int size)
{
	int	*tails;
	int	*tails_inc;
	int *prev;
	int	*flags;
	int	lis_len;
	t_lis_data	*data;
	int	i;
	int	pos;
	int	k;

	tails = malloc(sizeof(int ) * size);
	prev = malloc(sizeof(int ) * size);
	flags = calloc(size, sizeof(int ));
	tails_inc = malloc(sizeof(int ) * size);
	lis_len = 0;
	if (!tails || !prev || !flags || !tails_inc)
	{
		free(tails);
		free(prev);
		free(flags);
		return (NULL);
	}
	i = 0;
	while (i < size)
	{
		pos = ft_binary_search(tails, values[i], lis_len);
		tails[pos] = values[i];
		tails_inc[pos] = i;
		if (pos > 0)
			prev[i] = tails_inc[pos - 1];
		else
			prev[i] = -1;
		if (pos == lis_len)
			lis_len++;
		i++;
	}
	k = tails_inc[lis_len - 1];
	while (k != -1)
	{
		flags[k] = 1;
		k = prev[k];
	}
	data = malloc(sizeof(t_lis_data ));
	data->is_in_lis = flags;
	data->lis_lenght = lis_len;
	data->total_size = size;
	free(tails);
	free(prev);
	free(tails_inc);
	return (data);
}

static int	ft_get_best_lis_rotation(int *values, int size)
{
	int	max_lis_len = 0;
	int	best_rotation_count = 0;
	int	i = 0;
	int	j;
	int	temp;
	t_lis_data	*lis_data;

	while (i < size)
	{
		lis_data = ft_find_lis(values, size);
		if (!lis_data)
			return (-1);
		if (lis_data->lis_lenght > max_lis_len)
		{
			max_lis_len = lis_data->lis_lenght;
			best_rotation_count = i;
		}
		free(lis_data->is_in_lis);
		free(lis_data);
		if (i < size - 1)
		{
			temp = values[0];
			j = 0;
			while (j < size - 1)
			{
				values[j] = values[j + 1];;
				j++;
			}
			values[size - 1] = temp;
		}
		i++;
	}
	return (best_rotation_count);
}

static void	ft_align_best_lis(t_stack *a, t_stack *b, int rotations_needed)
{
	int	size;
	int	rra_count;

	size = a->size;
	if (rotations_needed <= size / 2)
	{
		while (rotations_needed-- > 0)
		{
			ft_rotate(a);
			// ft_print_stacks(a, b, ra");
			op_count++;
		}
	}
	else
	{
		rra_count = size - rotations_needed;
		while (rra_count-- > 0)
		{
			ft_rrotate(a);
			// ft_print_stacks(a, b, "rra");
			op_count++;
		}
	}
	(void) b;
}

static void	ft_push_non_lis_to_b(t_stack *a, t_stack *b, t_lis_data *data)
{
	int	pushed;
	int	target_pushes;
	int	position;
	int	rotations_done;

	pushed = 0;
	target_pushes = data->total_size - data->lis_lenght;
	position = 0;
	rotations_done = 0;
	while (pushed < target_pushes && rotations_done < data->total_size * 2)
	{
		if (data->is_in_lis[position % data->total_size])
		{
			ft_rotate(a);
			//ft_print_stacks(a, b, "ra");
			op_count++;
			position++;
		}
		else
		{
			ft_push(a, b);
			//ft_print_stacks(a, b, "pb");
			op_count++;
			pushed++;
		}
		rotations_done++;
	}
}

int ft_find_min_value(t_stack *stack)
{
	int		min;
	t_node	*current;

	if (!stack->head)
		return (2147483647);

	min = stack->head->value;
	current = stack->head->next;
	while (current)
	{
		if (current->value < min)
			min = current->value;
		current = current->next;
	}
	return (min);
}

int ft_find_min_position(t_stack *stack)
{
	int		min;
	int		min_pos;
	int		pos;
	t_node	*current;

	if (!stack->head)
		return (0);
	min = stack->head->value;
	min_pos = 0;
	pos = 0;
	current = stack->head;
	while (current)
	{
		if (current->value < min)
		{
			min = current->value;
			min_pos = pos;
		}
		pos++;
		current = current->next;
	}
	return (min_pos);
}

int	ft_find_insert_position(t_stack *stack, int value)
{
	int		pos;
	int		min;
	int		max;
	t_node	*node;

	if (!stack->head)
		return (0);
	pos = 0;
	min = ft_find_min_value(stack);
	max = stack->head->value;
	node = stack->head;
	while (node)
	{
		if (node->value > max)
			max = node->value;
		node = node->next;
	}
	if (value < min || value > max)
		return (ft_find_min_position(stack));
	node = stack->head;
	pos = 0;
	while (node && node->next)
	{
		if (node->value < value && value < node->next->value)
			return (pos + 1);
		pos++;
		node = node->next;
	}
	return (0);
}

static int	ft_find_target_pos_in_a(t_stack *a, int value_b)
{
	t_node	*node;
	int		target_val;
	int		min_greater;

	node = a->head;
	min_greater = MAX_INT;
	while (node)
	{
		if (node->value > value_b && node->value < min_greater)
			min_greater = node->value;
		node = node->next;
	}
	if (min_greater == MAX_INT)
		target_val = ft_find_min_value(a);
	else
		target_val = min_greater;
	return (ft_get_node_position(a, target_val));
}

static void	ft_calculate_move_cost(t_stack *a, t_stack *b, t_move_cost *costs,
		int pos_a, int pos_b)
{
	int size_a;
	int size_b;
	int local_ra;
	int local_rra;
	int local_rb;
	int local_rrb;
	int cost_rr;
	int cost_rrr;
	int cost_mix1;
	int cost_mix2;

	size_a = a->size;
	size_b = b->size;
	local_ra = pos_a;
	local_rra = 0;
	if (pos_a > 0)
		local_rra = size_a - pos_a;
	local_rb = pos_b;
	local_rrb = 0;
	if (pos_b > 0)
		local_rrb = size_b - pos_b;
	cost_rr = ft_max(local_ra, local_rb);
	cost_rrr = ft_max(local_rra, local_rrb);
	cost_mix1 = local_ra + local_rrb;
	cost_mix2 = local_rra + local_rb;
	costs->total_cost = cost_rr;
	costs->ra = local_ra; 
	costs->rb = local_rb; 
	costs->rra = 0; 
	costs->rrb = 0;
	if (cost_rrr < costs->total_cost)
	{
		costs->total_cost = cost_rrr;
		costs->ra = 0; 
		costs->rb = 0; 
		costs->rra = local_rra; 
		costs->rrb = local_rrb;
	}
	if (cost_mix1 < costs->total_cost)
	{
		costs->total_cost = cost_mix1;
		costs->ra = local_ra; 
		costs->rb = 0; 
		costs->rra = 0; 
		costs->rrb = local_rrb;
	}
	if (cost_mix2 < costs->total_cost)
	{
		costs->total_cost = cost_mix2;
		costs->ra = 0; 
		costs->rb = local_rb; 
		costs->rra = local_rra; 
		costs->rrb = 0;
	}
}

static void	ft_rr(t_stack *a, t_stack *b)
{
	ft_rotate(a);
	ft_rotate(b);
	op_count++;
}

static void	ft_rrr(t_stack *a, t_stack *b)
{
	ft_rrotate(a);
	ft_rrotate(b);
	op_count++;
}

static void	ft_execute_move(t_stack *a, t_stack *b, t_move_cost *costs)
{
	int	cost_rr = ft_max(costs->ra, costs->rb);
	int cost_rrr = ft_max(costs->rra, costs->rrb);

	if (costs->total_cost == cost_rr)
	{
		while (costs->ra > 0 && costs->rb > 0)
		{
			ft_rr(a, b);
			costs->ra--;
			costs->rb--;
		}
	}
	else if (costs->total_cost == cost_rrr)
	{
		while (costs->rra > 0 && costs->rrb > 0)
		{
			ft_rrr(a, b);
			costs->rra--;
			costs->rrb--;
		}
	}
	while (costs->ra-- > 0)
	{
		ft_rotate(a);
		op_count++;
	}
	while (costs->rra-- > 0)
	{
		ft_rrotate(a);
		op_count++;
	}
	while (costs->rb-- > 0)
	{
		ft_rotate(b);
		op_count++;
	}
	while (costs->rrb-- > 0)
	{
		ft_rrotate(b);
		op_count++;
	}
}

void	ft_push_back_sorted(t_stack *a, t_stack *b)
{
	t_move_cost	cheapest_cost;
	t_node		*b_node;
	int			pos_b;
	int			pos_a;

	while (b->size > 0)
	{
		b_node = b->head;
		pos_b = 0;
		cheapest_cost.total_cost = MAX_INT;
		while (b_node)
		{
			t_move_cost	curr_cost;
			
			pos_a = ft_find_target_pos_in_a(a, b_node->value);
			ft_calculate_move_cost(a, b, &curr_cost, pos_a, pos_b);
			if (curr_cost.total_cost < cheapest_cost.total_cost)
				cheapest_cost = curr_cost;
			b_node = b_node->next;
			pos_b++;
		}
		ft_execute_move(a, b, &cheapest_cost);
		ft_push(b, a);
		op_count++;
	}
}

void	ft_final_rotation(t_stack *a, t_stack *b)
{
	int	min_pos;
	int	size;

	min_pos = ft_find_min_position(a);
	size = a->size;
	if (min_pos <= size / 2)
	{
		while (min_pos > 0)
		{
			ft_rotate(a);
			//ft_print_stacks(a, b, "ra");
			op_count++;
			min_pos--;
		}
	}
	else
	{
		while (min_pos < size)
		{
			ft_rrotate(a);
			//ft_print_stacks(a, b, "rra");
			op_count++;
			min_pos++;
		}
	}
	(void ) b;
}

static void	ft_sort_big(t_stack *a, t_stack *b)
{
	int	*values;
	t_lis_data	*lis;
	int	rotations_to_best_lis;
	int	ops_before;

	//---
	printf("\n=== VALUES ===\n");
	t_node *temp = a->head;
	int count = 0;
	while (temp && count < 10)
	{
		printf("%d ", temp->value);
		temp = temp->next;
		count++;
	}
	printf("...\n");
	//---
	values = ft_normalized(a);
	if (!values)
		return ;
	//---
	printf("\n=== NORMALIZED VALUES ===\n");
	for (int i = 0; i < (a->size < 10 ? a->size : 10); i++)
		printf("%d ", values[i]);
	printf("...\n");
	//---
	rotations_to_best_lis = ft_get_best_lis_rotation(values, a->size);
	free(values);
	ops_before = op_count;
	ft_align_best_lis(a, b, rotations_to_best_lis);
	values = ft_normalized(a);
	if (!values)
		return ;
	lis = ft_find_lis(values, a->size);
	if (!lis)
	{
		free(values);
		return ;
	}
	printf("\n=== LIS INFO ===\n");
	printf("LIS length: %d / %d (%.1f%%)\n",
			lis->lis_lenght, lis->total_size,
			(float)lis->lis_lenght / lis->total_size * 100);
	printf("Non-LIS elements: %d\n", lis->total_size - lis->lis_lenght);
	printf("LIS indices: ");
	for (int i = 0; i < lis->total_size && i < 20; i++)
	{
		if (lis->is_in_lis[i])
			printf("%d ", i);
	}
	printf("...\n");
	printf("LIS values: ");
	for (int i = 0; i < lis->total_size && i < 20; i++)
	{
		if (lis->is_in_lis[i])
			printf("%d ", values[i]);
	}
	printf("...\n\n");
	printf("=== PHASE 1: PUSH NON-LIS TO B ===\n");
	ops_before = op_count;
	ft_push_non_lis_to_b(a, b, lis);
	printf("Operations in phase 1: %d\n", op_count - ops_before);
	printf("Elements in A: %d, in B: %d\n\n", a->size, b->size);
	printf("=== PHASE 2: PUSH BACK SORTED ===\n");
	ops_before = op_count;
	ft_push_back_sorted(a, b);
	printf("Operations in phase 2: %d\n", op_count - ops_before);
	printf("Elements in A: %d, in B: %d\n\n", a->size, b->size);
	printf("=== PHASE 3: FINAL ROTATION ===\n");
	ops_before = op_count;
	ft_final_rotation(a, b);
	printf("Operations in phase 3: %d\n\n", op_count - ops_before);
	printf("=== TOTAL ===\n");
	printf("Total operations: %d\n", op_count);
	free(lis->is_in_lis);
	free(lis);
	free(values);
}

static void	ft_choose_sort(t_stack *a, t_stack *b)
{
	if (a->size <= 5)
		ft_sort_big(a, b); //ft_sort_small(a, b);
	else
		ft_sort_big(a, b);
}

int ft_is_sorted(t_stack *stack_a)
{
    t_node  *current;

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
	/**
	ft_print_stacks(a, b, "initial");

	values = ft_normalized(a);

	lis = ft_find_lis(values, a->size);
	if (!lis)
		return (1);
	ft_push_non_lis_to_b(a, b, lis);
	ft_push_back_sorted(a, b);
	ft_final_rotation(a, b);
	printf("Qu operations: %d\n", op_count);
	**/

	//ft_print_stacks(a, b, "initial");
	ft_choose_sort(a, b);
	if (ft_is_sorted(a))
	{
		printf("not sorted :<");
	}
	else
	{
		printf("sorted :>");
	}
	ft_stack_free(a);
	ft_stack_free(b);
	(void ) argc;
}
