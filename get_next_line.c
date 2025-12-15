/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shavryle <shavryle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 11:04:05 by shavryle          #+#    #+#             */
/*   Updated: 2025/12/15 18:28:04 by shavryle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>


char	*get_line(char *buffer)
{
	int		i;
	char	*line;

	line = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	line[i] = '\n';
	return (line);
}

char	*join_buffers(int fd, char *stash)
{
	char		*buffer;
	int			bytes_read;
	char		*tmp;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (free(stash), NULL);
	bytes_read = 1;
	while (!ft_strchr(stash, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(buffer), free(stash), NULL);
		else if (bytes_read > 0)
		{
			tmp = stash;
			buffer[bytes_read] = '\0';
			stash = ft_strjoin(tmp, buffer);
			free(tmp);
		}
	}
	free(buffer);
	return (stash);
}

char	*f_return_line(char *stash)
{
	int		i;
	char	*return_line;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i++;
	return_line = malloc(i + 1);
	if (!return_line)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
	{
		return_line[i] = stash[i];
		i++;
	}
	if (stash[i] == '\n')
	{
		return_line[i] = stash[i];
		i++;
	}
	return_line[i] = '\0';
	return (return_line);
}

char	*f_new_stash(char *stash)
{
	char	*start;
	char	*new_stash;

	if (!stash)
		return (free(stash), NULL);
	start = stash;
	while (*stash && *stash != '\n')
		stash++;
	if (*stash == '\n')
		stash++;
	if (*stash == 0 || !*stash)
		return (free(start), NULL);
	new_stash = ft_strdup(stash);
	free(start);
	return (new_stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*return_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!stash)
		stash = ft_strdup("");
	stash = join_buffers(fd, stash);
	if (!stash || *stash == 0)
		return (NULL);
	return_line = f_return_line(stash);
	stash = f_new_stash(stash);
	return (return_line);
}

int	main(void)
{
	int		fd;
	char	*line;
	int		i;

	i = 0;
	line = NULL;
	fd = open("text.txt", O_RDONLY);
	while (i < 2)
	{
		line = get_next_line(fd);
		printf("%s", line);
		i++;
		free(line);
	}
	close(fd);
	return (0);
}

