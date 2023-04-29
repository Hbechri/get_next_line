/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbechri <hbechri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 14:44:13 by hbechri           #+#    #+#             */
/*   Updated: 2023/01/23 17:21:33 by hbechri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	static char	*line;
	char		*str;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = read_line(fd, line);
	if (line == NULL)
		return (NULL);
	str = show_line(&line);
	if (str == NULL)
		return (NULL);
	line = next_line(line);
	return (str);
}

int main()
{

	int i = 0;
	int fd = open("hatim.txt", O_RDONLY);
	char *str;
	while (i < 10)
	{
		str = get_next_line(fd);
		printf("%s", str);
		i++;
	}
}