/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shavryle <shavryle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 11:04:05 by shavryle          #+#    #+#             */
/*   Updated: 2025/12/03 18:00:00 by shavryle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char	buffer[1024];
	int		bytes_read;

	bytes_read = read(fd, buffer, 5);
	printf("%d", bytes_read);
	return (buffer);
}

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("text.txt", O_RDONLY);

	line = get_next_line(fd);
	while (line != NULL)
	{
		printf("%p", line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}
