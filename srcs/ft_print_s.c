/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_s.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 18:42:01 by tlavared          #+#    #+#             */
/*   Updated: 2025/10/20 18:45:15 by tlavared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	ft_sa(t_stack *a)
{
	ft_swap(a);
	write(1, "sa\n", 3);
}

void	ft_sb(t_stack *b)
{
	ft_swap(b);
	write(1, "sb\n", 3);
}

void	ft_ss(t_stack *a, t_stack *b)
{
	ft_swap(a);
	ft_swap(b);
	write(1, "ss\n", 3);
}
