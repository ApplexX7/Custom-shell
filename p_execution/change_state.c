/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_state.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 10:28:03 by mohilali          #+#    #+#             */
/*   Updated: 2024/03/08 10:28:44 by mohilali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

void set_back_io(int save_state)
{
	if (dup2(save_state, STDOUT_FILENO) == -1)
	{
		perror("Error");
		return ;
	}
}

int	ft_dup_parent(t_tree *root)
{
	int save_state;
	int fd;

	save_state = 1;
	if (root->output_file != NULL)
	{
		save_state = dup(STDOUT_FILENO);
		if (save_state == -1)
			return (-1);
		fd = open_files(root->output_file, 2);
		if (fd == -1)
			return (-1);
		if (dup2(fd, STDOUT_FILENO) == -1)
		{
			handle_error();
			return (1);
		}
	}
	return (save_state);
}
