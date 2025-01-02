/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapaila <srapaila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 15:29:54 by srapaila          #+#    #+#             */
/*   Updated: 2024/12/16 17:47:19 by srapaila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_read(int fd, char *buf)
{
	char	*tmp;
	ssize_t	bytes;

	tmp = (char *)ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (!tmp)
		return (free(buf), NULL);
	bytes = 1;
	while (!ft_strchr(buf, '\n') && bytes != 0)
	{
		bytes = read(fd, tmp, BUFFER_SIZE);
		if (bytes == -1)
		{
			free(tmp);
			return (NULL);
		}
		tmp[bytes] = '\0';
		buf = ft_strjoin(buf, tmp);
	}
	free(tmp);
	return (buf);
}

char	*ft_getline(char *buf)
{
	char	*line;
	int		i;

	if (!buf)
		return (NULL);
	i = 0;
	while (buf[i] && buf[i] != '\n')
		i++;
	line = (char *)ft_calloc(sizeof(char), i + 2);
	if (!line)
		return (NULL);
	i = 0;
	while (buf[i] && buf[i] != '\n')
	{
		line[i] = buf[i];
		i++;
	}
	if (buf[i] == '\n')
	{
		line[i] = buf[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*ft_restof(char *buffer)
{
	char	*restof;
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
	restof = (char *)ft_calloc(sizeof(char), (ft_strlen(buffer) - i + 1));
	if (!restof)
	{
		free(buffer);
		return (NULL);
	}
	i++;
	j = 0;
	while (buffer[i])
		restof[j++] = buffer[i++];
	restof[j] = '\0';
	free(buffer);
	return (restof);
}

char	*get_next_line(int fd)
{
	static char	*buffer = NULL;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = ft_read(fd, buffer);
	if (!buffer)
		return (NULL);
	if (buffer[0] == '\0')
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	line = ft_getline(buffer);
	buffer = ft_restof(buffer);
	if (!buffer || buffer[0] == '\0')
	{
		free(buffer);
		buffer = NULL;
	}
	return (line);
}

// int main()
// {
//     int fd;
//     char *line;

//     // Apri un file di testo in modalità lettura
//     fd = open("text.txt", O_RDONLY);  // Sostituisci con il tuo file
//     if (fd < 0) {
//         perror("Errore nell'aprire il file");
//         return (1);
//     }

//     // Leggi e stampa le righe una alla volta
//     while ((line = get_next_line(fd)) != NULL) {
//         write(1,"%s", line);
//         free(line);  // Ricordati di liberare la memoria per ogni riga letta
//     }

//     // Chiudi il file
//     close(fd);
//     return (0);
// }
