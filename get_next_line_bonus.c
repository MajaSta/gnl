/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utente <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 00:45:29 by utente            #+#    #+#             */
/*   Updated: 2023/02/20 00:45:34 by utente           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stdlib.h>
#include <stdio.h>//TODO


int find_newline_position(char *str_buf)
{
    int i = 0;
    while (str_buf[i] && str_buf[i] != '\n')
        i++;
    return str_buf[i] == '\n' ? i + 1 : -1;  // Return position after newline or -1 if none found
}

t_list *create_clean_node(t_list *last_node, int start_pos)
{
    t_list *clean_node;
    char *buf;
    int k = 0;

    buf = malloc(BUFFER_SIZE + 1);
    if (!buf)
        return NULL;

    while (last_node->str_buf[start_pos])
        buf[k++] = last_node->str_buf[start_pos++];
    buf[k] = '\0';

    clean_node = malloc(sizeof(t_list));
    if (!clean_node) {
        free(buf);
        return NULL;
    }
    clean_node->str_buf = buf;
    clean_node->next = NULL;
    return clean_node;
}

void polish_list(t_list **list)
{
    t_list *last_node = find_last_node(*list);
    int newline_pos = find_newline_position(last_node->str_buf);
    t_list *clean_node;

    if (newline_pos == -1) {
        dealloc(list, NULL, NULL);
        return;
    }
    clean_node = create_clean_node(last_node, newline_pos);
    dealloc(list, clean_node, clean_node->str_buf);  // Clean old list and set new
}


char	*get_line(t_list *list)
{
	int		str_len;
	char	*next_str;

	if (NULL == list)
		return (NULL);
	str_len = len_to_newline(list);
	next_str = malloc(str_len + 1);
	if (NULL == next_str)
		return (NULL);
	copy_str(list, next_str);
	return (next_str);
}

void	append(t_list **list, char *buf, int fd)
{
	t_list	*new_node;
	t_list	*last_node;

	last_node = find_last_node(list[fd]);
	new_node = malloc(sizeof(t_list));
	if (NULL == new_node)
		return ;
	if (NULL == last_node)
		list[fd] = new_node;
	else
		last_node->next = new_node;
	new_node->str_buf = buf;
	new_node->next = NULL;
}

int read_and_append(t_list **list, int fd)
{
    int char_read;
    char *buf = malloc(BUFFER_SIZE + 1);

    if (!buf)
        return -1;

    char_read = read(fd, buf, BUFFER_SIZE);
    if (char_read <= 0) {
        free(buf);
        return 0;
    }
    buf[char_read] = '\0';
    append(list, strdup(buf)); 
    free(buf);
    return 1;
}

void create_list(t_list **list, int fd)
{
    char *buf = malloc(BUFFER_SIZE + 1);
    if (!buf)
        return;

    int char_read;
    while (1)
    {
        char_read = read(fd, buf, BUFFER_SIZE);
        if (char_read <= 0)
        {
            free(buf);
            if (char_read == 0 && *list)
                return; 
            break;
        }
        buf[char_read] = '\0';
        append(list, strdup(buf));
        if (found_newline(*list))
            break;
    }
    free(buf);
}



char *get_next_line(int fd)
{
    static t_list *list = NULL;
    char *next_line;

    if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)
        return NULL;

    create_list(&list, fd);
    if (!list)
        return NULL;

    next_line = get_line(list);
    polish_list(&list);

    if (!next_line && list) 
    {
        next_line = get_line(list);
        polish_list(&list);
    }
    return next_line;
}

