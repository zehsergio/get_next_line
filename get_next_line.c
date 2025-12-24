/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdias-ju <jdias-ju@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 12:02:21 by jdias-ju          #+#    #+#             */
/*   Updated: 2025/12/24 14:49:57 by jdias-ju         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// It enters a loop that continues until a '\n' is found in remainder (static variable) OR the read() function returns 0 (EOF).
// It fills a temporary buffer and uses ft_strjoin to append it to your static remainder.
static char	*read_and_stash(int fd, char *stash)
{
	char	*buf;
	ssize_t	bytes_read;

	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (NULL);
	bytes_read = 1; 
	while (!ft_strchr(stash, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(buf);
			free(stash);
			stash = NULL;
			return (NULL); 
		}
		if (bytes_read > 0)
		{
			buf[bytes_read] = '\0'; 
			stash = ft_strjoin(stash, buf); 
		}
	}
	free(buf);
	return (stash);
}

// Once 'read_and_stash' stops, you have a string that contains at least one full line (or the end of the file).
// This function scans the string until '\n' and copies everything up to that point into a new string to return.
static char	*extract_line(char *stash)
{
	size_t	i;
	char	*line;

	i = 0;
	if (!stash || !stash[0])
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i++;
	line = ft_substr(stash, 0, i);
	return (line);
}

// This function remove from the static remainder (static variable), the part of that 'extract line' just returned.
// Example: If it returned "Hello'\n'", and remainder (static variable) was "Hello'\n'World", this function makes remainder (static variable) equal to "World".
static char	*clean_stash(char *stash)
{
	size_t	i;
	char	*new_stash;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
	{
		free(stash);
		return (NULL);
	}
	new_stash = ft_substr(stash, i + 1, ft_strlen(stash) - i);
	free(stash);
	return (new_stash);
}

char *get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = read_and_stash(fd, stash);
	if (!stash)
		return (NULL);
	line = extract_line(stash);
	stash = clean_stash(stash);
	return (line);
}
