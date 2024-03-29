/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 13:53:25 by mohilali          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/03/28 18:08:41 by mohilali         ###   ########.fr       */
=======
/*   Updated: 2024/03/28 17:51:24 by ayait-el         ###   ########.fr       */
>>>>>>> e9c36e0508e6eb612d8e8c07d9bc72bff1ba4c24
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	unsigned char	*s1;
	unsigned char	*s2;

	s1 = (unsigned char *) str1;
	s2 = (unsigned char *) str2;
	while (n > 0 && *s1 && *s2)
	{
		if (*s1 != *s2)
			break;
		s1++;
		s2++;
		n--;
	}
	if (n == 0)
		return (0);
	return (*s1 - *s2);
}
