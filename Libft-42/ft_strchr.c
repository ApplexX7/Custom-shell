/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 21:44:35 by mohilali          #+#    #+#             */
/*   Updated: 2024/02/26 18:45:37 by mohilali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned int	i;
	char			x;

	if (!s)
		return (NULL);
	x = (char)c;
	i = 0;
	while (s[i])
	{
		if (s[i] == x)
			return ((char *) &s[i]);
		i++;
	}
	if (s[i] == x)
		return ((char *) &s[i]);
	return (NULL);
}

