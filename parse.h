/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admaupie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 16:44:12 by admaupie          #+#    #+#             */
/*   Updated: 2022/06/14 20:09:14 by admaupie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

typedef struct s_lst
{
	char			*str;
	int				token;
	void			*value;
	struct s_lst	*next;
	struct s_lst	*prev;
}					t_lst;

//main.c
int		print_err(int err);
int		get_word(char *buffer, t_lst *new);
int		push_word(t_lst *lst, char *buffer);
int		parse(char *line_buffer);


//ft_lst.c
t_lst	*ft_lstnew(void);
int		lst_len(t_lst *lst);

//ft_libft.c
int		ft_strlen(char *str);
char	*ft_strndup(const char *src, int n);
int		ft_strcmp(const char *s1, const char *s2);

// n'existent pas
int		dollar_exist(t_lst *l, char *dollar);
int		dollar_value(t_lst *l, char *dollar);
int		has_pipe(t_lst *l);
int		has_redirect(t_lst *l);


#endif
