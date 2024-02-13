/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 12:51:12 by mohilali          #+#    #+#             */
/*   Updated: 2023/11/01 16:50:55 by mohilali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*s;
	int		len;
	char	*src;

	src = (char *) s1;
	len = ft_strlen(src);
	s = malloc(len + 1);
	if (s)
	{
		ft_strlcpy(s, src, len + 1);
		return (s);
	}
	return (NULL);
}
