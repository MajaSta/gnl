/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Oceano <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 11:48:03 by Oceano            #+#    #+#             */
/*   Updated: 2023/02/19 18:50:24 by utente           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <stdio.h>

void polish_list(t_list **list)
{
    t_list *last_node;
    t_list *clean_node;
    int i;
    int k;
    char *buf;

    buf = malloc(BUFFER_SIZE + 1);
    clean_node = malloc(sizeof(t_list));
    if (!buf || !clean_node)
        return (free(buf), free(clean_node), (void)0);
    last_node = find_last_node(*list);
    i = 0;
    while (last_node->str_buf[i] && last_node->str_buf[i] != '\n')
        i++;
    k = 0;
    while (last_node->str_buf[i])
        buf[k++] = last_node->str_buf[++i];
    buf[k] = '\0';
    clean_node->str_buf = buf;
    clean_node->next = NULL;
    dealloc(list, clean_node);
}



char *get_line(t_list *list)
{
    int str_len;
    char *next_str;

    if (list == NULL)
        return (NULL);
    
    str_len = len_to_newline(list);
    next_str = malloc(str_len + 1);
    if (next_str == NULL)
        return (NULL);
    
    copy_str(list, next_str);
    return (next_str);
}

void append(t_list **list, char *buf)
{
    t_list *new_node;
    t_list *last_node;

    new_node = malloc(sizeof(t_list));
    if (new_node == NULL)
        return;

    new_node->str_buf = buf;
    new_node->next = NULL;

    last_node = find_last_node(*list);
    if (last_node == NULL)
        *list = new_node;
    else
        last_node->next = new_node;
}

void create_list(t_list **list, int fd)
{
    int char_read;	
    char *buf;

    while (!found_newline(*list))
    {
        buf = malloc(BUFFER_SIZE + 1);
        if (buf == NULL)
            return;

        char_read = read(fd, buf, BUFFER_SIZE);
        if (char_read <= 0)
        {
            free(buf);
            return;
        }
        buf[char_read] = '\0';
        append(list, buf);
    }
}

char *get_next_line(int fd)
{
    static t_list *list; 
    char *next_line;
        
    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);

    create_list(&list, fd);
    if (list == NULL)
        return (NULL);
    
    next_line = get_line(list);
    polish_list(&list);
    return (next_line);
}

