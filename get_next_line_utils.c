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
                str[k] = '\0';
                return;
            }
            i++;
        }
        list = list->next;
    }
    str[k] = '\0';
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
            return length + 1; // Uwzględnij '\n'
        list = list->next;
    }
    return length; // W przypadku braku '\n'
}



void dealloc(t_list **list, t_list *clean_node)
{
    t_list *tmp;

    if (!list || !*list)
        return;

    // Zwalnianie wszystkich węzłów listy
    while (*list)
    {
        tmp = (*list)->next;
        free((*list)->str_buf);
        free(*list);
        *list = tmp;
    }

   if (clean_node)
    {
        if (clean_node->str_buf[0]) // Jeśli clean_node nie jest pusty
            *list = clean_node;
        else
        {
            free(clean_node->str_buf);
            free(clean_node);
        }
    }
}
