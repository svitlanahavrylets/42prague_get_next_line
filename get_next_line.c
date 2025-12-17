/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shavryle <shavryle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 11:04:05 by shavryle          #+#    #+#             */
/*   Updated: 2025/12/17 17:42:49 by shavryle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*join_buffers(int fd, char *stash)
{
	char		*buffer;
	int			bytes_read;
	char		*tmp;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (free(stash), NULL);
	bytes_read = 1;
	while (!ft_strchr(stash, DELIMITER) && bytes_read > 0)
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

char	*returned_line(char *stash)
{
	int		i;
	char	*line;

	i = 0;
	while (stash[i] && stash[i] != DELIMITER)
		i++;
	if (stash[i] == DELIMITER)
		i++;
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != DELIMITER)
	{
		line[i] = stash[i];
		i++;
	}
	if (stash[i] == DELIMITER)
	{
		line[i] = stash[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*create_new_stash(char *stash)
{
	int		i;
	char	*new_stash;

	if (!stash)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != DELIMITER)
		i++;
	if (stash[i] == DELIMITER)
		i++;
	if (stash[i] == '\0')
		return (free(stash), NULL);
	new_stash = ft_strdup(&stash[i]);
	free(stash);
	return (new_stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!stash)
		stash = ft_strdup("");
	stash = join_buffers(fd, stash);
	if (!stash || *stash == 0)
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	line = returned_line(stash);
	stash = create_new_stash(stash);
	return (line);
}

/*int	main(void)
{
	int		fd;
	char	*line;
	int		i;

	fd = open("text.txt", O_RDONLY);
	while ((line = get_next_line(fd)) != NULL)
	{

		i = 0;
		while (line[i])
		{
			if (line[i] != '\n') 
				write(1, &line[i], 1);
			i++;
		}
		write(1, "\n", 1);
		free(line);
	}
	close(fd);
	return (0);
}*/
