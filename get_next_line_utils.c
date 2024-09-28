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
    int k = 0;
    int i;

    while (list)
    {
        i = 0;
        while (list->str_buf[i])
        {
            str[k++] = list->str_buf[i];
            if (list->str_buf[i] == '\n')
            {
                str[k] = '\0'; // Terminate the string at the newline
                return;
            }
            i++;
        }
        list = list->next;
    }
    str[k] = '\0'; // Make sure to null-terminate the string if there's no newline
}

int len_to_newline(t_list *list)
{
    int length = 0;
    int i;
    
    while (list)
    {
        i = 0;
        while (list->str_buf[i] && list->str_buf[i] != '\n')
        {
            length++;
            i++;
        }
        if (list->str_buf[i] == '\n')
            return length + 1; // Include '\n'
        list = list->next;
    }
    return length; // Return the total length if no newline is found
}

void dealloc(t_list **list, t_list *clean_node)
{
    t_list *tmp;

    if (!list || !*list)
        return;

    // Free all nodes in the list
    while (*list)
    {
        tmp = (*list)->next;
        free((*list)->str_buf);
        free(*list);
        *list = tmp;
    }

    if (clean_node)
    {
        if (clean_node->str_buf && clean_node->str_buf[0]) // If clean_node is not empty
            *list = clean_node; // Assign clean_node to the list
        else
        {
            free(clean_node->str_buf); // Free empty buffer
            free(clean_node); // Free node
        }
    }
}
