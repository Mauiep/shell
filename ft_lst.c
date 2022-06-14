/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admaupie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 15:11:19 by admaupie          #+#    #+#             */
/*   Updated: 2022/06/13 16:16:45 by admaupie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include <stddef.h>
#include <stdlib.h>

int	lst_len(t_lst *lst)
{
	int		i;
	t_lst	*ptr;

	ptr = lst;
	i = 0;
	while (ptr && ptr->next && ++i)
		ptr = ptr->next;
	return (i);
}

t_lst	*ft_lstnew(void)
{
	t_lst	*new;

	new = malloc(sizeof(t_lst));
	if (!new)
		return (NULL);
	new->str = NULL;
	new->next = NULL;
	new->prev = NULL;
	new->token = 0;
	return (new);
}
