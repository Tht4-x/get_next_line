/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dancel <dancel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 19:31:24 by dancel            #+#    #+#             */
/*   Updated: 2024/11/08 15:31:39 by dancel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*extract_line(char **stash)
{
	size_t	i;
	char	*line;
	char	*temp;

	i = 0;
	while ((*stash)[i] && (*stash)[i] != '\n')
		i++;
	line = ft_substr(*stash, 0, i + ((*stash)[i] == '\n'));
	if (!line)
		return (free(*stash), *stash = NULL, NULL);
	temp = ft_strdup(*stash + i + ((*stash)[i] == '\n'));
	free(*stash);
	*stash = temp;
	return (line);
}

char	*get_next_line_2(int fd, ssize_t bytes_read, char *temp, char *buffer)
{
	static char	*stash;

	if (fd < 0 || BUFFER_SIZE <= 0 || !buffer)
		return (free(stash), stash = NULL, free(buffer), NULL);
	if (!stash)
		stash = ft_strdup("");
	while (!ft_strchr(stash, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(stash), free(buffer), stash = NULL, NULL);
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		temp = ft_strjoin(stash, buffer);
		if (!temp)
			return (free(stash), free(buffer), stash = NULL, NULL);
		free(stash);
		stash = temp;
	}
	free(buffer);
	if (!stash || !*stash)
		return (free(stash), stash = NULL, NULL);
	return (extract_line(&stash));
}

char	*get_next_line(int fd)
{
	ssize_t		bytes_read;
	char		*temp;
	char		*buffer;

	bytes_read = 0;
	temp = "";
	buffer = malloc(BUFFER_SIZE + 1);
	return (get_next_line_2(fd, bytes_read, temp, buffer));
}
