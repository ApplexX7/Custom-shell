/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 13:56:50 by mohilali          #+#    #+#             */
/*   Updated: 2024/03/25 17:13:49 by mohilali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

int	ft_pwd(t_tree *root)
{
	char	*buffer;
	size_t	size;

	size = 1024;
	buffer = malloc(sizeof(char) * size);
	if (!buffer)
		return (write(2, "Failed to allocated\n", 20), 1);
	if (!getcwd(buffer, size))
		return (EXIT_FILENOTEXIST);
	ft_putstr_fd(buffer, root->out_fd);
	ft_putchar_fd('\n', root->out_fd);
	return (0);
}
