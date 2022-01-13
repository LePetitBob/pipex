/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduriez <vduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 02:18:39 by vduriez           #+#    #+#             */
/*   Updated: 2022/01/13 17:16:04 by vduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	ft_strchar(char c, char s)
{
	if (c == s)
		return (1);
	return (-1);
}

int	ft_size_w(const char *str, int i, char c)
{
	int	j;

	j = 0;
	while (ft_strchar(str[i], c) && str[i] != '\0')
	{
		i++;
		j++;
	}
	return (j);
}

int	ft_count_word(const char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] != 0)
	{
		if (ft_strchar(str[i], c) != -1)
			i++;
		else
		{
			count++;
			while (ft_strchar(str[i], c) == -1 && str[i] != 0)
			{
				i++;
			}
		}
	}
	return (count);
}

char	**ft_split(char const *str, char c)
{
	char	**tab;
	int		i[3];

	if (!str)
		return (NULL);
	i[2] = 0;
	i[0] = 0;
	tab = malloc(sizeof(char *) * (ft_count_word(str, c) + 1));
	if (!tab)
		return (0);
	while (i[0] < ft_count_word(str, c) && str[0] != 0)
	{
		i[1] = 0;
		while (ft_strchar(str[i[2]], c) != -1 && str[i[2]] != 0)
			i[2]++;
		tab[i[0]] = malloc(sizeof(char) * (ft_size_w(str, i[2], c) + 1));
		if (!tab)
			return (0);
		while (ft_strchar(str[i[2]], c) == -1 && str[i[2]] != 0)
			tab[i[0]][i[1]++] = str[i[2]++];
		tab[i[0]][i[1]] = '\0';
		i[0]++;
	}
	tab[i[0]] = 0;
	return (tab);
}
