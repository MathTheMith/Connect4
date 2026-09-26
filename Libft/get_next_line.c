/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachon <mvachon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 17:59:09 by math              #+#    #+#             */
/*   Updated: 2026/09/26 11:05:42 by mvachon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*free_and_return_null(char **ptr1, char **ptr2)
{
	free_ptr((void **)ptr1);
	free_ptr((void **)ptr2);
	return (NULL);
}

char	*safe_read(int fd, char *storage)
{
	char	*buffer;
	int		bytes_read;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	while (1)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free_and_return_null(&buffer, &storage));
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		storage = ft_strjoin(storage, buffer);
		if (!storage)
			return (free_ptr((void **)&buffer));
		if (ft_strchr(storage, '\n'))
			break ;
	}
	free_ptr((void **)&buffer);
	return (storage);
}

static char	*extract_line(char *storage)
{
	char	*line;
	int		i;

	if (!storage || !storage[0])
		return (NULL);
	i = 0;
	while (storage[i] && storage[i] != '\n')
		i++;
	line = ft_substr(storage, 0, i + 1);
	return (line);
}

static char	*update_storage(char *storage)
{
	char	*new_storage;
	int		i;

	if (!storage)
		return (NULL);
	i = 0;
	while (storage[i] && storage[i] != '\n')
		i++;
	if (!storage[i])
		return (free_ptr((void **)&storage));
	new_storage = ft_substr(storage, i + 1, ft_strlen(storage) - i);
	free_ptr((void **)&storage);
	return (new_storage);
}

char	*get_next_line(int fd)
{
	static char	*storage;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	storage = safe_read(fd, storage);
	if (!storage)
		return (NULL);
	line = extract_line(storage);
	storage = update_storage(storage);
	return (line);
}