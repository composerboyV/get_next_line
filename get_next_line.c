/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkwak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 21:47:24 by junkwak           #+#    #+#             */
/*   Updated: 2024/04/12 18:16:05 by junkwak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

char	*get_line(char *str)

{
	char	*backup;
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!str)
		return (0);
	backup = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!backup)
		return (0);
	while ((str[i] != '\n') && str[i])
		i++;
	if (str[i] == '\n')
		i++;
	while (str[i] && (str[i] != '\n'))
	{
		backup[j++] = str[i];
		i++;
	}
	backup[j] = '\0';
	return (backup);
}

char	*get_linecheck(char *str)
{
	char	*result;
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!str)
		return (0);
	result = (char *)malloc(sizeof(char) * BUFFER_SIZE + 2);
	if (!result)
		return (0);
	while (str[i] && (str[i] != '\n'))
	{
		result[j++] = str[i];
		i++;
	}
	if (str[i] == '\n')
		result[j + 1 ] = '\0';
	else
	{
		result[j + 1] = '\n';
		result[j + 2] = '\0';
	}
	return (result);
}

char	*ft_get_line(char *str, int fd)
{
	char	*buffer;
	char	*sub_str;
	int	str_len;
	int	read_len;

	str_len = 0;
	if (str[str_len])
		str_len++;
	buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return (0);
	sub_str = (char *)malloc(str_len +  BUFFER_SIZE + 1);
	if (!sub_str)
		return (0);
	read_len = read(fd, buffer, BUFFER_SIZE);
	buffer[read_len] = '\0';
	str = ft_strjoin(sub_str, buffer);
	free(buffer);
	free(sub_str);
	return (str);
}

char    *get_next_line(int fd) 
{
        static char     *str;
        char    *save;

//	str = (char *)malloc(1);
//	if (!str)
//		return (0);
//	str[0] = '\0';
	if ( fd < 2 || !fd || fd >1025 || BUFFER_SIZE < 0)
                return (0);
        str = ft_get_line(str, fd);
	if (!str)
                return (0);
        save = get_linecheck(str);
        str = get_line(str);
        return (save);
}

int    main(void)
{
    char        *ret;
    int        fd;
    int	i;

    i = 0;
    fd = open("test2", O_RDONLY);
    while (i++ < 4)
    {
	ret = get_next_line(fd);
        printf("ret : %s\n", ret);
    }
}

