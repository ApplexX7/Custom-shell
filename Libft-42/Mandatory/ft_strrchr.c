/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 10:32:23 by mohilali          #+#    #+#             */
/*   Updated: 2023/11/01 17:15:16 by mohilali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		len;
	char	*str;

	str = (char *) s;
	len = 0;
	len = ft_strlen(str);
	if (c == '\0')
		return (&str[len]);
	while (len >= 0)
	{
		if (str[len] == (char) c)
			return (&str[len]);
		len--;
	}
	return (NULL);
}
