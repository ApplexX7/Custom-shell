/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 20:39:43 by mohilali          #+#    #+#             */
/*   Updated: 2023/11/03 15:16:14 by mohilali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**free_string(char **s, int i)
{
	while (i > 0)
	{
		i--;
		free(s[i]);
	}
	free(s);
	return (0);
}

static int	ft_count_word(const char *s, char c)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			i++;
		else
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (count);
}

static char	*ft_copy(char *str, const char *s, int i, int len_word)
{
	int	j;

	j = 0;
	while (len_word > 0)
	{
		str[j] = s[i - len_word];
		j++;
		len_word--;
	}
	str[j] = '\0';
	return (str);
}

static char	**ft_split_word(const char *s, char c, char **str, int n)
{
	int	len_word;
	int	i;
	int	word;

	i = 0;
	word = 0;
	len_word = 0;
	while (word < n)
	{
		while (s[i] && s[i] == c)
			i++;
		while (s[i] && s[i] != c)
		{
			len_word++;
			i++;
		}
		str[word] = (char *)malloc(sizeof(char) * (len_word + 1));
		if (!str[word])
			return (free_string(str, word));
		ft_copy(str[word], s, i, len_word);
		len_word = 0;
		word++;
	}
	str[word] = 0;
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char			**str;
	unsigned int	nbr;

	if (s == NULL)
		return (NULL);
	nbr = ft_count_word(s, c);
	str = (char **)malloc(sizeof(char *) * (nbr + 1));
	if (!str)
		return (NULL);
	str = ft_split_word(s, c, str, nbr);
	return (str);
}
