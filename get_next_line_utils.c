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
            if (list->str_buf[i] == '\n')
                return 1;
            i++;
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
    int k;
    int i;

    k = 0;
  while (list) 
  {
        i = 0;
        while (list->str_buf[i]) {
            str[k++] = list->str_buf[i];
            if (list->str_buf[i] == '\n') {
                str[k] = '\0'; // Null-terminate immediately after newline
                return;
            }
            i++;
        }
        list = list->next;
    }
    str[k] = '\0'; // Ensure str is always null-terminated
}



int len_to_newline(t_list *list)
{
    int length;
    int i;
    
    length = 0;
     while (list) 
     {
        i = 0;
        while (list->str_buf[i] && list->str_buf[i] != '\n') 
        {
            length++;
            i++;
        }
        if (list->str_buf[i] == '\n')
            return length + 1;
        list = list->next;
    }
    return length;
}


void dealloc(t_list **list, t_list *clean_node) {
    t_list *tmp;

    if (!list || !*list)
        return;

    while (*list) {
        tmp = (*list)->next;
        free((*list)->str_buf); // Free the buffer of the current node
        free(*list);            // Free the current node
        *list = tmp;           // Move to the next node
    }

    // Handle the clean_node separately
    if (clean_node) {
        if (clean_node->str_buf[0]) { // Check if the clean node has content
            clean_node->next = NULL; // Important to avoid dangling pointers
            *list = clean_node;      // Set clean_node as the new list head
        } else {
            free(clean_node->str_buf); // Free if empty
            free(clean_node);          // Free the node itself
        }
    }
}
