/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admaupie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 18:54:56 by admaupie          #+#    #+#             */
/*   Updated: 2022/07/14 21:14:22 by admaupie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "parse.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include "minishell.h"

int	get_word(char *buffer, t_lst *new)
{
	int	i;
	int	c;

	i = 0;
	c = ' ';
	while (buffer[i] && (c != ' ' || !is_sep(buffer[i])))
	{
		if (c == ' ' && (buffer[i] == SIMPLE_QUOTE || buffer[i] == 34))
			c = buffer[i];
		else if (c != ' ' && buffer[i] == c)
			c = ' ';
		i++;
	}
	if (c != ' ')
		return (-2);
	new->str = ft_strndup(buffer, i);
	if (!new->str)
		return (-1);
	return (1);
}

int	ft_strjoindollar(t_lst *l, char *var, int k, int dollar)
{
	int		i;
	char	*tmp;
	char	*new;

	i = ft_strlen(var);
	tmp = l->str;
	new = malloc(sizeof(char) * (ft_strlen(tmp) + i - dollar));
	if (!new)
		exit(-1);
	i = -1;
	while (++i >= 0 && tmp[i] && i < k)
		new[i] = tmp[i];
	i--;
	while (++i && var[i - k])
		new[i] = var[i - k];
	i--;
	k--;
	while (++i && ++k && tmp[k + dollar])
		new[i] = tmp[k + dollar];
	new[i] = '\0';
	free(tmp);
	tmp = NULL;
	l->str = new;
	return (1);
}

int	ft_replacedollar(t_lst *l, int k, int c, t_dynarray *darr)
{
	int		i;
	int		dollar;
	char	*var;

	dollar = 0;
	while (l->str[k + dollar] && l->str[k + dollar] != '\t'
		&& l->str[k + dollar] != ' ' && (c != 34 || l->str[k + dollar] != 34))
		dollar++;
	var = ft_getenvval(str, darr->list, darr->nb_cells); // comment faire la gestion erreur?
	i = ft_strlen(var);
	ft_strjoindollar(l, var, k, dollar);
//	free(var); faut il le free?
//	var = 0;
	return (i);
}

void	expand(t_lst *lst, t_dynarray *darr)
{
	t_lst	*ptr;
	int		i;
	int		c;

	ptr = lst->next;
	while (ptr)
	{
		if (ptr->token == 0)
		{
			i = 0;
			c = 0;
			while (ptr->str && ptr->str[i])
			{
				if (c == 0 && (ptr->str[i] == 39 || ptr->str[i] == 34))
					c = ptr->str[i];
				else if (c != 0 && ptr->str[i] == c)
					c = 0;
				else if (ptr->str[i] == '$' && c != SIMPLE_QUOTE)
					i = i + ft_replacedollar(ptr, i, c, &darr);
				i++;
			}
		}
		ptr = ptr->next;
	}
}

int	parse(char *line_buffer, t_dynarray *darr)
{
	int		i;
	int		len;
	t_lst	*lst;

	lst = ft_lstnew();
	if (!lst)
		return (print_err(-1));
	i = 0;
	while (line_buffer[i])
	{
		len = 1;
		if (!is_sep(line_buffer[i]))
			len = push_word(lst, line_buffer + i);
		else
			len = push_sep(lst, line_buffer + i);
		if (len < 0)
			return (print_err(len) + free_lst(lst));
		i = i + len;
	}
//	ft_printlst(lst);
	expand(lst, &darr);
//	ICI METTRE FONCTION NIKKI EXEC
//	ft_splitargs(lst->next);
//	ft_printlst(lst);
	free_lst(lst);
	return (1);
}

int	main(int ac, char **av, char **envp)
{
	char		*line_buffer;
//	t_dynarray	&darr;		ajouter include nikkishel

	(void)envp;//a delete
	(void)av;
	if (ac != 1)
		return (-1);
//	if (init_dyn_env(envp, &darr))
//		return (-1);
	while (1)
	{
		line_buffer = readline("$admaupie>");
		if (line_buffer == NULL)
			return (0);
		add_history(line_buffer);
		parse(line_buffer, darr);
		free(line_buffer);
	}
	return (0);
}
