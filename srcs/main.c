/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 05:19:47 by tlavared          #+#    #+#             */
/*   Updated: 2025/10/18 21:37:19 by tlavared         ###   ########.fr       */
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

int	main(int argc, char **argv)
{
	t_stack	*a;
	t_stack	*b;

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

	int	*values;
	values = ft_array_binary(a);
	int	i = 0;
	while (i <  a->size)
	{
		printf("%d \n", values[i]);
		i++;
	}
	int	search = 12;
	printf("Encontrado! %d\n", ft_binary_search(values, search, a->size));

	ft_push(a, b);
	ft_print_stacks(a, b, "pb");

	ft_rotate(a);
	ft_print_stacks(a, b, "ra");
	
	ft_push(a, b);
	ft_print_stacks(a, b, "pb");
	
	ft_rrotate(b);
	ft_print_stacks(a, b, "rb");

	ft_swap(a);
	ft_print_stacks(a, b, "sa");

	stack_free(a);
	stack_free(b);
	(void ) argc;
}
