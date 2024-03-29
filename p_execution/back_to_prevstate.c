/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   back_to_prevstate.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 22:17:44 by mohilali          #+#    #+#             */
/*   Updated: 2024/03/29 15:54:06 by ayait-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

void	set_back_io(int input, int output)
{
	if (dup2(input, STDIN_FILENO) == -1)
	{
		perror("dup");
		return ;
	}
	if (input != 0)
		ft_close(input);
	if (dup2(output, STDOUT_FILENO) == -1)
	{
		perror("dup");
		return ;
	}
	if (output != 1)
		ft_close(output);
}

int	dup_output(int fd_out)
{
	if (dup2(fd_out, STDOUT_FILENO) == -1)
	{
		perror("dup2 :");
		return (1);
	}
	ft_close(fd_out);
	return (0);
}

int	dup_input(int fd_in)
{
	if (dup2(fd_in, STDIN_FILENO) == -1)
	{
		perror("dup2 :");
		return (1);
	}
	ft_close(fd_in);
	return (0);
}
