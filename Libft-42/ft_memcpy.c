/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 17:22:07 by mohilali          #+#    #+#             */
/*   Updated: 2023/11/08 16:38:48 by mohilali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*pt;
	unsigned char	*sr;

	if (dst == NULL && src == NULL)
		return (NULL);
	pt = (unsigned char *) dst;
	sr = (unsigned char *) src;
	while (n--)
	{
		*pt = *sr;
		pt++;
		sr++;
	}
	return (dst);
}
