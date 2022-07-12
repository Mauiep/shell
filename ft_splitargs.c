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
		printf("on est dans la boucle de count i= %d str + i = %s\n", i, str + i);
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
	printf("on sort de count\n");
	return (w);
}

int		spe_lenword(char *str)
{
	char	c;
	int		i;

	c = ' ';
	i = 0;
	while (str[i] && (c != ' ' || str[i] != c))
	{
		if (c == ' ' && (str[i] == SIMPLE_QUOTE || str[i] == 34))
			c = str[i];
		else if (c != ' ' && str[i] == c)
			c = ' ';
		i++;
	}
	return (i);
}

char	*spe_get_word(char *str, int n, int size)
{
	int	w;
	int	i;
	int	j;
	char	*new;

	j = 0;
	w = 0;
	i = 0;
	while (w != n)
	{
		while (str[i] && str[i] == ' ')
			i++;
		if (str[i])
			w++;
		i = i + spe_lenword(str + i);
	}
	while (str[i] && str[i] == ' ')
			i++;
	j = spe_lenword(str + i); 
	new = ft_strndup(str + i, j);
	if (!new)
		return (NULL);
	printf("new word = %s\n", new);
	return (new);
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
	i = spe_count_words(lst->str);
	if (i > 1)
	{
		new->argv = malloc(sizeof(char *) * (i));
		if (!new->argv)
			return (NULL);
	}
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
		printf("argv[%d]=%s\n", j - 1, new->argv[j - 1]);
		j++;
	}
	return (new);
}
