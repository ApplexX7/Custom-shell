/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_args_helpers2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayait-el <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 18:30:50 by ayait-el          #+#    #+#             */
/*   Updated: 2024/03/27 18:31:16 by ayait-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// malloc: tmp, zeros
// create ones array from mask and set 'ones'
int	set_ones_arr(char *str, char *mask, char ***ones)
{
	char	*tmp;
	int		i;

	tmp = ft_strdup(mask);
	if (!tmp)
		return (perror("malloc"), 1);
	i = 0;
	while (tmp[i])
	{
		if (tmp[i] == '1')
			tmp[i] = str[i];
		i++;
	}
	*ones = ft_split(tmp, '0');
	free(tmp);
	if (!(*ones))
		return (perror("malloc"), 1);
	return (0);
}

// malloc: tmp, zeros
int	set_zeros_arr(char *str, char *mask, char ***zeros)
{
	char	*tmp;
	int		i;

	tmp = ft_strdup(mask);
	if (!tmp)
		return (perror("malloc"), 1);
	i = 0;
	while (tmp[i])
	{
		if (tmp[i] == '0')
			tmp[i] = str[i];
		i++;
	}
	*zeros = ft_split(tmp, '1');
	free(tmp);
	if (!(*zeros))
		return (perror("malloc"), 1);
	return (0);
}

// fills splited with the content of zeros and ones
// according to the order of appearence
int	fil_split_arr(t_list **splited, char **zeros, char **ones, char *mask)
{
	int		i;
	int		j;
	char	current;

	i = 0;
	j = 0;
	while (zeros[i] || ones[j])
	{
		current = *mask;
		if (current == '0' && new_and_add(splited, zeros[i++], '\''))
			return (1);
		else if (current == '1' && new_and_add(splited, ones[j++], 0))
			return (1);
		while (*mask == current)
			mask++;
	}
	return (0);
}

// allocs: zeros, ones
// split mask and return the splited list
t_list	*get_splited_list(char *str, char *mask)
{
	char	**zeros;
	char	**ones;
	t_list	*splited;

	if (set_zeros_arr(str, mask, &zeros))
		return (NULL);
	if (set_ones_arr(str, mask, &ones))
		return (free_2d_arr((void **)zeros), NULL);
	splited = NULL;
	if (fil_split_arr(&splited, zeros, ones, mask))
		return (ft_lstclear(&splited, &free), free_2d_arr((void **)zeros),
			free_2d_arr((void **)ones), NULL);
	(free_2d_arr((void **)zeros), free_2d_arr((void **)ones));
	return (splited);
}

// handles when and env arg expand to an empty string
int	handle_empty_string_case(char **value, t_list *node)
{
	char	*new_value;

	if (!(*value) && node->is_op == '"')
	{
		new_value = malloc(1);
		if (!new_value)
			return (perror("handle_empty_string_case"), 1);
		new_value[0] = '\0';
		*value = new_value;
	}
	return (0);
}
