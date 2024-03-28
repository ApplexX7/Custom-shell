/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_args_helpers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayait-el <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 18:31:41 by ayait-el          #+#    #+#             */
/*   Updated: 2024/03/28 18:03:43 by ayait-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// accept array of env args, get their value and update arr
// allocs: str
int	join_values(char **arr, char **dest)
{
	char	*tmp;
	char	*str;
	char	*value;
	int		i;

	i = 0;
	str = NULL;
	while (arr[i])
	{
		tmp = str;
		if (get_env_value(arr[i], NULL, &value))
			return (free(str), 1);
		str = ft_strjoin(str, value);
		free(value);
		free(tmp);
		if (!str && tmp)
			return (perror("join_values"), 1);
		i++;
	}
	return (*dest = str, 0);
}

// join current with before
int	join_before(t_list *before, t_list **lst, t_list *current)
{
	char	*new;

	new = ft_strjoin(before->content, current->content);
	if (!new)
		return (1);
	free(before->content);
	before->content = new;
	before->is_op = '\'';
	lst_remove_node(lst, current);
	return (0);
}

// join current with after
int	join_after(t_list *after, t_list **lst, t_list *current)
{
	char	*new;

	new = ft_strjoin(current->content, after->content);
	if (!new)
		return (1);
	free(current->content);
	current->content = new;
	current->is_op = '\'';
	lst_remove_node(lst, after);
	return (0);
}

// expand arg and split it and add to dest
int	lst_add_env_arg(char *arg, t_list **dest)
{
	char	**arr;
	t_list	*new_lst;

	if (!arg)
		return (0);
	if (arg[0])
		arr = ft_split(arg, ' ');
	else if (get_empty_str_arr(&arr))
		return (1);
	if (!arr)
		return (1);
	new_lst = convert_arr_to_list(arr);
	if (!new_lst)
		return (free_2d_arr((void **)arr), 1);
	append_list(new_lst, dest, 0);
	free(arr);
	return (0);
}

// return an empty string ft_split like array: ["", NULL]
int	get_empty_str_arr(char ***dest)
{
	char	**arr;

	arr = malloc(sizeof(char *) * 2);
	if (!arr)
		return (perror("get_empty_str_arr"), 1);
	arr[1] = NULL;
	arr[0] = malloc(1);
	if (!arr[0])
		return (perror("get_empty_str_arr"), free(arr), 1);
	return (*dest = arr, 0);
}
