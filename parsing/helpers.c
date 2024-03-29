/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 18:11:48 by mohilali          #+#    #+#             */
/*   Updated: 2024/03/28 18:28:42 by mohilali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_wildcard(t_list *node)
{
<<<<<<< HEAD
	if (ft_strchr(node->content, '*') && !node->is_op)
=======
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

// arr should be null terminated
int	arr_size(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

int get_env_value(char *arg, int *status, char **dest)
{
	char		*value;
	static int	*status_exit;

	if (status)
	{
		status_exit = status;
		return (0);
	}
	if (!ft_strncmp(arg, "?", 2))
  {
    value = ft_itoa((*status_exit) >> 8);
    if (!value)
      return (perror("get_env_value"), 1);
		return (*dest = value, 0);
  }
  else
  {
    value = get_exported_arg_value(arg, NULL, 0);
    *dest = ft_strdup(value);
    if (!(*dest) && value)
      return (1);
    else
      return (0);
  }
}

// allocs: content, mask, new_node
int	add_node(t_list **dest, t_list *node)
{
	char	*content;
	t_list	*new_node;
	char	*mask;

	content = ft_strdup(node->content);
	if (!content)
>>>>>>> e9c36e0508e6eb612d8e8c07d9bc72bff1ba4c24
		return (1);
	else
		return (0);
}

int	should_join_mask(t_list *start, t_list *end)
{
	int	join;

	join = 0;
	while (start != end)
	{
		if (start->mask)
			join = 1;
		start = start->next;
	}
	return (join);
}

// allocs: tmp, tmp3
int	join_mask(t_list *start, t_list *end, t_list *dest)
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	tmp = NULL;
	if (should_join_mask(start, end))
	{
		while (start != end)
		{
			if (!start->mask)
			{
				tmp2 = ft_strdup(start->content);
				full_withzero(&tmp2);
			}
			else
			{
				tmp2 = start->mask;
				start->mask = NULL;
			}
			if (!tmp2)
				return (free(tmp), perror("join_mask"), 1);
			tmp3 = tmp;
			tmp = ft_strjoin(tmp, tmp2);
			free(tmp2);
			free(tmp3);
			if (!tmp)
				return (perror("join_mask"), 1);
			start = start->next;
		}
	}
	return (dest->mask = tmp, 0);
}

void	do_nothing(void *arg)
{
	(void)arg;
}
