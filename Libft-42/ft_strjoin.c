/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 20:34:23 by mohilali          #+#    #+#             */
/*   Updated: 2023/11/01 22:49:45 by mohilali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (str == NULL)
		return (NULL);
	*str = '\0';
	ft_strlcat(str, s1, ft_strlen(s1) + ft_strlen(s2) + 1);
	ft_strlcat(str, s2, ft_strlen(s1) + ft_strlen(s2)+ 1);
	return (str);
}
