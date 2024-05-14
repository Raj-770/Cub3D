/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpambhar <rpambhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 16:59:02 by rpambhar          #+#    #+#             */
/*   Updated: 2024/01/07 13:49:50 by rpambhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = ft_read(fd, stash);
	if (!stash)
		return (NULL);
	line = ft_get_line(stash);
	if (line[0] == '\0')
	{
		free(stash);
		stash = NULL;
		return (free(line), NULL);
	}
	stash = ft_update_stash(stash);
	return (line);
}

char	*ft_read(int fd, char *stash)
{
	int		bytes_read;
	char	temp[BUFFER_SIZE + 1];

	bytes_read = 1;
	gnl_bzero(&temp, BUFFER_SIZE + 1);
	while (bytes_read > 0 && !gnl_strchr(temp, '\n'))
	{
		bytes_read = read(fd, temp, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(stash), NULL);
		temp[bytes_read] = '\0';
		stash = gnl_strjoin(stash, temp);
	}
	return (stash);
}

char	*ft_get_line(char *stash)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!stash)
		return (NULL);
	while (stash[j] && stash[j] != '\n')
		j++;
	if (stash[j] == '\n')
		j++;
	line = gnl_calloc(j + 1, sizeof(char));
	if (!line)
		return (NULL);
	while (stash && stash[i] != '\0' && stash[i] != '\n')
	{
		line[i] = stash[i];
		i++;
	}
	if (stash[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*ft_update_stash(char *stash)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	j = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
		return (free(stash), NULL);
	temp = gnl_calloc((gnl_strlen(stash) - i) + 1, sizeof(char));
	if (!temp)
		return (NULL);
	i++;
	while (stash[i])
		temp[j++] = stash[i++];
	temp[j] = '\0';
	return (free(stash), temp);
}
