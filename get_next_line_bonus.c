/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouate <ytouate@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 14:03:04 by ytouate           #+#    #+#             */
/*   Updated: 2021/12/04 17:06:51 by ytouate          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_get_line(char *buf)
{
	char	*temp;
	int		i;

	i = 0;
	while (buf[i] && buf[i] != '\n')
		i++;
	if (buf[i] == '\n')
		temp = malloc(i + 2 * sizeof(char));
	else
		temp = malloc(i + 1 * sizeof(char));
	if (!temp)
		return (NULL);
	i = 0;
	while (buf[i] && buf[i] != '\n')
	{
		temp[i] = buf[i];
		i++;
	}
	if (buf[i] == '\n')
		temp[i++] = '\n';
	temp[i] = '\0';
	return (temp);
}

char	*ft_save_left(char *buf)
{
	char	*temp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (buf[i] && buf[i] != '\n')
		i++;
	if (!buf[i])
	{
		free(buf);
		return (NULL);
	}
	temp = malloc(ft_strlen(buf) - i + 1 * sizeof(char));
	if (!temp)
	{
		free(buf);
		return (NULL);
	}
	i++;
	while (buf[i])
		temp[j++] = buf[i++];
	temp[j] = '\0';
	free(buf);
	return (temp);
}

char	*loop(char *save, char *buffer, int byte, int fd)
{
	buffer = malloc(BUFFER_SIZE + 1 * sizeof(char));
	buffer[0] = '\0';
	if (!buffer)
		return (NULL);
	while (!ft_strchr(buffer, '\n') && byte != 0)
	{
		byte = read (fd, buffer, BUFFER_SIZE);
		if (byte == -1)
		{
			free(buffer);
			return (NULL);
		}	
		buffer[byte] = '\0';
		save = ft_strjoin(save, buffer);
	}
	free(buffer);
	return (save);
}

char	*get_next_line(int fd)
{
	static char		*save[OPEN_MAX];
	char			*buffer;
	char			*line;
	int				byte;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	byte = 1;
	buffer = NULL;
	save[fd] = loop(save[fd], buffer, byte, fd);
	if (!save[fd])
		return (NULL);
	if (!save[fd][0])
	{
		free(save[fd]);
		save[fd] = NULL;
		return (NULL);
	}
	line = ft_get_line(save[fd]);
	save[fd] = ft_save_left(save[fd]);
	return (line);
}
