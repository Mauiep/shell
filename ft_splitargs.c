/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitargs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admaupie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 17:34:36 by admaupie          #+#    #+#             */
/*   Updated: 2022/07/07 19:29:53 by admaupie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include <stdio.h>
#include <stdlib.h>

int	spe_count_words(char *str)
{
	int	w;
	int	i;
	int	c;

	c = ' ';
	w = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] && str[i] == c && c == ' ')
			i++;
		if (str[i])
			w++;
		while (str[i] && (c != ' ' || str[i] != c))
		{
			if (c == ' ' && (str[i] == SIMPLE_QUOTE || str[i] == 34))
				c = str[i];
			else if (c != ' ' && str[i] == c)
				c = ' ';
			i++;
		}
	}
	return (w);
}

char	*spe_get_word(char *str, int n, int size)
{
	int	w;
	int	i;
	int	c;

	c = ' ';
	w = 0;
	i = 0;
	while (w != n)
	{
		while (str[i] && str[i] == c)
			i++;
		if (str[i])
			w++;
		printf("un mot\n");
		while (str[i] && (c != ' ' || str[i] != c))
		{
			if (c == ' ' && (str[i] == SIMPLE_QUOTE || str[i] == 34))
				c = str[i];
			else if (c != ' ' && str[i] == c)
				c = ' ';
			i++;
		}
	}
	printf("nous en sommes a : \"%s\"\n", str + i);
}

t_arg	*ft_splitargs(t_lst *lst)
{
	t_arg	*new;
	int		i;
	int		j;

	new = malloc(sizeof(t_arg *));
	if (!new)
		return (NULL);
	new->argv = NULL;
	new->str = NULL;
	printf("On va compteoh \n");
	i = spe_count_words(lst->str);
	printf("On a compteoh i = %d\n", i);
	if (i > 1)
	{
		new->argv = malloc(sizeof(char *) * (i));
		if (!new->argv)
			return (NULL);
	}
	printf("premier mot:\n");
	new->str = spe_get_word(lst->str, 0, i);
	if (!new->str)
		return (NULL);
	printf("%s\n", new->str);
	j = 1;
	while (j < i)
	{
		new->argv[j - 1] = spe_get_word(lst->str, j, i);
		if (!new->argv[j - 1])
			return (NULL);
		j++;
	}
	return (new);
}
