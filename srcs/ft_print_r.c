/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_r.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 13:36:56 by tlavared          #+#    #+#             */
/*   Updated: 2025/10/20 13:38:04 by tlavared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	ft_rra(t_stack *a)
{
	ft_rrotate(a);
	write(1, "rra\n", 4);
}

void	ft_rrb(t_stack *b)
{
	ft_rrotate(b);
	write(1, "rrb\n", 4);
}
