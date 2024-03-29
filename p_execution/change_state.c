/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_state.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 10:28:03 by mohilali          #+#    #+#             */
/*   Updated: 2024/03/29 17:27:32 by mohilali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

int	complite_woksdup(t_tree *root, int fd_out)
{
	fd_out = root->out_fd;
	root->out_fd = dup(STDOUT_FILENO);
	if (dup_output(fd_out))
		return (1);
	return (0);
}

int	complite_woksdup_input(t_tree *root, int fd_in)
{
	fd_in = root->fd;
	root->fd = dup(STDIN_FILENO);
	if (dup_input(fd_in))
		return (1);
	return (0);
}

int	ft_dup_parent(t_tree *root)
{
	int	fd_out;
	int	fd_in;

	fd_out = 1;
	fd_in = 0;
	if (root->input_files != NULL)
	{
		if (input_files(root))
			return (1);
	}
	else if (root->fd != 0)
	{
		if (complite_woksdup_input(root, fd_in))
			return (1);
	}
	if (root->output_files != NULL)
	{
		if (output_files(root))
			return (1);
	}
	else if (root->out_fd != 1)
		if (complite_woksdup(root, fd_out))
			return (1);
	return (0);
}
