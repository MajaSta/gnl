/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 19:47:12 by marvin            #+#    #+#             */
/*   Updated: 2024/09/16 19:47:12 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

int     found_newline(t_list *list);
void    append(t_list **list_adrs, char *buf);
char    *get_line(t_list *list_adrs);
void    polish_list(t_list **list_adrs);
void    dealloc(t_list **list_adrs, t_list *clean_node, char *buf);
int     len_to_newline(t_list *list_adrs);
void    copy_str(t_list *list_adrs, char *str);
t_list  *find_last_node(t_list *list_adrs);

char *get_next_line(int fd)
{
    static t_list *list = NULL;
    char *next_line;

    if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)
        return (NULL);

    while (!found_newline(list))
    {
        char *buf = malloc(BUFFER_SIZE + 1);
        if (!buf)
            return (NULL);

        int char_read = read(fd, buf, BUFFER_SIZE);
        if (char_read <= 0)
        {
            free(buf);
            if (!list)
                return (NULL);
            break;
        }

        buf[char_read] = '\0';
        append(&list, buf);
    }

    next_line = get_line(list);
    polish_list(&list);
    return (next_line);
}

int found_newline(t_list *list)
{
    while (list)
    {
        int i = 0;
        while (list->str_buf[i])
        {
            if (list->str_buf[i] == '\n')
                return (1);
            i++;
        }
        list = list->next;
    }
    return (0);
}

void append(t_list **list_adrs, char *buf)
{
    t_list *new_node = malloc(sizeof(t_list));
    if (!new_node)
        return;

    new_node->str_buf = buf;
    new_node->next = NULL;

    if (!*list_adrs)
        *list_adrs = new_node;
    else
    {
        t_list *last = find_last_node(*list_adrs);
        last->next = new_node;
    }
}

t_list *find_last_node(t_list *list_adrs)
{
    while (list_adrs && list_adrs->next)
        list_adrs = list_adrs->next;
    return list_adrs;
}

char *get_line(t_list *list_adrs)
{
    if (!list_adrs)
        return (NULL);

    int str_len = len_to_newline(list_adrs);
    char *next_str = malloc(str_len + 1);
    if (!next_str)
        return (NULL);

    copy_str(list_adrs, next_str);
    return (next_str);
}

int len_to_newline(t_list *list_adrs)
{
    int len = 0;
    while (list_adrs)
    {
        int i = 0;
        while (list_adrs->str_buf[i])
        {
            if (list_adrs->str_buf[i] == '\n')
                return (++len);
            i++;
            len++;
        }
        list_adrs = list_adrs->next;
    }
    return (len);
}

void copy_str(t_list *list_adrs, char *str)
{
    int i, k = 0;
    while (list_adrs)
    {
        i = 0;
        while (list_adrs->str_buf[i])
        {
            str[k++] = list_adrs->str_buf[i];
            if (list_adrs->str_buf[i++] == '\n')
            {
                str[k] = '\0';
                return;
            }
        }
        list_adrs = list_adrs->next;
    }
    str[k] = '\0';
}

void polish_list(t_list **list_adrs)
{
    t_list *last_node = find_last_node(*list_adrs);
    if (!last_node)
        return;

    int i = 0;
    while (last_node->str_buf[i] && last_node->str_buf[i] != '\n')
        i++;

    if (!last_node->str_buf[i] || !last_node->str_buf[i + 1])
    {
        dealloc(list_adrs, NULL, NULL);
        return;
    }

    char *new_buf = malloc(BUFFER_SIZE + 1);
    if (!new_buf)
        return;

    int k = 0;
    i++;
    while (last_node->str_buf[i])
        new_buf[k++] = last_node->str_buf[i++];
    new_buf[k] = '\0';

    t_list *new_node = malloc(sizeof(t_list));
    if (!new_node)
    {
        free(new_buf);
        return;
    }

    new_node->str_buf = new_buf;
    new_node->next = NULL;

    dealloc(list_adrs, new_node, NULL);
}

void	dealloc(t_list **list, t_list *clean_node, char *buf)
{
	t_list	*tmp;

	if (NULL == *list)
		return ;
	while (*list)
	{
		tmp = (*list)->next;
		free((*list)->str_buf);
		free(*list);
		*list = tmp;
	}
	*list = NULL;
	if (clean_node->str_buf[0])
		*list = clean_node;
	else
	{
		free(buf);
		free(clean_node);
	}
}

// Main function for testing
int main()
{
    int fd = open("test.txt", O_RDONLY);
    if (fd < 0)
    {
        perror("open");
        return (1);
    }

    char *line;
    int lines = 1;

    while ((line = get_next_line(fd)))
    {
        printf("%d: %s", lines++, line);
        free(line);  // Don't forget to free the returned line.
    }

    close(fd);
    return (0);
}
