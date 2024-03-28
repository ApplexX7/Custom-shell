/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayait-el <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 18:13:35 by ayait-el          #+#    #+#             */
/*   Updated: 2024/03/28 18:19:17 by ayait-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

static int	is_matched_in_env(char *arg, char *env_content)
{
	if (!ft_strncmp(arg, env_content, ft_strlen(arg))
		&& (((char *)env_content)[ft_strlen(arg)] == '='
		|| ((char *)env_content)[ft_strlen(arg)] == '\0'))
		return (1);
	else
		return (0);
}

int	ft_unset(t_tree *tree, t_list **local_env)
{
	static t_list	**env = NULL;
	t_list			*tmp;
	t_list			*arg;

	if (local_env)
		env = local_env;
	else
	{
		arg = tree->node->next;
		tmp = *env;
		while (arg)
		{
			while (tmp)
			{
				if (is_matched_in_env(arg->content, tmp->content))
				{
					lst_remove_node(env, tmp);
					break ;
				}
				tmp = tmp->next;
			}
			arg = arg->next;
		}
	}
	return (0);
}
