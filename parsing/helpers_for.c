/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_for.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 17:23:47 by mohilali          #+#    #+#             */
/*   Updated: 2024/03/29 15:11:24 by ayait-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_local_env_representation(t_list **local_env, char ***dest)
{
	static t_list	**env = NULL;
	char			**result;

	if (local_env)
		env = local_env;
	else
	{
		result = convert_list_to_arr(*env);
		if (!result)
			return (1);
		*dest = result;
	}
	return (0);
}

char	**convert_list_to_arr(t_list *lst)
{
	int		len;
	char	**arr;
	int		i;

	len = ft_lstsize(lst);
	arr = (char **)malloc(sizeof(char *) * (len + 1));
	if (!arr)
		return (NULL);
	i = 0;
	while (i < len)
	{
		arr[i] = (char *)lst->content;
		lst = lst->next;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

void	append_list(t_list *source, t_list **dest, char op)
{
	t_list	*tmp;

	while (source)
	{
		tmp = source;
		source = source->next;
		tmp->next = NULL;
		tmp->is_op = op;
		ft_lstadd_back(dest, tmp);
	}
}

int	is_space(t_list *node)
{
	if (node && !strncmp(node->content, " ", 2) && !node->is_op)
		return (1);
	else
		return (0);
}

void	del_spaces(t_list **lst)
{
	t_list	*tmp;
	t_list	*tmp2;

	tmp = *lst;
	while (tmp)
	{
		tmp2 = tmp->next;
		if (is_space(tmp))
			lst_remove_node(lst, tmp);
		tmp = tmp2;
	}
}
