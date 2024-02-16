/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 16:54:42 by mohilali          #+#    #+#             */
/*   Updated: 2023/11/08 16:39:52 by mohilali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *ptr, int c, size_t count)
{
	unsigned char	*pt;

	pt = (unsigned char *) ptr;
	while (count)
	{
		*pt = (unsigned char)c;
		count--;
		pt++;
	}
	return (ptr);
}
