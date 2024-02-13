/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 11:14:05 by mohilali          #+#    #+#             */
/*   Updated: 2023/11/08 16:37:10 by mohilali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_check_numbers(int n)
{
	int	nbr;

	nbr = 0;
	if (n < 0)
	{
		n = -n;
		nbr = 1;
	}
	while (n > 0)
	{
		n = n / 10;
		nbr++;
	}
	return (nbr);
}

static void	ft_copy(char *s, unsigned int len, unsigned int n)
{
	unsigned int	i;

	i = len;
	while (len-- && n > 0)
	{
		s[len] = (n % 10) + '0';
		n = n / 10;
	}
	s[i] = '\0';
}

char	*ft_itoa(int n)
{
	char			*s;
	unsigned int	len;

	len = ft_check_numbers(n);
	if (n == 0)
	{
		s = malloc(2);
		if (!s)
			return (NULL);
		s[0] = '0';
		s[1] = '\0';
		return (s);
	}
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	s = malloc(len + 1);
	if (!s)
		return (NULL);
	if (n < 0)
	{
		s[0] = '-';
		n = -n;
	}
	ft_copy(s, len, n);
	return (s);
}
