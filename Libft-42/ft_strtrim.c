/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 18:14:24 by mohilali          #+#    #+#             */
/*   Updated: 2023/11/06 13:00:08 by mohilali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	int		len;
	char	*str;
	int		i;

	i = 0;
	start = 0;
	if (s1 == NULL || set == NULL)
		return (NULL);
	end = ft_strlen(s1) - 1;
	while (start <= end && ft_strchr(set, s1[start]) != NULL)
		start++;
	while (end >= start && ft_strchr(set, s1[end]) != NULL)
		end--;
	len = end - start + 1;
	if (len <= 0)
		return (ft_strdup(""));
	str = (char *) malloc(len + 1);
	if (!str)
		return (NULL);
	while (i < len)
		str[i++] = s1[start++];
	str[i] = '\0';
	return (str);
}
