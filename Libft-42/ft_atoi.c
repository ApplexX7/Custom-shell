/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 09:40:41 by mohilali          #+#    #+#             */
/*   Updated: 2023/12/18 16:05:47 by mohilali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_handle(char *s, int sign)
{
	long int	nbr;
	long int	nb;

	nb = 0;
	nbr = 0;
	while (*s >= '0' && *s <= '9')
	{
		nb = nbr * 10 + (*s - '0');
		if (nb < nbr && sign == 1)
			return (-1);
		else if (nb < nbr && sign == -1)
			return (0);
		nbr = nb;
		s++;
	}
	return ((int) nbr * sign);
}

int	ft_atoi(const char *str)
{
	char	*s;
	int		sign;

	sign = 1;
	s = (char *) str;
	while (*s == ' ' || *s == '\n' || *s == '\v' || *s == '\f'
		|| *s == '\t' || *s == '\r')
		s++;
	if (*s == '+')
		s++;
	else if (*s == '-')
	{
		sign = -1;
		s++;
	}
	return (ft_handle(s, sign));
}
