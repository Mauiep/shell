/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admaupie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 18:29:06 by admaupie          #+#    #+#             */
/*   Updated: 2022/06/16 19:46:22 by admaupie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	push_word(t_lst *lst, char *buffer)
{
	t_lst	*new;
	int		ret;

	new = ft_lstnew();
	if (!new)
		return (-1);
	ret = get_word(buffer, new);
	if (ret < 0)
		return (ret);
	push_lst(new, lst);
	return (ft_strlen(new->str));
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
