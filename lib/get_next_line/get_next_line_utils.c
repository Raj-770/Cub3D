/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpambhar <rpambhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 16:59:41 by rpambhar          #+#    #+#             */
/*   Updated: 2024/01/07 13:49:06 by rpambhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*gnl_calloc(size_t nitems, size_t size)
{
	char	*memory_ptr;
	size_t	i;

	i = 0;
	memory_ptr = malloc(nitems * size);
	if (memory_ptr == NULL)
		return (NULL);
	while (i < (nitems * size))
	{
		*((unsigned char *)memory_ptr + i) = '\0';
		i++;
	}
	return (memory_ptr);
}

char	*gnl_strjoin(char *s1, char *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	i = 0;
	if (!s1 && !s2)
		return (NULL);
	str = gnl_calloc(gnl_strlen(s1) + gnl_strlen(s2) + 1, sizeof(char));
	while (s1 && s1[i] != 0)
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2 && s2[j] != 0)
	{
		str[i + j] = s2[j];
		j++;
	}
	str[gnl_strlen(s1) + gnl_strlen(s2)] = '\0';
	if (s1)
		free(s1);
	return (str);
}

int	gnl_strchr(char *str, char c)
{
	int	i;
	int	len;

	if (!str)
		return (0);
	i = 0;
	len = gnl_strlen(str);
	while (i < len)
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	gnl_strlen(const char *s)
{
	int	len;

	len = 0;
	if (!s)
		return (0);
	while (s[len])
		len++;
	return (len);
}

void	*gnl_bzero(void *ptr, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		*((unsigned char *)ptr + i) = '\0';
		i++;
	}
	return (ptr);
}
