/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapaila <srapaila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 16:13:50 by srapaila          #+#    #+#             */
/*   Updated: 2024/12/16 18:08:11 by srapaila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_read(int fd, char *buffer)
{
	char	*tmp;
	ssize_t	bytes;

	tmp = (char *)ft_calloc(sizeof(char), BUFFER_SIZE + 1);
	if (!tmp)
		return (free(buffer), NULL);
	bytes = 1;
	while (!ft_strchr(buffer, '\n') && bytes != 0)
	{
		bytes = read(fd, tmp, BUFFER_SIZE);
		if (bytes == -1)
		{
			free(tmp);
			return (NULL);
		}
		tmp[bytes] = '\0';
		buffer = ft_strjoin(buffer, tmp);
	}
	free (tmp);
	return (buffer);
}

char	*ft_getline(char *buffer)
{
	char	*line;
	int		i;

	if (!buffer)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = (char *)ft_calloc(sizeof(char), i + 2);
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*ft_rest_of_buffer(char *buffer)
{
	char	*rest;
	int		i;
	int		j;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	rest = (char *)ft_calloc(sizeof(char), (ft_strlen(buffer) - i + 1));
	if (!rest)
	{
		free(buffer);
		return (NULL);
	}
	i++;
	j = 0;
	while (buffer[i])
		rest[j++] = buffer[i++];
	rest[j] = '\0';
	free(buffer);
	return (rest);
}

char	*get_next_line(int fd)
{
	static char	*buffer[1024];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer[fd] = ft_read(fd, buffer[fd]);
	if (!buffer[fd])
		return (NULL);
	if (buffer[fd][0] == '\0')
	{
		free(buffer[fd]);
		buffer[fd] = NULL;
		return (NULL);
	}
	line = ft_getline(buffer[fd]);
	buffer[fd] = ft_rest_of_buffer(buffer[fd]);
	if (!buffer[fd] || buffer[fd][0] == '\0')
	{
		free(buffer[fd]);
		buffer[fd] = (NULL);
	}
	return (line);
}
// int main(void)
// {
//     int fd1 = open("file1.txt", O_RDONLY);
//     int fd2 = open("file2.txt", O_RDONLY);
//     char *line1;
//     char *line2;
//     if (fd1 < 0 || fd2 < 0)
//         return (1);
//     while ((line1 = get_next_line(fd1)) || (line2 = get_next_line(fd2)))
//     {
//         if (line1)
//         {
//             printf("File1: %s\n", line1);
//             free(line1);
//         }
//         if (line2)
//         {
//             printf("File2: %s\n", line2);
//             free(line2);
//         }
//     }
//     close(fd1);
//     close(fd2);
//     return (0);
// }
