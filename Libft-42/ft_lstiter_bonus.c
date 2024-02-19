/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 18:01:33 by mohilali          #+#    #+#             */
/*   Updated: 2023/11/06 18:37:03 by mohilali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*ptr;

	if (lst == NULL || f == NULL)
		return ;
	ptr = lst;
	while (ptr != NULL)
	{
		f(ptr->content);
		ptr = ptr->next;
	}
}

/*void print_my(void *lst)
{
    printf("%"s, (char *)lst);
}

int main()
{
    t_list *lst = malloc(sizeof(t_list));

    lst->content = "hello word";
    lst->next = NULL;
    lst->next->content = "go home";
    lst->next->next = NULL;

    ft_lstiter(lst, print_my);
}*/
