/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_five.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 17:31:58 by mohilali          #+#    #+#             */
/*   Updated: 2024/03/28 17:34:55 by mohilali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_2d_arr(void **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

int	is_open_parenth(t_list *node)
{
	if (!ft_strncmp(node->content, "(", 2) && !node->is_op)
		return (1);
	else
		return (0);
}

int	is_close_parenth(t_list *node)
{
	if (!ft_strncmp(node->content, ")", 2) && !node->is_op)
		return (1);
	else
		return (0);
}

int	is_herdoc(t_list *lst)
{
	if (!ft_strncmp(lst->content, ">>", 3) || !ft_strncmp(lst->content, "<<",
			3))
		return (1);
	else
		return (0);
}

int	arr_size(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}
