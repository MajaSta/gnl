/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 13:00:56 by marvin            #+#    #+#             */
/*   Updated: 2024/09/16 13:00:56 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

typedef struct s_list
{
    char            *str_buf;
    struct s_list   *next;
}t_list;

/* Function Prototypes */
char    *get_next_line(int fd);
void    append(t_list **list, char *buf);
char    *get_line(t_list *list);
void    polish_list(t_list **list);
void    dealloc(t_list **list, t_list *clean_node, char *buf);
int     found_newline(t_list *list);
int     len_to_newline(t_list *list);
void    copy_str(t_list *list, char *str);
t_list  *find_last_node(t_list *list);

#endif

