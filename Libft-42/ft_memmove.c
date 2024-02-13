/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 17:42:59 by mohilali          #+#    #+#             */
/*   Updated: 2023/11/01 16:34:35 by mohilali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*ptr_dst;
	unsigned char	*ptr_src;

	ptr_dst = (unsigned char *) dst;
	ptr_src = (unsigned char *) src;
	if (dst < src)
	{
		while (len--)
		{
			*ptr_dst++ = *ptr_src++;
		}
	}
	else if (dst > src)
	{
		ptr_dst += len;
		ptr_src += len;
		while (len--)
		{
			*(--ptr_dst) = *(--ptr_src);
		}
	}
	return (dst);
}
