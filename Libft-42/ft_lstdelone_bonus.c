/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 13:09:33 by mohilali          #+#    #+#             */
/*   Updated: 2023/11/06 18:47:12 by mohilali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (lst == NULL || del == NULL)
		return ;
	del((void *)(lst->content));
	free(lst);
}

/*void del(void *content) {
    if (content != NULL) {
        free(content);  
    }
}

int main() {
    t_list *node = malloc(sizeof(t_list));
    char *content = ft_strdup("Hello, World!");
    node->content = content;
    node->next = NULL;

    ft_lstdelone(node, del);
    return 0;
}*/
