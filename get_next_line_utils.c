/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkwak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 21:19:07 by junkwak           #+#    #+#             */
/*   Updated: 2024/04/12 01:28:31 by junkwak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t  ft_strlen(const char *s)
{
        size_t  i;

        i = 0;
        while (s[i])
                i++;
        return (i);
}

char    *ft_strjoin(char const *s1, char const *s2)
{
        char    *result;
        int             i;
        int             j;

        i = -1;
        result = (char *) malloc(sizeof(char *)
                        * (ft_strlen(s1) + ft_strlen(s2) + 1));
        if (!(result))
                return (NULL);
        *result = 0;
        while (s1[++i] != '\0')
                result[i] = s1[i];
        j = i;
        i = 0;
        while (s2[i] != '\0')
                result[j++] = s2[i++];
        result[j] = '\0';
        return (result);
}

char    *ft_strchr(const char *s, int c)
{
        int     i;
        while (s[i])
        {
                if (s[i] == c)
                        return ((char *)&s[i]);
                i++;
        }
        if (s[i] == c)
                return ((char *)&s[i]);
        return (NULL);
}

