/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Oceano <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 17:58:53 by Oceano            #+#    #+#             */
/*   Updated: 2023/02/19 18:51:33 by utente           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>

int found_newline(t_list *list)
{
    int i;

    while (list)
    {
        i = 0;
        while (list->str_buf[i])
        {
            if (list->str_buf[i++] == '\n')
                return 1;
        }
        list = list->next;
    }
    return 0;
}

t_list *find_last_node(t_list *list)
{
    if (!list)
        return NULL;

    while (list->next)
        list = list->next;
    
    return list;
}

void copy_str(t_list *list, char *str)
{
    int i, k = 0;

    while (list)
    {
        i = 0;
        while (list->str_buf[i])
        {
            str[k++] = list->str_buf[i++];
            if (list->str_buf[i - 1] == '\n')
            {
                str[k] = '\0';
                return;
            }
        }
        list = list->next;
    }
    str[k] = '\0';
}

int len_to_newline(t_list *list)
{
    int i, len = 0;

    while (list)
    {
        i = 0;
        while (list->str_buf[i])
        {
            if (list->str_buf[i] == '\n')
                return (len + 1);
            ++i;
            ++len;
        }
        list = list->next;
    }
    return len;
}

void dealloc(t_list **list, t_list *clean_node)
{
    t_list *tmp;

    if (!list || !*list)
        return;

    while (*list)
    {
        tmp = (*list)->next;
        free((*list)->str_buf);
        free(*list);
        *list = tmp;
    }
    
    *list = NULL;

    if (clean_node && clean_node->str_buf[0])
        *list = clean_node;
    else if (clean_node) 
        free(clean_node->str_buf), free(clean_node);
}
