/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkwak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 21:47:24 by junkwak           #+#    #+#             */
/*   Updated: 2024/04/13 16:36:39 by junkwak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

char	*get_line(char *str, int i)

{
	char	*backup;
	int		j;
	int		str_len;

	str_len = 0;
	j = 0;
	while (str[str_len])
		str_len++;
	while ((str[i] != '\n') && str[i])
		i++;
	if (str[i] == '\n')
		i++;
	if (str[i] == 0)
	{
		free(str);
		return (0);
	}
	backup = (char *)malloc(sizeof(char) * str_len - i + 1);
	if (!backup)
		return (0);
	while (str[i] && j <= str_len)
		backup[j++] = str[i++];
	backup[j] = '\0';
	free(str);
	return (backup);
}

char	*get_linecheck(char *str)
{
	char	*result;
	int		i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	result = (char *)malloc(sizeof(char) * i +2);
	if (!result)
		return (0);
	i = 0;
	while (str[i] && (str[i] != '\n'))
	{
		result[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{
		result[i] = str[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

char	*ft_get_line(char *str, int fd)
{
	char	*buffer;
	int		a;

	if (str == 0)
	{
		free(str);
		return (0);
	}
	buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return (0);
	a = 1;
	while (ft_strchr (str, '\n') == 0 && a != 0)
	{
		a = read(fd, buffer, BUFFER_SIZE);
		buffer[a] = '\0';
		str = ft_strjoin(str, buffer);
	}
	free(buffer);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*save;
	int			i;

	i = 0;
	if (!str)
	{
		str = (char *)malloc(1);
		str[0] = '\0';
		if (!str)
			return (0);
	}
	if (fd < 2 || BUFFER_SIZE <= 0)
	{
		free(str);
		return (0);
	}
	str = ft_get_line(str, fd);
	if (!str)
		return (0);
	save = get_linecheck(str);
	str = get_line(str, i);
	return (save);
}
/*
int    main(void)
{
    char        *ret;
    int        fd;
    int	i;

    i = 0;
    fd = open("test2", O_RDONLY);
    while (i++ < 10)
    {
	ret = get_next_line(fd);
        printf("ret : %s\n", ret);
	free(ret);
    }
}
*/
