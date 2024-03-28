/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 17:22:09 by mohilali          #+#    #+#             */
/*   Updated: 2024/03/28 18:00:26 by mohilali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*copy_lst(t_list *lst)
{
	char	*content;
	t_list	*new;
	t_list	*node;

	new = NULL;
	while (lst)
	{
		content = ft_strdup(lst->content);
		if (!content)
			return (ft_lstclear(&new, &free), NULL);
		node = ft_lstnew(content);
		if (!node)
			return (ft_lstclear(&new, &free), free(content), NULL);
		node->is_op = lst->is_op;
		node->mask = ft_strdup(lst->mask);
		if (!node->mask && lst->mask)
			return (ft_lstclear(&new, &free), NULL);
		ft_lstadd_back(&new, node);
		lst = lst->next;
	}
	return (new);
}

char	*join_list(t_list *lst)
{
	char	*new;
	char	*tmp;

	new = malloc(1);
	if (!new)
		return (NULL);
	new[0] = '\0';
	while (lst)
	{
		tmp = new;
		new = ft_strjoin(new, lst->content);
		free(tmp);
		if (!new)
			return (NULL);
		lst = lst->next;
	}
	return (new);
}

int	handle_ambiguous_redirection(t_list *file)
{
	t_list	*tmp;
	t_list	*new;

	tmp = file->next;
	file->next = NULL;
	new = copy_lst(file);
	file->next = tmp;
	if (!new)
		return (perror("malloc"), 1);
	if (expand_args(&new))
		return (1);
	if (ft_lstsize(new) != 1)
		return (ft_lstclear(&new, &free),
			ft_putstr_fd("ambiguous redirection\n", 2), 1);
	free(file->content);
	file->content = new->content;
	free(new->mask);
	free(new);
	return (0);
}

char	*get_env_value(char *arg, int *status)
{
	char		*value;
	static int	*status_exit;

	if (status)
	{
		status_exit = status;
		return (NULL);
	}
	if (!ft_strncmp(arg, "?", 2))
		return (ft_itoa((*status_exit) >> 8));
	value = get_exported_arg_value(arg, NULL, 0);
	if (value)
		return (ft_strdup(value));
	else
		return (NULL);
}

int	new_and_add(t_list **head, void *content, char is_op)
{
	char	*duped_content;
	t_list	*new;

	duped_content = ft_strdup(content);
	if (!duped_content)
		return (1);
	new = ft_lstnew(duped_content);
	if (!new)
		return (free(duped_content), 1);
	new->is_op = is_op;
	ft_lstadd_back(head, new);
	return (0);
}
