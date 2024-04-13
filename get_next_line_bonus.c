/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkwak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 21:47:24 by junkwak           #+#    #+#             */
/*   Updated: 2024/04/13 16:46:32 by junkwak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
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
	static char	*str[2048];
	char		*save;
	int			i;

	i = 0;
	if (!str[fd])
	{
		str[fd] = (char *)malloc(1);
		*str[fd] = '\0';
		if (!str[fd])
			return (0);
	}
	if (fd < 2 || BUFFER_SIZE <= 0)
	{
		free(str[fd]);
		return (0);
	}
	str[fd] = ft_get_line(str[fd], fd);
	if (!str[fd])
		return (0);
	save = get_linecheck(str[fd]);
	str[fd] = get_line(str[fd], i);
	return (save);
}

int    main(void)
{
    char        *ret1;
    char        *ret2;
    int        fd1;
    int		fd2;
    int	i;

    i = 0;
    fd1 = open("test2", O_RDONLY);
    fd2 = open("test2", O_RDONLY);
    while (i++ < 10)
    {
	ret1 = get_next_line(fd1);
	ret2 = get_next_line(fd2);
        printf("ret1 : %s", ret1);
        printf("ret2 : %s", ret2);
	free(ret1);
	free(ret2);
    }
    close(fd1);
    close(fd2);
}

