/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 05:19:47 by tlavared          #+#    #+#             */
/*   Updated: 2025/10/18 23:12:41 by tlavared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

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

static void	ft_move_lis_to_b(t_stack *a, t_stack *b, t_lis_data *lis)
{
	int	top_value;
	int	pushed;

	pushed = 0;
	top_value = 0;
	while (pushed < lis->total_size - lis->lis_lenght && a->head)
	{
		if (lis->is_in_lis[top_value])
		{
			ft_rotate(a);
			ft_print_stacks(a, b, "ra");
		}
		else
		{
			ft_push(a, b);
			ft_print_stacks(a, b, "pb");
			pushed++;
		}
		top_value = (top_value + 1) % lis->total_size;
	}
}

int	main(int argc, char **argv)
{
	t_stack		*a;
	t_stack		*b;
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

	stack_free(a);
	stack_free(b);
	(void ) argc;
}
