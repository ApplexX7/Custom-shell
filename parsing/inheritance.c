/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inheritance.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:34:19 by mohilali          #+#    #+#             */
/*   Updated: 2024/03/18 15:58:50 by mohilali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	inheritance_builting(t_tree *root, int fbuiltins)
{
	if (!root)
		return ;
	else if (is_pipe(root->node) && root->fbuiltins == 1)
	{
		inheritance_builting(root->left, 1);
		inheritance_builting(root->right, 1);
	}
	else
	{
		root->fbuiltins = fbuiltins;
		inheritance_builting(root->left, fbuiltins);
		inheritance_builting(root->right, fbuiltins);
	}
}
