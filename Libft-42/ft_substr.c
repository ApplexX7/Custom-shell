/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 17:43:33 by mohilali          #+#    #+#             */
/*   Updated: 2023/12/18 16:05:17 by mohilali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_copy_st(const char *s, char *src, int start, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len && s[start + i])
	{
		src[i] = s[start + i];
		i++;
	}
	src[i] = '\0';
	return (src);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*src;
	int		i;

	i = 0;
	if (s == NULL)
		return (NULL);
	if ((unsigned int)ft_strlen(s) < start)
	{
		src = malloc(1);
		if (!src)
			return (NULL);
		src[0] = '\0';
		return (src);
	}
	if ((unsigned int)ft_strlen(s) - start < len)
		src = malloc((ft_strlen(s) - start) + 1);
	else
		src = malloc(len + 1);
	if (!src)
		return (NULL);
	ft_copy_st(s, src, start, len);
	return (src);
}
