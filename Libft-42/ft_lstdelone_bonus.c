/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 13:09:33 by mohilali          #+#    #+#             */
/*   Updated: 2024/03/23 17:52:02 by mohilali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (lst == NULL || del == NULL)
		return ;
	del((void *)(lst->content));
	del((void *)(lst->mask));
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
