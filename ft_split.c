/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduriez <vduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 02:18:39 by vduriez           #+#    #+#             */
/*   Updated: 2021/11/29 02:53:12 by vduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int		ft_strchar(char c, char s)
{
	if (c == s)
		return (1);
	return (-1);
}

int		ft_size_w(const char *str, int i, char c)
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

int		ft_count_word(const char *str, char c)
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
	int		i;
	int		j;
	int		k;

	if (!str)
		return (NULL);
	k = 0;
	i = 0;
	if (!(tab = malloc(sizeof(char *) * (ft_count_word(str, c) + 1))))
		return (0);
	while (i < ft_count_word(str, c) && str[0] != 0)
	{
		j = 0;
		while (ft_strchar(str[k], c) != -1 && str[k] != 0)
			k++;
		if (!(tab[i] = malloc(sizeof(char) * (ft_size_w(str, k, c) + 1))))
			return (0);
		while (ft_strchar(str[k], c) == -1 && str[k] != 0)
			tab[i][j++] = str[k++];
		tab[i][j] = '\0';
		i++;
	}
	tab[i] = 0;
	return (tab);
}
