/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_seven.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 00:22:17 by mohilali          #+#    #+#             */
/*   Updated: 2024/03/30 01:42:53 by mohilali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset_tty(void)
{
	static int				count = 0;
	static struct termios	g_original_terminos;

	if (count == 0)
	{
		tcgetattr(STDIN_FILENO, &g_original_terminos);
		count++;
	}
	if (count > 0)
		tcsetattr(STDIN_FILENO, TCSANOW, &g_original_terminos);
}

void	init_variables(int *a, int *b, int *c, int *d)
{
	*a = 0;
	*b = 0;
	*c = 0;
	*d = 0;
}
