/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 05:19:47 by tlavared          #+#    #+#             */
/*   Updated: 2025/10/23 19:20:57 by tlavared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int	main(int argc, char **argv)
{
	t_stack		*a;
	t_stack		*b;

	if (argc < 2)
		return (1);
	a = ft_stacknew();
	b = ft_stacknew();
	if (!a || !b)
		return (1);
	if (ft_parse(argc, argv + 1, a))
	{
		ft_free_stacks(a, b);
		return ((ft_handler_logic("Error\n")));
	}
	if (ft_is_sorted(a, b))
	{
		ft_free_stacks(a, b);
		return (1);
	}
	ft_choose_sort(a, b);
	ft_stack_free(a);
	ft_stack_free(b);
}
