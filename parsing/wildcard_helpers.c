/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayait-el <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 23:11:15 by ayait-el          #+#    #+#             */
/*   Updated: 2024/03/27 23:11:18 by ayait-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// allocs: cwd, current_dir, lst
t_list	*get_current_files(void)
{
	char			*cwd;
	DIR				*current_dir;
	struct dirent	*content;
	t_list			*lst;

	lst = NULL;
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (NULL);
	current_dir = opendir(cwd);
	if (!current_dir)
		return (free(cwd), NULL);
	content = readdir(current_dir);
	while (content)
	{
		if (new_and_add(&lst, (void *)content->d_name, '\''))
			return (free(cwd), closedir(current_dir), ft_lstclear(&lst, &free),
				NULL);
		content = readdir(current_dir);
	}
	closedir(current_dir);
	return (free(cwd), lst);
}

// allocs: new
// return a new list start with 'start' and end with 'end'
t_list	*lst_copy_portion(t_list *start, t_list *end)
{
	t_list	*tmp;
	t_list	*new;

	tmp = end->next;
	end->next = NULL;
	new = copy_lst(start);
	end->next = tmp;
	if (!new)
		return (NULL);
	return (new);
}

int	is_matched(char *str, t_list *wildcard, int open_end, int open_start)
{
	t_list	*tmp;

	tmp = wildcard;
	if (!tmp)
		return (1);
	while (tmp)
	{
		if (ft_strlen(str) < ft_strlen(tmp->content))
			return (0);
		if (tmp == wildcard && !open_start)
			str = ft_strnstr(str, tmp->content, ft_strlen(tmp->content));
		else if (tmp->next || open_end)
			str = ft_strnstr(str, tmp->content, ft_strlen(str));
		else
			str = ft_strnstr(&str[ft_strlen(str) - ft_strlen(tmp->content)],
					tmp->content, ft_strlen(str));
		if (!str)
			return (0);
		str += ft_strlen(tmp->content);
		tmp = tmp->next;
	}
	return (1);
}

// remove .. and . from the matched list if 'matched'
void	remove_points_dir(t_list *start, t_list **lst, int *matched)
{
	t_list	*tmp;
	t_list	*tmp2;

	tmp = *lst;
	if (start && ((char *)start->content)[0] != '.')
	{
		while (tmp)
		{
			tmp2 = tmp->next;
			if (!ft_strncmp(tmp->content, ".", 1))
				lst_remove_node(lst, tmp);
			tmp = tmp2;
		}
		if (ft_lstsize(*lst) == 0)
			*matched = 0;
	}
}

// allocs: portion
int	get_matched_list(t_list *start, t_list *end, t_list **dest)
{
	int		open_end;
	int		open_start;
	t_list	*portion;
	int		matched;

	matched = 0;
	if (start && end)
	{
		portion = lst_copy_portion(start, end);
		if (!portion)
			return (1);
		set_ends(&open_end, &open_start, portion);
		if (split_by_star(&portion))
			return (ft_lstclear(&portion, &free), 1);
		if (add_if_matched(dest, portion,
				(int [2]){open_end, open_start}, &matched))
			return (ft_lstclear(&portion, &free), 1);
		remove_points_dir(start, dest, &matched);
		if (add_if_nomatch(dest, start, end, matched))
			return (ft_lstclear(&portion, &free), 1);
	}
	ft_lstclear(&portion, &free);
	return (0);
}
