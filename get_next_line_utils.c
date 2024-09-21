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

/*
 * Check if a newline exists in the linked list.
 */
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


/*
 * Find and return the last node in the linked list.
 */

t_list *find_last_node(t_list *list)
{
    if (!list)
        return NULL;

    while (list->next)
        list = list->next;
    
    return list;
}

/*
 * Copy (string\n]
*/
/*
 * Copy the string until the newline into the provided buffer.
 */
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


/*
 * find the len to new line in
 * my linked list
*/
/*
 * Find the length to newline in the linked list.
 */
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


/*
 * dealloc all from head
 * set heat->NULL
*/
/*
 * Dealloc all from head and set head to NULL.
 * Optionally keep clean_node if it has data.
 */
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
    
    *list = NULL;  // Clear the list pointer

    // If clean_node contains data, set it as the new head
    if (clean_node && clean_node->str_buf[0])
        *list = clean_node;
    else if (clean_node)  // If no data, free the clean_node
        free(clean_node->str_buf), free(clean_node);
}