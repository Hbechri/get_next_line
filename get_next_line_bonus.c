/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbechri <hbechri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 18:35:52 by hbechri           #+#    #+#             */
/*   Updated: 2023/01/22 15:19:55 by hbechri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*read_line(int fd, char *line)
{
	char		*buffer;
	ssize_t		i;

	i = 1;
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	if (!line)
		line = ft_strdup("");
	while (!ft_strchr(line) && i != 0)
	{
		i = read(fd, buffer, BUFFER_SIZE);
		if (i < 0)
		{
			free(buffer);
			free(line);
			line = NULL;
			return (NULL);
		}
		buffer[i] = '\0';
		line = ft_strjoin(line, buffer);
	}
	free (buffer);
	return (line);
}

char	*show_line(char **line)
{
	int	i;

	i = 0;
	if (line[0][i] == '\0')
	{
		free(*line);
		*line = NULL;
		return (NULL);
	}
	while (line[0][i] != '\n' && line[0][i] != '\0')
		i++;
	return (ft_substr(*line, 0, (i + 1)));
}

char	*next_line(char *line)
{
	char	*str;
	int		i;

	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
		i++;
	str = ft_substr(line, (i + 1), ft_strlen(line));
	free(line);
	line = NULL;
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*line[10240];
	char		*str;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line[fd] = read_line(fd, line[fd]);
	if (line[fd] == NULL)
		return (NULL);
	str = show_line(&line[fd]);
	if (str == NULL)
		return (NULL);
	line[fd] = next_line(line[fd]);
	return (str);
}
