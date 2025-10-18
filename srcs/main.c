/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 05:19:47 by tlavared          #+#    #+#             */
/*   Updated: 2025/10/18 03:49:14 by tlavared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static int	ft_parse(char **argv, t_stack *list)
{
	int	value;

	while (*argv)
	{
		value = ft_atoi(*argv);
		stack_push_back(list, value);
		argv++;
	}
	return (1);
}

static int	ft_check_repeat(t_node *head)
{
	t_node	*node;

	while (head)
	{
		node = head->next;
		while (node)
		{
			if (head->value == node->value)
				return (1);
			node = node->next;
		}
		head = head->next;
	}
	return (0);
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
	stack_free(a);
	stack_free(b);
	(void ) argc;
}
