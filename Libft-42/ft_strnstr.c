/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 10:52:13 by mohilali          #+#    #+#             */
/*   Updated: 2024/02/26 12:11:59 by ayait-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
int	find_word(char *haystack, char *needle, size_t i, size_t len)
{
	while (i < len && *needle != '\0')
	{
		if (*haystack != *needle)
			return (0);
		haystack++;
		needle++;
		i++;
	}
	if (*needle == '\0' && i <= len)
		return (1);
	return (0);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;

	i = 0;
	if (*needle == '\0')
		return ((char *) haystack);
	if (len == 0 || *haystack == '\0')
		return (NULL);
	while (i < len && haystack[i])
	{
		if (find_word((char *)(haystack + i), (char *)needle, i, len) == 1)
			return ((char *)(haystack + i));
		i++;
	}
	return (NULL);
}
*/
char    *ft_strnstr(const char *haystack, const char *needle, size_t len)
{
    size_t    i;
    int        j;

    i = 0;
    j = 0;
    if (needle[0] == '\0')
        return ((char *)haystack);
    while (i < len && haystack[i])
    {
        j = 0;
        while (haystack[i + j] == needle[j] && needle[j] && (i + j) < len)
            j++;
        if (needle[j] == '\0')
            return ((char *)(haystack + i));
        i++;
    }
    return (0);
}
