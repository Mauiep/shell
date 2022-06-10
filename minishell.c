#include <stdio.h>
#include <stdlib.h>

#define SIMPLE_QUOTE=39

int print_err(int err)
{
    if (err == -1)
        write(2, "Error malloc\n", 14);
    else if (err == -2)
        write(2, "Missing quotes\n", 16);
    return (err);
}

int get_word(char *buffer, t_lst *new)
{
    int i;
    int c;

    i = 0;
    c = ' ';
    while (buffer[i] && ((c == ' ' && buffer[i] != c) || (c != ' '
        && buffer[i] == c && (buffer[i + 1] != 0 || buffer[i + 1] != ' '))))
    {
        if (c == ' ' && (buffer[i] == SIMPLE_QUOTE || buffer[i] == 34 || buffer[i] == 96))
            c = *buffer;
        else if (buffer[i] == c)
            c == ' ';
        i++;
    }
    if (buffer[i] == 0 && c != ' ')
        return (-2);
    if (c != ' ')
        i++;
    new->str = ft_strndup(buffer, i);
    if (!new->str)
        return (-1);
    return (1);
}

int nb_quotes(char *buffer)
{
    int i;
    int nb;
    int c;

    i = 1;
    nb = 1;
    if (*buffer == SIMPLE_QUOTE || *buffer == 34 || *buffer == 96)
    {
        c == *buffer;
        while (buffer[i] != c && (buffer[i + 1] != 0 || buffer[i + 1] != ' '))
        {
            if (buffer[i] == c)
                nb++;
            i++;
        }
        nb++;
    }
    else
        return (0);
}

int push_word(t_lst *lst, char *buffer)
{
    t_lst   *new;
    t_lst   *tmp;
    int     ret;

    tmp = lst;
    new = ft_lstnew();
    if (!new)
        return (print_err(-1));
    ret = get_word(buffer, new);
    if (ret < 0)
        return (print_err(ret));
    if (tmp)
    {
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = new
    }
    else
        lst = new;
    return (lst_len(new->str));
}

int parse(char *line_buffer)
{
    int     i;
    int     len;

    i = 0;
    while (line_buffer[i])
    {
        if (line_buffer[i] != ' ')
            len = push_word(lst, line_buffer + i);
        if (len < 0)
            return (print_err(len));
        i = i + len;
    }
}

int main(int ac, char **av, char **envp)
{
    char    *line_buffer;
    t_lst   *lst;

    lst = NULL;
    if (ac != 1)
		return (printf("Error\n"));
	while (1)
	{
		line_buffer = readline("$>");
		if (line_buffer == NULL)
			return (0);
		parse(line_buffer);
		free(line_buffer);
	}
    return (1);
}