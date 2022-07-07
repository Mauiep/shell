/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admaupie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 16:44:12 by admaupie          #+#    #+#             */
/*   Updated: 2022/07/07 19:12:43 by admaupie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# define SIMPLE_QUOTE 39

typedef struct s_arg
{
	char	*str;
	char	**argv;
}			t_arg;

typedef struct s_lst
{
	char			*str;
	int				token;
	void			*value;
	struct s_lst	*next;
	struct s_lst	*prev;
}					t_lst;

//main.c
int		get_word(char *buffer, t_lst *new);
int		push_word(t_lst *lst, char *buffer);
int		parse(char *line_buffer);

//ft_lst.c
int		free_lst(t_lst *src);
void	ft_printlst(t_lst *a);
void	push_lst(t_lst *new, t_lst *lst);
t_lst	*ft_lstnew(void);
int		lst_len(t_lst *lst);

//ft_libft.c
int		ft_strlen(char *str);
char	*ft_strndup(const char *src, int n);
int		ft_strcmp(const char *s1, const char *s2);

//utils.c
int		print_err(int err);
int		which_redirect(char *str);
int		is_sep(char c);

//ft_push.c
int		push_word(t_lst *lst, char *buffer);
int		push_sep(t_lst *lst, char *buffer);

// n'existent pas
int		dollar_exist(t_lst *l, char *dollar);
int		dollar_value(t_lst *l, char *dollar);
int		has_pipe(t_lst *l);
int		has_redirect(t_lst *l);

t_arg	*ft_splitargs(t_lst *lst);

#endif
