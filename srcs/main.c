/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 05:19:47 by tlavared          #+#    #+#             */
/*   Updated: 2025/10/15 15:29:40 by tlavared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static int	ft_handler_logic(char *str)
{
	ft_putstr_fd(str, 2);
	return (1);
}

static int	ft_isnum(char	*str)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (1);
		str++;
	}
	return (0);
}


static t_list	*ft_parse(char **argv)
{
	t_list	*a;
	t_list	*node;
	int		*ptr;
	int		i;

	i = 1;
	a = NULL;
	while (argv[i])
	{
		if (ft_isnum(argv[i]) == 0)
		{
			ptr = (int *) malloc (sizeof(int ));
			if (!ptr)
				return (NULL);
			*ptr = ft_atoi(argv[i]);
			node = ft_lstnew(ptr);
			ft_lstadd_back(&a, node);
		}
		else
			break ;
		i++;
	}
	return (a);
}

static int	ft_check_repeats(t_list *list)
{
	t_list	*i;
	t_list	*j;

	i = list;
	while (i)
	{
		j = i->next;
		while (j)
		{
			if (*(int *) i->content == *(int *) j->content)
				return (1);
			j = j->next;
		}
		i = i->next;
	}
	return (0);
}

static void	ft_del(void	*ptr)
{
	free(ptr);
}

static void	ft_swap(t_list **head)
{
	t_list	*first;
	t_list	*second;

	if (!head || !*head || !(*head)->next)
		return ;
	first = *head;
	second = first->next;
	first->next = second->next;
	second->next = first;
	*head = second;
}

static void	ft_push(t_list **src, t_list **dest)
{
	t_list	*tmp;

	if (!src || !*src)
		return ;
	tmp = *src;
	*src = (*src)->next;
	tmp->next = *dest;
	*dest = tmp;
}

static void	ft_rotate(t_list **head)
{
	t_list	*first;
	t_list	*last;

	if (!head || !*head || !(*head)->next)
		return ;
	first = *head;
	last = *head;
	while (last->next)
		last = last->next;
	*head = first->next;
	first->next = NULL;
	last->next = first;
}

static void	ft_rrotate(t_list **head)
{
	t_list	*prev;
	t_list	*last;

	if (!head || !*head || !(*head)->next)
		return ;
	prev = NULL;
	last = *head;
	while (last->next)
	{
		prev = last;
		last = last->next;
	}
	prev->next = NULL;
	last->next = *head;
	*head = last;
}

static void	ft_print_stacks(t_list *a, t_list *b, const char *op)
{
	int	i;

	i = 0;
	printf("%-10s%-10s%-10s (%s)\n", "index", "a", "b", op);
	while (a || b)
	{
		printf("node[%-2d]: ", i);
		if (a)
		{
			printf("%-10d", *(int *)(a->content));
			a = a->next;
		}
		else
			printf("%-10s", "");
		if (b)
		{
			printf("%-10d", *(int *)(b->content));
			b = b->next;
		}
		else
			printf("%-10s", "");
		printf("\n");
		i++;
	}
	printf("-------------------------------\n");
}

int	main(int argc, char **argv)
{
	t_list	*a;
	t_list	*b;

	if (argc <= 1)
		return (ft_handler_logic("Error\n"));
	a = ft_parse(argv);
	if (!a)
		return (ft_handler_logic("Error\n"));
	if (ft_check_repeats(a))
	{
		ft_lstclear(&a, ft_del);
		return (ft_handler_logic("Error\n"));
	}
	b = NULL;
	ft_print_stacks(a, b, "initial");

	ft_rotate(&a);
	ft_print_stacks(a, b, "ra");

	ft_swap(&a);
	ft_print_stacks(a, b, "sa");

	ft_push(&a, &b);
	ft_print_stacks(a, b, "pb");

	ft_rrotate(&a);
	ft_print_stacks(a, b, "rra");

	ft_push(&a, &b);
	ft_print_stacks(a, b, "pb");

	ft_push(&b, &a);
	ft_print_stacks(a, b, "pa");
	
	ft_push(&a, &b);
	ft_print_stacks(a, b, "pb");

	ft_swap(&b);
	ft_print_stacks(a, b, "sb");

	ft_push(&b, &a);
	ft_print_stacks(a, b, "pa");

	ft_lstclear(&a, ft_del);
	(void ) argc;
}
