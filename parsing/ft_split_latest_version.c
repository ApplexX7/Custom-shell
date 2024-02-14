/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_latest_version.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 13:02:49 by mohilali          #+#    #+#             */
/*   Updated: 2024/02/14 20:10:09 by mohilali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int ft_word(char *av)
{
	int count;
	int len;
	int i;
	
	i = 0;
	count = 0;
	len = 0;
	while(av[i])
	{
		if (!(ft_isalpha(av[i]) && av[i + 1] != av[i])|| av[i] == ' ')
			count++;
		i++;
	}
	if (count == 0)
		return (1);
	return (count);
}

char *ft_copy(char *str, char *s, int i, int len_word)
{
	int j;
	
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

char **split_parsing(char **data, int nbr, char *str)
{
	int i;
	int j;
	int word;
	int len_word;
	
	i = 0;
	word = 0;
	len_word = 0;
	while (word < (nbr * 2) && str[i])
	{
		len_word = 0;
		while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'))
			i++;
		while(str[i] && !ft_isalpha(str[i])&& str[i] != ' ')
		{
			i++;
			len_word++;
		}
		if (len_word > 0)
		{
			data[word] = malloc(sizeof(char) * (len_word + 1));
			ft_copy(data[word], str, i, len_word);
			if (!data[word])
				exit(0);
			word++;
		}
		len_word = 0;
		while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'))
			i++;
		while (str[i] && ft_isalnum(str[i]) && str[i] != ' ')
		{
			i++;
			len_word++;
		}
		data[word] = malloc(sizeof(char) * (len_word + 1));
		ft_copy(data[word], str, i, len_word);
		if (!data[word])
			exit(0);
		word++;
	}
	data[word] = 0;
	return (data);
}

char **ft_srtok(char *av)
{
	char **data;
	int split_carr;

	split_carr = ft_word(av);
	data = malloc(sizeof(char *) * ((split_carr * 2) + 1));
	if (!data)
		printf("can't allocate\n"), exit(0);
	data = split_parsing(data, split_carr, av);
	return (data);
}
