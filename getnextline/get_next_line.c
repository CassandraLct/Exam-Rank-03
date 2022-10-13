/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 15:53:54 by clecat            #+#    #+#             */
/*   Updated: 2022/10/13 16:55:20 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
//pour compiler : gcc -DBUFFER_SIZE = 5
char    *get_next_line(int fd)
{
    int i = 0;
    int rd = 0;
    char character;
    char *buffer = malloc(BUFFER_SIZE);

    if(!fd || !BUFFER_SIZE)
        return(NULL);
    while((rd = read(fd, &character, 1)) > 0 && (i < BUFFER_SIZE))
    {
        buffer[i] = character;
        if(character == '\n')
            break;
        i++;
    }
    if((!buffer[i] && !rd) || rd == -1)
    {
        free(buffer);
        return(NULL);
    }
    buffer[i + 1] = '\0';
    return(buffer);
}

int main(int argc, char **argv)
{
    int fd;
    char *ret;
    (void)argc;
    
    fd = open(argv[1], O_RDONLY);
    while((ret = get_next_line(fd)) != NULL)
        printf("%s\n", ret);
    return(0);
}