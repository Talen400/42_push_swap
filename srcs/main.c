/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 05:19:47 by tlavared          #+#    #+#             */
/*   Updated: 2025/10/18 23:57:46 by tlavared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int	op_count = 0;

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
	return (data);
}

static void	ft_push_non_lis_to_b(t_stack *a, t_stack *b, t_lis_data *data)
{
	int	pushed;
	int	target_pushes;
	int	position;
	int	rotations;

	pushed = 0;
	target_pushes = data->total_size - data->lis_lenght;
	position = 0;
	rotations = 0;
	while (pushed < target_pushes && rotations < data->total_size * 2)
	{
		if (data->is_in_lis[position])
		{
			ft_rotate(a);
			ft_print_stacks(a, b, "ra");
			op_count++;
		}
		else
		{
			ft_push(a, b);
			ft_print_stacks(a, b, "pb");
			op_count++;
			pushed++;
			if (b->size > 1)
			{
				if (b->head->value < b->head->next->value)
				{
					ft_rotate(b);
					ft_print_stacks(a, b, "rb");
					op_count++;
				}
			}
		}
		position++;
		if (position >= data->total_size)
			position = 0;
		rotations++;
	}
}

int ft_find_min_value(t_stack *stack)
{
    int     min;
    t_node  *current;

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
    int     min;
    int     min_pos;
    int     pos;
    t_node  *current;

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

void	ft_push_back_sorted(t_stack *a, t_stack *b)
{
	int	target_pos;
	int	size_a;

	while  (b->head)
	{
		target_pos = ft_find_insert_position(a, b->head->value);
		size_a = a->size;
		if (target_pos <= size_a / 2)
		{
			while (target_pos > 0)
			{
				ft_rotate(a);
				ft_print_stacks(a, b, "ra");
				op_count++;
				target_pos--;
			}
		}
		else
		{
			while (target_pos < size_a)
			{
				ft_rrotate(a);
				ft_print_stacks(a, b, "rra");
				op_count++;
				target_pos++;
			}
		}
		ft_push(b, a);
		ft_print_stacks(a, b, "pa");
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
			ft_print_stacks(a, b, "ra");
			op_count++;
			min_pos--;
		}
	}
	else
	{
		while (min_pos < size)
		{
			ft_rrotate(a);
			ft_print_stacks(a, b, "rra");
			op_count++;
			min_pos++;
		}
	}
}

int	main(int argc, char **argv)
{
	t_stack		*a;
	t_stack		*b;
	int			*values;
	t_lis_data	*lis;

	if (argc < 2)
		return (ft_handler_logic("Error\n"));
	a = ft_stacknew();
	b = ft_stacknew();
	if (!a || !b)
		return (1);
	if (!ft_parse(argv + 1, a))
	{
		stack_free(a);
		stack_free(b);
	}
	if (ft_check_repeat(a->head))
	{
		stack_free(a);
		stack_free(b);
		return ((ft_handler_logic("Error\n")));
	}
	ft_print_stacks(a, b, "initial");

	values = ft_array_binary(a);

	lis = ft_find_lis(values, a->size);
	if (!lis)
		return (1);
	ft_push_non_lis_to_b(a, b, lis);
	ft_push_back_sorted(a, b);
	ft_final_rotation(a, b);
	printf("Qu operations: %d\n", op_count);
	free(lis);
	free(values);
	stack_free(a);
	stack_free(b);
	(void ) argc;
}
