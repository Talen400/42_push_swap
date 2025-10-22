/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 05:19:47 by tlavared          #+#    #+#             */
/*   Updated: 2025/10/21 22:28:46 by tlavared         ###   ########.fr       */
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
	ft_print_stacks(a, b, "final");
	printf("insertion pos: %d\n" , ft_insert_pos(a, b->head));
	ft_stack_free(a);
	ft_stack_free(b);
	(void ) argc;
}
