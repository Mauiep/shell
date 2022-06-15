/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admaupie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 18:54:56 by admaupie          #+#    #+#             */
/*   Updated: 2022/06/15 20:05:35 by admaupie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "parse.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>

#define SIMPLE_QUOTE 39

void	ft_printlst(t_lst *a)
{
	int		i;
	t_lst	*tmp;

	i = 0;
	tmp = a;
	while (tmp)
	{
		if (tmp->str)
			printf("- %s\n", tmp->str);
		tmp = tmp->next;
		i++;
	}
	printf("%d\n", i);
}

int print_err(int err)
{
    if (err == -1)
        write(2, "Error malloc\n", 13);
    else if (err == -2)
        write(2, "Missing quotes\n", 15);
    else if (err == -3)
        write(2, "Syntax error\n", 13);
    return (err);
}

int	is_sep(char c)
{
	if (c == ';' || c == '>' || c == '<' || c == '|')
		return (1);
	return (0);
}

int get_word(char *buffer, t_lst *new)
{
    int i;
  	int c;

    i = 0;
/*    c = ' ';
    while (buffer[i] && ((c == ' ' && buffer[i] != c) || (c != ' '
        && buffer[i] == c && (buffer[i + 1] != 0 || buffer[i + 1] != ' '))))
    {
        if (c == ' ' && (buffer[i] == SIMPLE_QUOTE || buffer[i] == 34
				|| buffer[i] == 96))
            c = buffer[i];
        else if (buffer[i] == c)
            c = ' ';
        i++;
    }
	if (buffer[i] == c && (buffer[i + 1] != ' '))
	{
		i++;
		c = ' ';
	}
	printf("i = %d\n", i);
    if (buffer[i] == 0 && c != ' ')//CORRESPOND A : on arrive a \0 sans retrouver le guillemet
        return (-2);*/
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

void	push_lst(t_lst *new, t_lst *lst)
{
    t_lst   *tmp;

    tmp = lst;
    if (tmp)
    {
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = new;
		new->prev = tmp;
    }
    else
        lst = new;
	return ;
}

int push_word(t_lst *lst, char *buffer)
{
    t_lst   *new;
    int     ret;

    new = ft_lstnew();
    if (!new)
        return (-1);
    ret = get_word(buffer, new);
    if (ret < 0)
        return (ret);
	push_lst(new, lst);
    return (ft_strlen(new->str));
}

int	which_redirect(char *str)
{
	if (ft_strcmp(str, "|") == 0)
		return (1);
	else if (ft_strcmp(str, ">") == 0)
		return (2);
	else if (ft_strcmp(str, "<") == 0)
		return (3);
	else if (ft_strcmp(str, ">>") == 0)
		return (4);
	else if (ft_strcmp(str, "<<") == 0)
		return (5);
	else
		return (-1);
}

int	push_sep(t_lst *lst, char *buffer)
{
	int		i;
	t_lst	*tmp;
	t_lst	*new;
	int		token;

	i = 0;
    tmp = lst;
    new = ft_lstnew();
    if (!new)
        return (-1);
	while (is_sep(buffer[i]))
		i++;
    new->str = ft_strndup(buffer, i);
    if (!new->str)
        return (-1);
	token = which_redirect(new->str);
	if (token == -1)
		return (-3);
	new->token = token;
	push_lst(new, lst);
	return (i);
}

int	ft_replacedollar(t_lst *l, int k, int c)
{
	int		i;
	int		dollar;
	char	*var;
	char	*new;
	int		n;

	dollar = 0;
	i = 0;
	while (l->str[k + dollar] && l->str[k + dollar] != '\t'
			&& l->str[k + dollar] != ' ' && (c != 34 || l->str[k + dollar] != 34))
		dollar++;
	var = "";//fonction pour choper la str dans **envp
	n = ft_strlen(var);
	new = malloc(ft_strlen(l->str) + n - dollar);
	if (!new)
		return (-1);
	while (l->str[i] && i < k)
	{
		new[i] = l->str[i];
		i++;
	}
	while (var[i - k])
	{
		new[i] = var[i];
		i++;
	}
	while (l->str[k + dollar])
	{
		new[i] = l->str[k + dollar];
		i++;
		k++;
	}
	new[i] == '\0';
	var = l->str;
	l->str = new;
	free(var);
	var = 0; 
	return (n - 2);
}

void	expand(t_lst *lst)
{
	t_lst	*ptr;
	int		i;
	int		c;

	ptr = lst;
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
					i = i + ft_replacedollar(ptr, i, c);//LA CHECK ENV ET REMPLACER
				i++;
			}
			//	ENSUITE gerer " / '
		}
		ptr = ptr->next;
	}
}

int parse(char *line_buffer)
{
    int     i;
    int     len;
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
            return (print_err(len));
        i = i + len;
    }
	ft_printlst(lst);
	expand(lst);
	ft_printlst(lst);
	return (1);
}

int	main(int ac, char **av, char **envp)
{
	char	*line_buffer;

	if (ac != 1)
		return (-1);
	while (1)
	{
		line_buffer = readline("$admaupie>");
		if (line_buffer == NULL)
			return (0);
		add_history(line_buffer);
		parse(line_buffer);
		free(line_buffer);
	}
	printf("arg[%d] = %s\n", 0, av[0]);
	return (0);
}
