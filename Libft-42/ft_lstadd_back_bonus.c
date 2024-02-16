/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 11:03:27 by mohilali          #+#    #+#             */
/*   Updated: 2023/11/06 12:45:19 by mohilali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*current;

	if (!lst || ! new)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
	{
		current = *lst;
		while (current->next != NULL)
		{
			current = current->next;
		}
		current->next = new;
	}
}

/*
void    ft_lstadd_back(t_list **lst, t_list *new)
{
        t_list  *last;

        if (lst == NULL || new == NULL)
                return ;
        if (*lst == NULL)
                *lst = new;
        else
        {
                last = ft_lstlast(*lst);
                last->next = new;
        }
}
*/
